/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:53:52 by gonische          #+#    #+#             */
/*   Updated: 2024/08/29 16:31:04 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_in(int pipefd[2], char *filepath, char **cmd, char *exe)
{
	open_file_as_stdin(filepath);
	dup2(pipefd[1], STDOUT_FILENO);
	close_pipe(pipefd);
	if (execve(exe, cmd, NULL) < 0)
	{
		perror(exe);
		exit(EXIT_FAILURE);
	}
}

void	child_out(int pipefd[2], char *filepath, char **cmd, char *exe)
{
	open_file_as_stdout(filepath);
	dup2(pipefd[0], STDIN_FILENO);
	close_pipe(pipefd);
	if (execve(exe, cmd, NULL) < 0)
	{
		perror(exe);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid[2];
	int		pipefd[2];
	char	**cmd[2];
	char	*exe[2];

	check_arg_error(argc, argv);
	parse_args(argv, cmd, exe);
	pipe(pipefd);
	pid[0] = fork();
	check_err_fd_pid(pid[0], "fork0");
	if (pid[0] == 0)
		child_in(pipefd, argv[1], cmd[0], exe[0]);
	else
	{
		pid[1] = fork();
		check_err_fd_pid(pid[1], "fork1");
		if (pid[1] == 0)
			child_out(pipefd, argv[4], cmd[1], exe[1]);
		close_pipe(pipefd);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], NULL, 0);
		clean_allocated_stuff(cmd, exe);
	}
	return (0);
}
