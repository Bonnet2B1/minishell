/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuning_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:28:17 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/05 21:03:18 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew_tuning(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
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

void	*calloc_tuning(t_list **lst, size_t size)
{
	t_list			*new;
	unsigned char	*ret;
	size_t			i;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
		ret[i++] = 0;
	new = ft_lstnew_tuning(ret);
	if (!new)
		return (NULL);
	ft_lstadd_back(lst, new);
	return (ret);
}

void	free_tuning(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	free(*lst);
}
