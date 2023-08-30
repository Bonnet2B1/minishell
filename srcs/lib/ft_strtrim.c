/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:57:26 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/24 17:57:26 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	getstart(const char *s, const char *set)
{
	int	start;

	start = 0;
	while (ft_strchr(set, s[start]) && *s)
		start++;
	return (start);
}

static int	getend(const char *s, const char *set)
{
	int	end;

	end = ft_strlen(s);
	while (ft_strrchr(set, s[end]))
		end--;
	return (end - getstart(s, set) + 1);
}

char	*ft_strtrim(const char *s, const char *set)
{
	char	*str;

	if (!s)
		return (NULL);
	str = ft_substr(s, getstart(s, set), getend(s, set));
	free((char *)s);
	return (str);
}
