/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:14:57 by gonische          #+#    #+#             */
/*   Updated: 2024/07/18 15:07:33 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // Is used for size_t

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = '\0';
}

/*
// Tests
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_strdup(char *src)
{
	int		len;
	char	*result;

	len = ft_strlen(src);
	result = (char *)malloc(len);
	ft_strcpy(result, src);
	return (result);
}

void	test(void *s, size_t n)
{
	char	*str1;

	str1 = ft_strdup((char *)s);
	ft_bzero((void *)str1,  n);
	printf("Result: %s\n", str1);
}

int	main(void)
{
	test("1111", 1);
}
*/