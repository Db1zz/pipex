/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:21 by gonische          #+#    #+#             */
/*   Updated: 2024/09/02 12:32:06 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_error(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return ;
	write(STDERR_FILENO, str1, ft_strlen(str1));
	write(STDERR_FILENO, str2, ft_strlen(str2));
	write(STDERR_FILENO, "\n", 1);
}

void	fatal_error(const char *str1)
{
	if (!str1)
		display_error(str1, "");
	exit(EXIT_FAILURE);
}

void	fatal_error_info(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		display_error(str1, str2);
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
