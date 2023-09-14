/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:58:41 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/14 19:19:11 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipes(t_list *parsing_lst)
{
	t_parsing	*parsing_node;

	while (parsing_lst)
	{
		parsing_node = parsing_lst->content;
		if (parsing_node->token == PIPE)
		{
			close(parsing_node->pipe_fd[INPIPE]);
			close(parsing_node->pipe_fd[OUTPIPE]);
		}
		parsing_lst = parsing_lst->next;
	}
}
