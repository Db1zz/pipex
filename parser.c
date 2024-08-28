/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:56:08 by gonische          #+#    #+#             */
/*   Updated: 2024/08/28 18:05:27 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_executable_path(const char *exec)
{
	const char	*exec_unix_folder = "/bin/";
	char		*result;

	if (exec == NULL)
	{
		ft_printf("Command string is empty\n");
		exit(EXIT_FAILURE);
	}
	result = ft_strjoin(exec_unix_folder, exec);
	return (result);
}

char	**parse_cmd(const char *cmd)
{
	char	**result;

	if (!cmd)
		return (NULL);
	result = ft_split(cmd, ' ');
	return (result);
}

void	parse_args(char **argv, char **cmd[2], char *exe[2])
{
	cmd[0] = parse_cmd(argv[2]);
	cmd[1] = parse_cmd(argv[3]);
	exe[0] = get_executable_path(cmd[0][0]);
	exe[1] = get_executable_path(cmd[1][0]);
}

void	clean_allocated_stuff(char **cmd[2], char *exe[2])
{
	free_char_matrix(cmd[0]);
	free_char_matrix(cmd[1]);
	free(exe[0]);
	free(exe[1]);
}
