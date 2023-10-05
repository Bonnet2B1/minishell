/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:41:14 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/05 02:01:01 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tabadd_back(t_shell_memory *data, char **tab, char *new_str)
{
	int		len;
	int		i;
	char	**new_tab;

	if (!new_str)
		return (NULL);
	len = 0;
	while (tab && tab[len])
		len++;
	new_tab = calloc_tuning(&data->malloc_chain, sizeof(char *) * (len + 2));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		new_tab[i] = tab[i];
	new_tab[i] = new_str;
	new_tab[i + 1] = NULL;
	return (new_tab);
}
