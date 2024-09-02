/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:53:52 by gonische          #+#    #+#             */
/*   Updated: 2024/09/02 12:14:52 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	check_child_params(char *exe, char **cmd, int fd, char *fn)
{
	if (fd < 0)
	{
		display_error(ERR_NO_FILE, fn);
		return (false);
	}
	if (!cmd || !exe || access(exe, X_OK) < 0)
	{
		display_error(ERR_INCORRECT_CMD, cmd[0]);
		return (false);
	}
	return (true);
}

static void	child_in(t_args *args, char *fn)
{
	if (!check_child_params(args->exe[0], args->cmd[0], args->fd[0], fn))
		return ;
	args->pid[0] = fork();
	if (check_err_fd_pid(args->pid[0], ERR_FORK_IN, args) == 0)
	{
		if (dup2(args->fd[0], STDIN_FILENO) < 0
			|| dup2(args->pipefd[1], STDOUT_FILENO) < 0)
		{
			doomsday(args);
			free(args);
			fatal_error(ERR_DUP2_FAILED);
		}
		close_pipe(args->pipefd);
		execve(args->exe[0], args->cmd[0], args->env);
		perror(args->exe[0]);
	}
}

static void	child_out(t_args *args, char *fn)
{
	if (!check_child_params(args->exe[1], args->cmd[1], args->fd[1], fn))
		return ;
	args->pid[1] = fork();
	if (check_err_fd_pid(args->pid[1], ERR_FORK_OUT, args) == 0)
	{
		if (dup2(args->fd[1], STDOUT_FILENO) < 0
			|| dup2(args->pipefd[0], STDIN_FILENO) < 0)
		{
			doomsday(args);
			free(args);
			fatal_error(ERR_DUP2_FAILED);
		}
		close_pipe(args->pipefd);
		execve(args->exe[1], args->cmd[1], args->env);
		perror(args->exe[1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;

	check_arg_error(argc, argv);
	args = ft_calloc(1, sizeof(t_args));
	parse_args(argv, envp, args);
	pipe(args->pipefd);
	check_err_fd_pid(args->pipefd[1], ERR_OPN_PIPE, args);
	args->fd[0] = open(argv[1], O_RDONLY, 0644);
	args->fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	child_in(args, argv[1]);
	child_out(args, argv[4]);
	doomsday(args);
	waitpid(args->pid[0], NULL, 0);
	waitpid(args->pid[1], NULL, 0);
	free(args);
	return (0);
}
