/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stake_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:29:20 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/31 01:22:01 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	stake_cmd_args(t_shell_memory *data, t_list *lst)
{
	t_list	*new;

	while (lst)
	{
		new = ft_lstnew((t_split *)create_split_node(NULL));
		((t_split *)new->content)->token = COMMAND;
		((t_split *)new->content)->cmd = malloc(sizeof(char *));
		((t_split *)new->content)->cmd[0] = NULL;
		while (((t_split *)lst->content)->token != PIPE && lst)
		{
			if (((t_split *)lst->content)->token == COMMAND)
			{
				((t_split *)new->content)->cmd = ft_tabadd_back(((t_split *)
							new->content)->cmd, ((t_split *)lst->content)->arg);
				if (lst->next)
				{
					lst = lst->next;
					ft_lstdel_here(&data->parsing_lst, lst->prev);
				}
				else
					break ;
			}
			else
				lst = lst->next;
		}
		print_tab(((t_split *)new->content)->cmd);
		lst = lst->next;
	}
}
