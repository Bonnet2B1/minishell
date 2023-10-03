/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:00:33 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/02 23:00:37 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_remove(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		if (is_between_quote(temp->content, 0) != '0')
			temp->content = ft_substr(temp->content, 1,
					ft_strlen(temp->content) - 2);
		temp = temp->next;
	}
}

char	is_between_quote(char *str, int index)
{
	char	quote;
	int		i;

	quote = '0';
	i = 0;
	if (!str)
		return (1);
	while (str[i] && i <= index)
	{
		if (quote == '0' && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote != '0' && str[i] == quote)
			quote = '0';
		i++;
	}
	return (quote);
}

char	check_quote(char *str)
{
	char	quote;
	int		i;

	quote = '0';
	i = 0;
	while (str[i])
	{
		if (quote == '0' && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = '0';
		i++;
	}
	if (quote != '0')
		printf("Minishell : syntax error near unexpected token \'%c\'\n", quote);
	return (quote);
}
