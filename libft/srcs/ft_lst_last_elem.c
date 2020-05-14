/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_last_elem.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: zitzak <zitzak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/14 09:42:21 by zitzak        #+#    #+#                 */
/*   Updated: 2020/05/14 09:46:33 by zitzak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_list_last_elem(t_list *head)
{
	t_list		*temp;

	if (head == NULL)
		return (NULL);
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
