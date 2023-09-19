/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:00:50 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/18 16:08:23 by edelarbr         ###   ########.fr       */
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
	if (((t_exec *)exec_node->content)->out_struct->token == PIPE
		&& ((t_exec *)exec_node->content)->out_struct == ((t_exec *)exec_node->next->content)->in_struct)
	{
		((t_exec *)exec_node->content)->out_fd = ((t_exec *)exec_node->content)->out_struct->pipe_fd[INPIPE];
		((t_exec *)exec_node->next->content)->in_fd = ((t_exec *)exec_node->next->content)->in_struct->pipe_fd[OUTPIPE];
	}
	else if (((t_exec *)exec_node->content)->out_struct->token == PIPE && ((t_exec *)exec_node->next->content)->cmd)
	{
		((t_exec *)exec_node->content)->out_struct = NULL;
		((t_exec *)exec_node->content)->out_fd = -1;
	}
}

void	pipe_prev(t_list *exec_node)
{
	if (((t_exec *)exec_node->content)->in_struct->token == PIPE
		&& ((t_exec *)exec_node->content)->in_struct == ((t_exec *)exec_node->prev->content)->out_struct)
	{
		((t_exec *)exec_node->content)->in_fd = ((t_exec *)exec_node->content)->in_struct->pipe_fd[OUTPIPE];
		((t_exec *)exec_node->prev->content)->out_fd = ((t_exec *)exec_node->prev->content)->out_struct->pipe_fd[INPIPE];
	}
	else if (((t_exec *)exec_node->content)->in_struct->token == PIPE && ((t_exec *)exec_node->prev->content)->cmd)
	{
		((t_exec *)exec_node->content)->in_struct = NULL;
		((t_exec *)exec_node->content)->in_fd = -1;
	}
}

void	setup_fd(t_shell_memory *data, t_list *exec_lst)
{
	pipe_pipes(data->parsing_lst);
	while (exec_lst)
	{
		if (exec_lst->next)
			pipe_next(exec_lst);
		if (exec_lst->prev)
			pipe_prev(exec_lst);
		if (((t_exec *)exec_lst->content)->in_struct && (((t_exec *)exec_lst->content)->in_struct->token == REDIR_IN || ((t_exec *)exec_lst->content)->in_struct->token == REDIR_APPEND || ((t_exec *)exec_lst->content)->in_struct->token == REDIR_OUT))
			((t_exec *)exec_lst->content)->in_fd = ((t_exec *)exec_lst->content)->in_struct->file_fd;
		if (((t_exec *)exec_lst->content)->out_struct && (((t_exec *)exec_lst->content)->out_struct->token == REDIR_IN || ((t_exec *)exec_lst->content)->out_struct->token == REDIR_APPEND || ((t_exec *)exec_lst->content)->out_struct->token == REDIR_OUT))
			((t_exec *)exec_lst->content)->out_fd = ((t_exec *)exec_lst->content)->out_struct->file_fd;
		exec_lst = exec_lst->next;
	}
}
