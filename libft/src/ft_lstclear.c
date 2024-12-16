/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:14:12 by abernade          #+#    #+#             */
/*   Updated: 2023/11/14 12:49:38 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (!lst || !*lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		next = node->next;
		(*del)(node->content);
		free(node);
		node = next;
	}
	*lst = (t_list *)0;
}
