/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:48:12 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/19 20:17:49 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_ast(t_shell_memory *data)
{
	int		i;
	// t_node	*node;
	// int		left_counter;

	printf("cmd_line_split:\n");
	i = -1;
	while (data->current_cmd->cmd_line_split[++i])
		printf("%d : %s\n", i, data->current_cmd->cmd_line_split[i]);
	// left_counter = 0;
	// if (data->current_cmd->first_node)
	// {
	// 	node = data->current_cmd->first_node;
	// 	printf("ast:\n");
	// 	while (1)
	// 	{
	// 		i = -1;
	// 		while (++i < left_counter)
	// 			node = node->left;
	// 		while (node)
	// 		{
	// 			if (node->type == PIPE)
	// 			{
	// 				printf("  PIPE -----");
	// 				printf("   |\n   |\n   |\n");
	// 			}
	// 			if (node->type == COMMAND)
	// 			{
	// 				printf("COMMAND\n%s\n", node->cmd_line_split);
	// 			}
	// 		}
	// 		node = data->current_cmd->first_node;
	// 		left_counter++;
	// 	}
	// }
}
