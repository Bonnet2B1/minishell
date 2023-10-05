/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:43:08 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/06 01:32:18 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_attributs(t_shell_memory *data, t_list *parsing_lst,
	t_parsing *parsing_node, t_exec *new_exec_node)
{
	if (parsing_node->token == COMMAND)
	{
		new_exec_node->cmd = ft_tabdup(data, parsing_node->cmd);
		parsing_node->to_del = 1;
	}
	if (parsing_node->token == REDIR_IN)
	{
		new_exec_node->in_struct = parsing_lst->content;
		if (parsing_node->open_error == 1)
			new_exec_node->open_error = 1;
	}
	if (parsing_node->token == REDIR_OUT)
	{
		new_exec_node->out_struct = parsing_lst->content;
		if (parsing_node->open_error == 1)
			new_exec_node->open_error = 1;
	}
	if (parsing_node->token == REDIR_APPEND)
	{
		new_exec_node->out_struct = parsing_lst->content;
		if (parsing_node->open_error == 1)
			new_exec_node->open_error = 1;
	}
}

void	setup_execution_lst(t_shell_memory *data, t_list *parsing_lst)
{
	t_exec	*new_exec_node;

	while (parsing_lst)
	{
		new_exec_node = create_execution_node(data);
		if (((t_parsing *)parsing_lst->content)->token == PIPE)
		{
			new_exec_node->in_struct = parsing_lst->content;
			parsing_lst = parsing_lst->next;
		}
		while (parsing_lst
			&& ((t_parsing *)parsing_lst->content)->token != PIPE)
		{
			join_attributs(data, parsing_lst,
				((t_parsing *)parsing_lst->content), new_exec_node);
			parsing_lst = parsing_lst->next;
		}
		if (parsing_lst && ((t_parsing *)parsing_lst->content)->token == PIPE
			&& new_exec_node->out_struct == NULL)
			new_exec_node->out_struct = parsing_lst->content;
		if (!new_exec_node->cmd)
			new_exec_node->execute = 0;
		ft_lstadd_back(&data->exec_lst, ft_lstnew(data, new_exec_node));
	}
	epure_lst(&data->parsing_lst);
}
