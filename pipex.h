/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:36:13 by gonische          #+#    #+#             */
/*   Updated: 2024/08/30 02:51:43 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "./libft/libft.h"

# ifndef ARGS_AMOUNT
#  define ARGS_AMOUNT 5
# endif // ARGS_AMOUNT

# ifndef DEFAULT_UNIX_EXEC_FOLDER
#  define DEFAULT_UNIX_EXEC_FOLDER "/bin"
# endif // DEFAULT_UNIX_EXEC_FOLDER

/*
	Macroses for displaying errors
*/
# define ERR_FORK_IN "Failed to create child_in with Fork()"
# define ERR_FORK_OUT "Failed to create child_out with Fork()"
# define ERR_OPN_PIPE "Failed to open Pipe."
# define ERR_EMPTY_CMD "Command string is empty"
# define ERR_MALLOC	"Buy more RAM Lol"
# define ERR_ARGS_AMOUNT "Invalid amount of arguments: "
# define ERR_NULL_ARGS "One or more arguments are NULL"
# define ERR_DUP2_FAILED "Failed to open new FD with dup2()"

# define CMD_DELIMETER 127

typedef struct t_args
{
	pid_t	pid[2];
	int		pipefd[2];
	char	**cmd[2];
	char	*exe[2];
	char	**env;
}	t_args;

int		check_err_fd_pid(int fd, const char *err_str);
char	*get_cmd_path(const char *exec, char **envp);
char	*validate_cmd(char *cmd);
int		check_access(const char *filepath, int acc_mode);
void	fatal_error(const char *str);
void	open_file_as_stdin(const char *path);
void	open_file_as_stdout(const char *path);
void	free_char_matrix(char **matrix);
void	close_pipe(int pipefd[2]);
void	parse_args(char **argv, char **envp, t_args *args);
void	clean_allocated_stuff(t_args *args);
void	check_arg_error(int argc, char **argv);

#endif // PIPEX_H