/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnstr_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmisiedj <wmisiedj@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 17:02:54 by wmisiedj      #+#    #+#                 */
/*   Updated: 2020/04/22 17:40:14 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

ssize_t		ft_putnstr_fd(const char *str, size_t len, int fd)
{
	return (write(fd, str, len));
}
