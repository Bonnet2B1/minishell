/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:27:22 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/14 14:09:18 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strlen_rmchar(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			len++;
		i++;
	}
	return (len);
}

char	*ft_rmchar(char *str, char c)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen_rmchar(str, c) + 1);
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}
