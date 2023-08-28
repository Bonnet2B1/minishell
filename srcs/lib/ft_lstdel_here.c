/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:45:27 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/28 16:45:33 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdel_here(t_list **first, t_list *node_to_delete)
{
	if (!first || !*first || !node_to_delete)
		return ;
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	else
		*first = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	else if (!node_to_delete->prev)
		*first = 0;
	free(node_to_delete);
}
