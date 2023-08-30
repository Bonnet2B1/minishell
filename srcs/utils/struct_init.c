/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:04:42 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/30 21:18:51 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	data_init(t_shell_memory *data)
{
	data->parsing_lst = NULL;
	data->working_node = NULL;
	data->cmd_line_split = NULL;
}

t_split	*create_split_node(char *arg)
{
	t_split	*new_node;

	new_node = malloc(sizeof(t_split));
	if (!new_node)
		return (perror("Malloc error :"), NULL);
	new_node->arg = arg;
	return (new_node);
}
