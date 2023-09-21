/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:41:14 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/21 19:51:33 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tabadd_back(char **tab, char *new_str)
{
	int		len;
	int		i;
	char	**new_tab;

	if (!new_str)
		return (NULL);
	// if (!tab)
	// {
	// 	new_tab = malloc(sizeof(char *) * 2);
	// 	new_tab[0] = new_str;
	// 	new_tab[1] = NULL;
	// 	return (new_tab);
	// }
	len = 0;
	while (tab && tab[len])
		len++;
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		new_tab[i] = tab[i];
	new_tab[i] = new_str;
	new_tab[i + 1] = NULL;
	free(tab);
	return (new_tab);
}
