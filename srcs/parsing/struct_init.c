/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:04:42 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/11 19:27:19 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	data_init(t_shell_memory *data)
{
	data->parsing_lst = NULL;
	data->cmd_line_split = NULL;
	data->error = 0;
}

t_split	*create_split_node(char *arg)
{
	t_split	*new_node;

	new_node = malloc(sizeof(t_split));
	if (!new_node)
		return (perror("Malloc error :"), NULL);
	new_node->to_del = 0;
	new_node->token = 0;
	new_node->arg = arg;
	new_node->cmd = NULL;
	return (new_node);
}
