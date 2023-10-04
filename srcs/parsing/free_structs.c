/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:46:28 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 23:13:06 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_parsing_node(t_parsing *node)
{
	int	i;

	if (!node)
		return (NULL);
	if (node->arg)
		free(node->arg);
	i = -1;
	if (node->cmd)
	{
		while (node->cmd[++i])
			free(node->cmd[i]);
		free(node->cmd);
	}
	free(node);
	return (NULL);
}

void	*free_exec_node(t_exec *node)
{
	int	i;

	i = -1;
	if (!node)
		return (NULL);
	if (node->cmd)
	{
		while (node->cmd[++i])
			free(node->cmd[i]);
		free(node->cmd);
	}
	if (node->in_struct)
		free_parsing_node(node->in_struct);
	if (node->out_struct)
		free_parsing_node(node->out_struct);
	return (NULL);
}
