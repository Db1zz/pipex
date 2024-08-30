/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:56:08 by gonische          #+#    #+#             */
/*   Updated: 2024/08/30 02:51:37 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_file_accessible(char *path, char *filename, int flags)
{
	bool	result;
	char	*complete_path;

	if (!path || !filename)
		fatal_error(ERR_NULL_ARGS);
	complete_path = ft_strjoin(path, filename);
	if (!complete_path)
		fatal_error(ERR_MALLOC);
	result = access(complete_path, flags) >= 0;
	free(complete_path);
	return (result);
}

static char	*find_cmd_path(char	**env_paths, char *patched_exec)
{
	if (!env_paths || !patched_exec)
		fatal_error(ERR_NULL_ARGS);
	while (*env_paths)
	{
		if (is_file_accessible(*env_paths, patched_exec, F_OK | X_OK))
			return (ft_strjoin(*env_paths, patched_exec));
		env_paths++;
	}
	return (NULL);
}

char	*get_cmd_path(const char *exec, char **envp)
{
	char	*patched_exec;
	char	**env_paths;
	char	*result;

	if (exec == NULL)
		fatal_error(ERR_EMPTY_CMD);
	patched_exec = ft_strjoin("/", exec);
	if (!patched_exec)
		fatal_error(ERR_MALLOC);
	if (is_file_accessible(DEFAULT_UNIX_EXEC_FOLDER, patched_exec, X_OK))
		return (ft_strjoin(DEFAULT_UNIX_EXEC_FOLDER, patched_exec));
	while (*envp && ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	env_paths = ft_split(*envp + 5, ':');
	if (!env_paths)
		fatal_error(ERR_MALLOC);
	result = find_cmd_path(env_paths, patched_exec);
	free_char_matrix(env_paths);
	free(patched_exec);
	return (result);
}

char	*validate_cmd(char *cmd)
{
	char	*cmd_start;
	char	*c;

	cmd_start = cmd;
	while (*cmd_start)
	{
		if (*cmd_start == '\'' || *cmd_start == '\"')
		{
			c = cmd_start + 1;
			while (*c && *c != *cmd_start)
				c++;
			if (*c == *cmd_start)
			{
				*c = CMD_DELIMETER;
				*cmd_start = CMD_DELIMETER;
				cmd_start = c;
			}
		}
		if (*cmd_start == ' ')
			*cmd_start = CMD_DELIMETER;
		cmd_start++;
	}
	return (cmd);
}

void	parse_args(char **argv, char **envp, t_args *args)
{
	args->env = envp;
	args->cmd[0] = ft_split(validate_cmd(argv[2]), CMD_DELIMETER);
	args->cmd[1] = ft_split(validate_cmd(argv[3]), CMD_DELIMETER);
	args->exe[0] = get_cmd_path(args->cmd[0][0], args->env);
	args->exe[1] = get_cmd_path(args->cmd[1][0], args->env);
}
