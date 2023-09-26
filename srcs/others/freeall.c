/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:10:56 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/26 17:21:29 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*freeall(t_shell_memory *data)
{
	if (!data)
		return (NULL);
	if (data->input_line)
		data->input_line = freetab(data->input_line);
	if (data->env)
		data->env = freetab(data->env);
	if (data->cmd_line_split)
		data->cmd_line_split = freetab(data->cmd_line_split);
	if (data->parsing_lst)
		ft_lstclear(&data->parsing_lst, (void *)free_parsing_node);
	if (data->exec_lst)
		ft_lstclear(&data->exec_lst, (void *)free_exec_node);
	if (data->paths)
		data->paths = freetab(data->paths);
	if (data->cmd_path)
		free(data->cmd_path);
	return (NULL);
}
