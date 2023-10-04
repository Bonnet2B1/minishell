/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:45:27 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 20:01:03 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdel_here(t_list **first, t_list *to_delet, void (*del)(void*))
{
	if (!first || !*first || !to_delet)
		return ;
	if (*first == to_delet)
		*first = to_delet->next;
	if (to_delet->next)
		to_delet->next->prev = to_delet->prev;
	if (to_delet->prev)
		to_delet->prev->next = to_delet->next;
	del(to_delet->content);
	free(to_delet);
}
