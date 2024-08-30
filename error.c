/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:21 by gonische          #+#    #+#             */
/*   Updated: 2024/08/31 01:42:03 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_error(const char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

void	fatal_error(const char *str)
{
	display_error(str);
	exit(EXIT_FAILURE);
}

int	check_err_fd_pid(int fd, const char *err_str, t_args *args)
{
	if (fd < 0)
	{
		doomsday(args);
		free(args);
		fatal_error(err_str);
	}
	return (fd);
}

void	check_arg_error(int argc, char **argv)
{
	int	i;

	if (argc != ARGS_AMOUNT)
	{
		i = 1;
		ft_printf(ERR_ARGS_AMOUNT);
		while (i < argc)
			ft_printf("[%s]", argv[i++]);
		ft_printf("\n");
		exit(EXIT_FAILURE);
	}
}
