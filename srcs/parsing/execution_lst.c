/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:43:08 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/18 15:39:35 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_parsing_data(t_shell_memory *data, t_list *parsing_lst)
{
	t_exec	*new_exec_node;

	while (parsing_lst)
	{
		new_exec_node = create_execution_node();
		if (((t_parsing *)parsing_lst->content)->token == PIPE)
		{
			new_exec_node->in_struct = parsing_lst->content;
			parsing_lst = parsing_lst->next;
		}
		while (parsing_lst && ((t_parsing *)parsing_lst->content)->token != PIPE)
			{
			if (((t_parsing *)parsing_lst->content)->token == COMMAND)
			{
				new_exec_node->cmd = ft_tabdup(((t_parsing *)parsing_lst->content)->cmd);
				((t_parsing *)parsing_lst->content)->to_del = 1;
			}
			if (((t_parsing *)parsing_lst->content)->token == REDIR_IN)
				new_exec_node->in_struct = parsing_lst->content;
			if (((t_parsing *)parsing_lst->content)->token == REDIR_OUT)
				new_exec_node->out_struct = parsing_lst->content;
			if (((t_parsing *)parsing_lst->content)->token == REDIR_APPEND)
				new_exec_node->out_struct = parsing_lst->content;
			parsing_lst = parsing_lst->next;
		}
		if (parsing_lst)
		{
			if (((t_parsing *)parsing_lst->content)->token == PIPE && new_exec_node->out_struct == NULL)
				new_exec_node->out_struct = parsing_lst->content;
		}
		if (!new_exec_node->cmd)
			new_exec_node->execute = 0;
		ft_lstadd_back(&data->exec_lst, ft_lstnew(new_exec_node));

	}
	clear_lst(&data->parsing_lst);
}

void	setup_execution_lst(t_shell_memory *data, t_list *parsing_lst)
{
	(void)parsing_lst;
	get_parsing_data(data, data->parsing_lst);
}
