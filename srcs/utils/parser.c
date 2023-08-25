/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:13:02 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/26 00:54:39 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_gestion(t_shell_memory *data)
{
	int i;

	data->cmd_line_split = ft_split_white_space(data->input_line);
	i = -1;
	while (data->cmd_line_split[++i])
		ft_lstadd_back(&data->first,
			ft_lstnew(create_split_node(data->cmd_line_split[i])));
	free(data->cmd_line_split);
	data->node = data->first;
	while (data->node)
	{
		data->cmd_line_split = ft_split_keep_char(((t_split *)data->node->content)->arg, '|');
		i = -1;
		while (data->cmd_line_split[++i])
			printf("tab[%d] = %s\n", i, data->cmd_line_split[i]);
		break;
	}
}
