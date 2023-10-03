/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:52:56 by gloms             #+#    #+#             */
/*   Updated: 2023/10/03 01:29:11 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_letter(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_valid(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if ((c >= '0' && c <= '9') || c == '=')
		return (1);
	return (0);
}

int	ft_srch(char *s)
{
	int	i;
	int	eq;

	eq = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && eq == 0)
			eq = 1;
		else if (!is_valid(s[i]) && eq == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*rtn_arg(char *str)
{
	int		i;
	char	*new;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	if (i > 0)
	{
		new = ft_substr(str, 0, i);
		return (new);
	}
	return (NULL);
}

void	tab_print(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}
