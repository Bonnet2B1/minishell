/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbiddens_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:41:53 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/07 16:57:30 by edelarbr         ###   ########.fr       */
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
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putchar_fd(input_line[0][i], 2);
			ft_putstr_fd("'\n", 2);
			data->exit_code = 258;
			return (1);
		}
		if ((input_line[1][i] == '0' && input_line[0][i] == '&'
				&& input_line[0][i + 1] == '&') || (input_line[1][i] == '0'
				&& input_line[0][i] == '|' && input_line[0][i + 1] == '|'))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putchar_fd(input_line[0][i], 2);
			ft_putchar_fd(input_line[0][i + 1], 2);
			ft_putstr_fd("'\n", 2);
			data->exit_code = 258;
			return (1);
		}
	}
	return (0);
}
