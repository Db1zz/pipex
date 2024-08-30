/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:53:52 by gonische          #+#    #+#             */
/*   Updated: 2024/08/30 14:51:39 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_in(char *filepath, t_args *args)
{
	args->pid[0] = fork();
	if (check_err_fd_pid(args->pid[0], ERR_FORK_IN, args) == 0)
	{
		open_file_as_stdin(filepath);
		if (dup2(args->pipefd[1], STDOUT_FILENO) < 0)
			fatal_error(ERR_DUP2_FAILED);
		close_pipe(args->pipefd);
		execve(args->exe[0], args->cmd[0], args->env);
		perror(args->exe[0]);
	}
}

void	child_out(char *filepath, t_args *args)
{
	args->pid[1] = fork();
	if (check_err_fd_pid(args->pid[1], ERR_FORK_OUT, args) == 0)
	{
		open_file_as_stdout(filepath);
		if (dup2(args->pipefd[0], STDIN_FILENO) < 0)
			fatal_error(ERR_DUP2_FAILED);
		close_pipe(args->pipefd);
		execve(args->exe[1], args->cmd[1], args->env);
		perror(args->exe[1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	check_arg_error(argc, argv);
	parse_args(argv, envp, &args);
	pipe(args.pipefd);
	check_err_fd_pid(args.pipefd[1], ERR_OPN_PIPE, &args);
	child_in(argv[1], &args);
	child_out(argv[4], &args);
	close_pipe(args.pipefd);
	clean_allocated_stuff(&args);
	waitpid(args.pid[0], NULL, 0);
	waitpid(args.pid[1], NULL, 0);
	return (0);
}
