/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:04:42 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/20 21:58:16 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	current_cmd_init(t_shell_memory *data)
{
	data->current_cmd = malloc(sizeof(t_current_cmd));
	data->current_cmd->cmd_line_split = ft_split_white_space(data->cmd_line);
}
