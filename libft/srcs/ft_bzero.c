/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmisiedj <wmisiedj@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/30 15:56:12 by wmisiedj      #+#    #+#                 */
/*   Updated: 2020/07/10 15:08:14 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		((char*)s)[n - 1] = 0;
		--n;
	}
}

// void	ft_bzero(void *s, size_t n)
// {
// 	char	i;

// 	i = 1;
// 	while (i * sizeof(long long int) <= n)
// 	{
// 		((long long int*)s)[i - 1] = 0;
// 		i++;
// 	}
// 	while (i * sizeof(long int) <= n)
// 	{
// 		((long int*)s)[i - 1] = 0;
// 		i++;
// 	}
// 	while (i * sizeof(int) <= n)
// 	{
// 		((int*)s)[i - 1] = 0;
// 		i++;
// 	}
// 	while (i * sizeof(char) <= n)
// 	{
// 		((char*)s)[i - 1] = 0;
// 		i++;
// 	}
// }
