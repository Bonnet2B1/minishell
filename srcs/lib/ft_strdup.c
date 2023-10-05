/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:13:13 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/05 01:55:18 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(t_shell_memory *data, const char *src)
{
	int		i;
	char	*dup;

	if (!src)
		return (NULL);
	i = -1;
	dup = calloc_tuning(&data->malloc_chain, sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (NULL);
	while (src[++i])
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}
