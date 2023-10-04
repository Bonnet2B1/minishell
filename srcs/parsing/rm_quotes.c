/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:10:13 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 19:14:52 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*erase_quote(char *str, int *index_tab)
{
	char	*new;
	int		index_tab_len;
	int 	i;
	int 	j;
	int 	k;

	index_tab_len = 0;
	while (index_tab[index_tab_len] != -1)
		index_tab_len++;
	if (index_tab_len == 0)
		return (str);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1 - index_tab_len));
	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (i == index_tab[k])
		{
			i++;
			k++;
		}
		else
			new[j++] = str[i++];
	}
	new[ft_strlen(str) - index_tab_len] = '\0';
	free(str);
	return (new);
}

int	*quote_index(char *str, int *index_tab)
{
	char	quote;
	int		i;
	int		u;

	quote = 0;
	i = 0;
	u = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			index_tab[u++] = i;
		}
		else if (quote != 0 && str[i] == quote)
		{
			quote = 0;
			index_tab[u++] = i;
		}
		i++;
	}
	return (index_tab);
}

char	*quote_remove(char *str)
{
	int		*index_tab;
	int		i;
	char	*new;

	i = 0;
	index_tab = malloc(sizeof(int) * 100);
	while (i < 100)
		index_tab[i++] = -1;
	i = -1;
	index_tab = quote_index(str, index_tab);
	new = erase_quote(str, index_tab);
	free(index_tab);
	return (new);
}

void	rm_quotes(t_list *parsing_lst)
{
	t_parsing	*node;
	while (parsing_lst)
	{
		node = parsing_lst->content;
		node->arg = quote_remove(node->arg);
		parsing_lst = parsing_lst->next;
	}
}
