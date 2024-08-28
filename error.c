/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:21 by gonische          #+#    #+#             */
/*   Updated: 2024/08/28 20:07:45 by gonische         ###   ########.fr       */
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

void	check_arg_error(int argc, char **argv)
{
	int	i;

	if (argc != ARGS_AMOUNT)
	{
		i = 1;
		ft_printf("Invalid amount of arguments: ");
		while (i < argc)
			ft_printf("[%s]", argv[i++]);
		ft_printf("\n");
	}
	exit(EXIT_FAILURE);
}
