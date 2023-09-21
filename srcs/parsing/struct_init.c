/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:04:42 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/21 19:45:29 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	data_init(t_shell_memory *data)
{
	data->input_line[2] = NULL;
	data->parsing_lst = NULL;
	data->exec_lst = NULL;
	data->cmd_line_split = NULL;
	data->fatal_error = 0;
	data->paths = NULL;
}

t_parsing	*create_parsing_node(char *arg)
{
	t_parsing	*new_node;

	new_node = malloc(sizeof(t_parsing));
	if (!new_node)
		return (perror("Malloc"), NULL);
	new_node->to_del = 0;
	new_node->to_unlink = 0;
	new_node->token = NONE;
	new_node->arg = arg;
	new_node->cmd = NULL;
	return (new_node);
}

t_exec	*create_execution_node(void)
{
	t_exec *new_node;

	new_node = malloc(sizeof(t_exec));
	if (!new_node)
		return (perror("Malloc"), NULL);
	new_node->execute = 1;
	new_node->cmd = NULL;
	new_node->in_struct = NULL;
	new_node->out_struct = NULL;
	new_node->in_fd = 0;
	new_node->out_fd = 1;
	return (new_node);
}
