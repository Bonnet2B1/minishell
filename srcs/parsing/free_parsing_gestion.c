/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing_gestion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:46:28 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/10 22:21:31 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_split_node(t_split *node)
{
	int	i;

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
