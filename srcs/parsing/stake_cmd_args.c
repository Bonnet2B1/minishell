/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stake_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:29:20 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/11 21:38:51 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_lst(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		if (((t_split *)tmp->content)->to_del)
			ft_lstdel_here(lst, tmp, (void *)free_split_node);
		tmp = next;
	}
}

t_list	*prepare_new(void)
{
	t_list	*new;

	new = ft_lstnew((t_split *)create_split_node(NULL));
	((t_split *)new->content)->token = COMMAND;
	((t_split *)new->content)->cmd = malloc(sizeof(char *));
	((t_split *)new->content)->cmd[0] = NULL;
	return (new);
}

void	stack_cmd_args(t_shell_memory *data, t_list *lst)
{
	t_list	*new;
	t_list	*save;

	while (lst)
	{
		if (((t_split *)lst->content)->token == COMMAND)
			save = lst;
		new = prepare_new();
		while (lst && ((t_split *)lst->content)->token != PIPE)
		{
			if (((t_split *)lst->content)->token == COMMAND)
			{
				((t_split *)new->content)->cmd = ft_tabadd_back(((t_split *)
							new->content)->cmd, ft_strdup(((t_split *)lst->content)->arg));
				((t_split *)lst->content)->to_del = 1;
			}
			lst = lst->next;
		}
		if ((((t_split *)new->content)->cmd[0]))
			ft_lstadd_here(save, new);
		else
			free_split_node(new->content);
		if (lst)
			lst = lst->next;
	}
	clean_lst(&data->parsing_lst);
}
