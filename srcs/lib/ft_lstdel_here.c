/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:45:27 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/10 22:33:59 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdel_here(t_list **first, t_list *node_to_delete, void (*del)(void*))
{
	if (!first || !*first || !node_to_delete)
		return ;
	if (*first == node_to_delete)
		*first = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	del(node_to_delete->content);
	free(node_to_delete);
}
