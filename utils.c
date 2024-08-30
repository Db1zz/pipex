/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:48:43 by gonische          #+#    #+#             */
/*   Updated: 2024/08/30 00:24:09 by gonische         ###   ########.fr       */
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

void	clean_allocated_stuff(t_args *args)
{
	close_pipe(args->pipefd);
	free_char_matrix(args->cmd[0]);
	free_char_matrix(args->cmd[1]);
	free(args->exe[0]);
	free(args->exe[1]);
}
