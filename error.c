/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:21 by gonische          #+#    #+#             */
/*   Updated: 2024/08/30 13:38:28 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fatal_error(const char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

int	check_err_fd_pid(int fd, const char *err_str, t_args *args)
{
	if (fd < 0)
	{
		clean_allocated_stuff(args);
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
