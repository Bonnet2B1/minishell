/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_or_whitespaces.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:25:38 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/29 23:34:05 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty_or_whitespaces(char *str)
{
	int	i;

	if (str[0] == '\0')
		return (1);
	i = -1;
	while (str[++i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
	}
	return (1);
}
