/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freetab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:24:03 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/24 20:35:19 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**freetab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (NULL);
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}
