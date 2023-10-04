/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:00:50 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 20:22:22 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_pipes(t_list *parsing_lst)
{
	while (parsing_lst)
	{
		if (((t_parsing *)parsing_lst->content)->token == PIPE)
			pipe(((t_parsing *)parsing_lst->content)->pipe_fd);
		parsing_lst = parsing_lst->next;
	}
}

void	pipe_next(t_list *exec_node)
{
	if (((t_exec *)exec_node->content)->out_struct->token == PIPE)
	{
		((t_exec *)exec_node->content)->out_fd
			= ((t_exec *)exec_node->content)->out_struct->pipe_fd[INPIPE];
		((t_exec *)exec_node->next->content)->in_fd
			= ((t_exec *)exec_node->next->content)->in_struct->pipe_fd[OUTPIPE];
	}
}

void	pipe_prev(t_list *exec_node)
{
	if (((t_exec *)exec_node->content)->in_struct->token == PIPE)
	{
		((t_exec *)exec_node->content)->in_fd
			= ((t_exec *)exec_node->content)->in_struct->pipe_fd[OUTPIPE];
		((t_exec *)exec_node->prev->content)->out_fd
			= ((t_exec *)exec_node->prev->content)->out_struct->pipe_fd[INPIPE];
	}
}

void	setup_fd(t_shell_memory *data, t_list *exec_lst)
{
	t_exec	*node;

	pipe_pipes(data->parsing_lst);
	while (exec_lst)
	{
		node = exec_lst->content;
		if (node->in_struct
			&& (node->in_struct->token == PIPE))
			node->in_fd = node->in_struct->pipe_fd[OUTPIPE];
		if (node->out_struct
			&& (node->out_struct->token == PIPE))
			node->out_fd = node->out_struct->pipe_fd[INPIPE];
		if (node->in_struct
			&& (node->in_struct->token == REDIR_IN
				|| node->in_struct->token == REDIR_APPEND
				|| node->in_struct->token == REDIR_OUT))
			node->in_fd = node->in_struct->file_fd;
		if (node->out_struct
			&& (node->out_struct->token == REDIR_IN
				|| node->out_struct->token == REDIR_APPEND
				|| node->out_struct->token == REDIR_OUT))
			node->out_fd = node->out_struct->file_fd;
		exec_lst = exec_lst->next;
	}
}
