/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 14:40:57 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/04/22 17:38:32 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	node = NULL;
	node = (t_list*)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (content == NULL)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		node->content = ft_memdup((void*)content, content_size);
		if (!(node->content))
		{
			free(node);
			return (NULL);
		}
		node->content_size = content_size;
	}
	node->next = NULL;
	return (node);
}
