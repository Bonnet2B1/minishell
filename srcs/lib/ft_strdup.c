/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:13:13 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/11 17:04:08 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;

	i = -1;
	dup = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (NULL);
	while (src[++i])
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}
