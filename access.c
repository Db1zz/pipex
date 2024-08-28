/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:30:55 by gonische          #+#    #+#             */
/*   Updated: 2024/08/28 18:11:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_access(const char *filepath, int acc_mode)
{
	int	result;

	result = access(filepath, acc_mode);
	if (result < 0)
		perror(filepath);
	return (result);
}

void	open_file_as_stdin(const char *path)
{
	int	fd;
	int	fd_in;

	if (check_access(path, F_OK) < 0)
		exit(EXIT_FAILURE);
	if (check_access(path, R_OK) < 0)
		exit(EXIT_FAILURE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		exit(EXIT_FAILURE);
	}
	fd_in = dup2(fd, STDIN_FILENO);
	close(fd);
	if (fd_in < 0)
	{
		perror("dup2()");
		exit(EXIT_FAILURE);
	}
}

void	open_file_as_stdout(const char *path)
{
	int	fd;
	int	fd_out;

	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (fd < 0)
	{
		perror(path);
		exit(EXIT_FAILURE);
	}
	fd_out = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (fd_out < 0)
	{
		perror("dup2()");
		exit(EXIT_FAILURE);
	}
}
