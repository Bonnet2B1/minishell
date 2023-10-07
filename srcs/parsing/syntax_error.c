/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:55:38 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/07 18:20:13 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_shell_memory *data, t_list *parsing_lst)
{
	t_parsing	*node;

	while (parsing_lst)
	{
		node = (t_parsing *)parsing_lst->content;
		if (node->token == PIPE && (!parsing_lst->prev
				|| (parsing_lst->next
					&& ((t_parsing *)parsing_lst->next->content)->token
					== PIPE)))
		{
			ft_putstr_fd(
				"minishell: syntax error near unexpected token `|'\n", 2);
			return (data->exit_code = 258);
		}
		else if (node->token == PIPE && !parsing_lst->next)
		{
			ft_putstr_fd(
				"minishell: syntax error near unexpected token `newline'\n", 2);
			return (data->exit_code = 258);
		}
		parsing_lst = parsing_lst->next;
	}
	return (0);
}
