/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:56:08 by gonische          #+#    #+#             */
/*   Updated: 2024/09/02 12:29:10 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_cmd_path(char	**env_paths, char *patched_exec)
{
	char	*result;

	if (!env_paths || !patched_exec)
		fatal_error_info(ERR_NULL_ARGS, "find_cmd_path");
	result = NULL;
	while (*env_paths)
	{
		if (is_file_accessible(*env_paths, patched_exec, F_OK | X_OK))
		{
			result = ft_strjoin(*env_paths, patched_exec);
			break ;
		}
		env_paths++;
	}
	return (result);
}

char	*get_cmd_path(const char *exec, char **envp)
{
	char	*patched_exec;
	char	**env_paths;
	char	*result;

	if (exec == NULL)
		fatal_error_info(ERR_EMPTY_CMD, "(NULL)");
	if (access(exec, X_OK) >= 0)
		return (ft_strjoin("", exec));
	patched_exec = ft_strjoin("/", exec);
	if (!patched_exec)
		fatal_error_info(ERR_MALLOC, "get_cmd_path");
	while (*envp && ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	env_paths = ft_split(*envp + 5, ':');
	if (!env_paths)
		fatal_error_info(ERR_MALLOC, "get_cmd_path");
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
	if (argv[2][0])
	{
		args->cmd[0] = ft_split(validate_cmd(argv[2]), CMD_DELIMETER);
		args->exe[0] = get_cmd_path(args->cmd[0][0], args->env);
	}
	if (argv[3][0])
	{
		args->cmd[1] = ft_split(validate_cmd(argv[3]), CMD_DELIMETER);
		args->exe[1] = get_cmd_path(args->cmd[1][0], args->env);
	}
}
