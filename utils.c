/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:48:43 by gonische          #+#    #+#             */
/*   Updated: 2024/08/31 01:48:53 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	free_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	doomsday(t_args *args)
{
	if (args->cmd[0])
		free_char_matrix(args->cmd[0]);
	if (args->cmd[1])
		free_char_matrix(args->cmd[1]);
	if (args->exe[0])
		free(args->exe[0]);
	if (args->exe[1])
		free(args->exe[1]);
	if (args->fd[0] >= 0)
		close(args->fd[0]);
	if (args->fd[1] >= 0)
		close(args->fd[1]);
	close_pipe(args->pipefd);
}

int	check_access(const char *filepath, int acc_mode)
{
	int	result;

	result = access(filepath, acc_mode);
	if (result < 0)
		perror(filepath);
	return (result);
}
