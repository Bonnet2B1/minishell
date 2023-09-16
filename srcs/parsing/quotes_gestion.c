/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:01:23 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/16 20:38:35 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(char **line)
{
	int	i;

	line[1] = malloc(sizeof(char) * (ft_strlen(line[0]) + 1));
	i = -1;
	while (line[0][++i])
		line[1][i] = '0';
	line[1][i] = '\0';
}

int	quotes_gestion(char **line)
{
	int i;
	char quote;

	initialize(line);
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
		return (printf("minishell: syntax error near expected token `%c'\n", quote), 0);
	else
		return (1);
}
