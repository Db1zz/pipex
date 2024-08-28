/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:21 by gonische          #+#    #+#             */
/*   Updated: 2024/08/28 14:31:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_err_fd_pid(int fd, const char *err_str)
{
	if (fd < 0)
	{
		perror(err_str);
		exit(EXIT_FAILURE);
	}
}
