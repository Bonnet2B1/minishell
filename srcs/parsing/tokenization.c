/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:40:34 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/02 18:40:53 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenization(t_list *lst)
{
	while (lst)
	{
		if (!ft_strncmp(((t_parsing *)lst->content)->arg, "|", 1))
			((t_parsing *)lst->content)->token = PIPE;
		else if (!ft_strncmp(((t_parsing *)lst->content)->arg, ">>", 2))
			((t_parsing *)lst->content)->token = REDIR_APPEND;
		else if (!ft_strncmp(((t_parsing *)lst->content)->arg, ">", 1))
			((t_parsing *)lst->content)->token = REDIR_OUT;
		else if (!ft_strncmp(((t_parsing *)lst->content)->arg, "<<", 2))
			((t_parsing *)lst->content)->token = HERE_DOC;
		else if (!ft_strncmp(((t_parsing *)lst->content)->arg, "<", 1))
			((t_parsing *)lst->content)->token = REDIR_IN;
		else if (lst->prev
			&& (((t_parsing *)lst->prev->content)->token == REDIR_IN
				|| ((t_parsing *)lst->prev->content)->token == REDIR_OUT
				|| ((t_parsing *)lst->prev->content)->token == HERE_DOC
				|| ((t_parsing *)lst->prev->content)->token == REDIR_APPEND))
			((t_parsing *)lst->content)->token = FILEE;
		else
			((t_parsing *)lst->content)->token = COMMAND;
		lst = lst->next;
	}
}
