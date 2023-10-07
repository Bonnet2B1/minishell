/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:01:23 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/07 17:16:56 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_shell_memory *data, char **line)
{
	int	i;

	line[1] = calloc_tuning(&data->malloc_chain,
			sizeof(char) * (ft_strlen(line[0]) + 1));
	i = -1;
	while (line[0][++i])
		line[1][i] = '0';
	line[1][i] = '\0';
}

int	quotes_gestion(t_shell_memory *data, char **line)
{
	int		i;
	char	quote;

	initialize(data, line);
	quote = '0';
	i = -1;
	while (line[0][++i])
	{
		line[1][i] = quote;
		if (quote == '0' && (line[0][i] == '\'' || line[0][i] == '\"'))
		{
			quote = line[0][i];
			line[1][i] = 'o';
		}
		else if (quote != '0' && line[0][i] == quote)
		{
			quote = '0';
			line[1][i] = 'c';
		}
	}
	if (quote != '0')
		return (ft_putstr_fd("minishell: syntax error near expected token `",
				2), ft_putchar_fd(quote, 2), ft_putstr_fd("'\n", 2), 0);
	return (1);
}
