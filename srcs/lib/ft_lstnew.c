/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:34:16 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/05 01:55:18 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(t_shell_memory *data, void *content)
{
	t_list	*list;

	list = calloc_tuning(&data->malloc_chain, sizeof(t_list));
	if (!list)
		return (NULL);
	if (list)
	{
		list->content = content;
		list->next = NULL;
		list->prev = NULL;
	}
	return (list);
}
