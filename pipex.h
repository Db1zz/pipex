/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:36:13 by gonische          #+#    #+#             */
/*   Updated: 2024/08/28 20:07:35 by gonische         ###   ########.fr       */
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
# include "./libft/libft.h"
# include "./ft_printf/include/ft_printf.h"

# ifndef ARGS_AMOUNT
#  define ARGS_AMOUNT 5
# endif // ARGS_AMOUNT

void	check_err_fd_pid(int fd, const char *err_str);
char	*get_executable_path(const char *exec);
char	**parse_cmd(const char *cmd);
int		check_access(const char *filepath, int acc_mode);
void	open_file_as_stdin(const char *path);
void	open_file_as_stdout(const char *path);
void	child_delete_trash(int pipefd[2], char **cmd, char *exec);
void	free_char_matrix(char **matrix);
void	close_pipe(int pipefd[2]);
void	parse_args(char **argv, char **cmd[2], char *exe[2]);
void	clean_allocated_stuff(char **cmd[2], char *exe[2]);
void	check_arg_error(int argc, char **argv);

#endif // PIPEX_H