/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbiddens_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:41:53 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/06 00:26:19 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	forbiddens_chars(t_shell_memory *data, char **input_line)
{
	int	i;

	i = -1;
	while (input_line[0][++i])
	{
		if (input_line[1][i] == '0' && (input_line[0][i] == ';'
				|| input_line[0][i] == '\\' || input_line[0][i] == '('
				|| input_line[0][i] == ')'))
		{
			printf("minishell: syntax error near unexpected token `%c\'\n",
				input_line[0][i]);
			data->exit_code = 258;
			return (1);
		}
		if ((input_line[1][i] == '0' && input_line[0][i] == '&'
				&& input_line[0][i + 1] == '&') || (input_line[1][i] == '0'
				&& input_line[0][i] == '|' && input_line[0][i + 1] == '|'))
		{
			printf("minishell: syntax error near unexpected token \"%c%c\"\n",
				input_line[0][i], input_line[0][i + 1]);
			data->exit_code = 258;
			return (1);
		}
	}
	return (0);
}
