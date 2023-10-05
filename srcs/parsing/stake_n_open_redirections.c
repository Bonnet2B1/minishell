/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stake_n_open_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:47:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/05 01:52:50 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_to_redir_functions(t_shell_memory *data, t_list **lst)
{
	if (((t_parsing *)(*lst)->content)->token == REDIR_IN)
		stake_redir_in(data, (*lst));
	else if (((t_parsing *)(*lst)->content)->token == REDIR_OUT)
		stake_redir_out(data, (*lst));
	else if (((t_parsing *)(*lst)->content)->token == REDIR_APPEND)
		stake_redir_append(data, (*lst));
	else if (((t_parsing *)(*lst)->content)->token == HERE_DOC)
	{
		if (!(*lst)->next
			|| ((t_parsing *)(*lst)->next->content)->token != FILEE)
			redir_error(data, (*lst));
		else
		{
			((t_parsing *)(*lst)->content)->arg
				= ft_strdup(data, ((t_parsing *)(*lst)->next->content)->arg);
			ft_lstdel_here(&data->parsing_lst, (*lst)->next,
				NULL);
		}
	}
}

void	stake_n_open_files(t_shell_memory *data, t_list *lst)
{
	while (lst)
	{
		while (lst && ((t_parsing *)lst->content)->token != PIPE
			&& !data->fatal_error)
		{
			redir_to_redir_functions(data, &lst);
			if (((t_parsing *)lst->content)->open_error == 1)
				break ;
			lst = lst->next;
		}
		while (lst && ((t_parsing *)lst->content)->token != PIPE)
			lst = lst->next;
		if (lst && ((t_parsing *)lst->content)->token == PIPE)
			lst = lst->next;
	}
}
