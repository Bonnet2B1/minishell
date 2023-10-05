/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:17:49 by edelarbr          #+#    #+#             */
/*   Updated: 2022/10/31 18:17:49 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(t_shell_memory *data, char const *s,
		unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;
	size_t	slen;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	if (slen - start < len)
		len = slen - start;
	cpy = calloc_tuning(&data->malloc_chain, sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (len-- && s[start])
		cpy[i++] = s[start++];
	cpy[i] = '\0';
	return (cpy);
}
