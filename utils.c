/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:48:43 by gonische          #+#    #+#             */
/*   Updated: 2024/08/28 17:23:53 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	child_delete_trash(int pipefd[2], char **cmd, char *exec)
{
	close_pipe(pipefd);
	free(exec);
	free_char_matrix(cmd);
}

void	free_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}
