/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:10:19 by edelarbr          #+#    #+#             */
/*   Updated: 2022/11/23 15:10:19 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	defsign(t_shell_memory *data, long *n, int *s_len, char **s)
{
	int	n_cpy;

	n_cpy = *n;
	while (n_cpy / 10)
	{
		n_cpy /= 10;
		(*s_len)++;
	}
	if (*n < 0)
		(*s_len)++;
	*s = calloc_tuning(&data->malloc_chain, sizeof(char) * (*s_len + 2));
	if (!*s)
		return ;
	(*s)[*s_len + 1] = '\0';
}

char	*ft_itoa(t_shell_memory *data, int n)
{
	int		s_len;
	char	*s;
	long	nb;

	nb = n;
	s_len = 0;
	defsign(data, &nb, &s_len, &s);
	if (!s)
		return (NULL);
	if (nb == 0)
		s[0] = '0';
	if (nb < 0)
	{
		s[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		s[s_len--] = (nb % 10) + 48;
		nb /= 10;
	}
	return (s);
}
