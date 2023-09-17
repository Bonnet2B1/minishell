/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:10:13 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/17 22:07:25 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_rm_quotes(char *str)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == 'o' || str[i] == 'c')
			continue ;
		len++;
	}
	return (len);
}

void	rm_quotes(char **line)
{
	int		i;
	int		j;
	char	*new_line;
	char	*new_quotes;

	new_line = malloc(sizeof(char) * (ft_strlen_rm_quotes(line[1]) + 1));
	new_quotes = malloc(sizeof(char) * (ft_strlen_rm_quotes(line[1]) + 1));
	i = -1;
	j = 0;
	while (line[1][++i])
	{
		if (line[1][i] == 'o' || line[1][i] == 'c')
			continue ;
		new_line[j] = line[0][i];
		new_quotes[j] = line[1][i];
		j++;
	}
	new_line[j] = '\0';
	new_quotes[j] = '\0';
	free(line[0]);
	free(line[1]);
	line[0] = new_line;
	line[1] = new_quotes;
}
