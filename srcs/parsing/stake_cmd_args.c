/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stake_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:29:20 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/14 11:36:17 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_lst(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		if (((t_parsing *)tmp->content)->to_del)
			ft_lstdel_here(lst, tmp, (void *)free_parsing_node);
		tmp = next;
	}
}

t_list	*prepare_node(t_list *node)
{
	((t_parsing *)node->content)->cmd = malloc(sizeof(char *) * 2);
	((t_parsing *)node->content)->cmd[0] = ((t_parsing *)node->content)->arg;
	((t_parsing *)node->content)->cmd[1] = NULL;
	((t_parsing *)node->content)->arg = NULL;
	return (node);
}

void	stack_cmd_args(t_shell_memory *data, t_list *lst)
{
	t_list	*save;

	while (lst)
	{
		while (lst && ((t_parsing *)lst->content)->token != COMMAND)
			lst = lst->next;
		if (((t_parsing *)lst->content)->token == COMMAND)
		{
			save = prepare_node(lst);
			lst = lst->next;
			while (lst && ((t_parsing *)lst->content)->token != PIPE)
			{
				if (((t_parsing *)lst->content)->token == COMMAND)
				{
					((t_parsing *)save->content)->cmd = ft_tabadd_back(((t_parsing *)save->content)->cmd, ft_strdup(((t_parsing *)lst->content)->arg));
					((t_parsing *)lst->content)->to_del = 1;
				}
				lst = lst->next;
			}
		}
	}
	clear_lst(&data->parsing_lst);
}
