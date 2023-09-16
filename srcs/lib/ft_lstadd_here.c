/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:52:23 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/16 18:43:22 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_here(t_list **lst, t_list *new)
{
	if (!lst)
		lst = &new;
	if (!(*lst))
		*lst = new;
	else
	{
		new->prev = (*lst);
		if ((*lst)->next)
		{
			new->next = (*lst)->next;
			(*lst)->next->prev = new;
		}
		(*lst)->next = new;
	}
}

// void	ft_lstadd_here(t_list **lst, t_list *new)
// {
// 	if (!*lst)
// 	{
// 		new->prev = 0;
// 		(*lst) = new;
// 	}
// 	else
// 	{
// 		if ((*lst)->prev)
// 		{
// 			new->prev = (*lst)->prev;
// 			(*lst)->prev->next = new;
// 		}
// 		else
// 			new->prev = NULL;
// 		if ((*lst)->next)
// 		{
// 			new->next = (*lst)->next;
// 			(*lst)->next->prev = new;
// 		}
// 		else
// 			new->next = NULL;
// 		(*lst)->next = new;
// 	}
// }

// void	ft_lstadd_here(t_list **lst, t_list *new)
// {
// 	if (!*lst)
// 	{
// 		new->prev = 0;
// 		(*lst) = new;
// 	}
// 	else
// 	{
// 		new->prev = (*lst);
// 		if ((*lst)->next)
// 		{
// 			new->next = (*lst)->next;
// 			(*lst)->next->prev = new;
// 		}
// 		else
// 			new->next = NULL;
// 		(*lst)->next = new;
// 	}
// }
