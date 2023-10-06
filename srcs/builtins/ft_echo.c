/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:05:06 by gloms             #+#    #+#             */
/*   Updated: 2023/10/06 17:01:20 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (i);
}

void	ft_echo(t_shell_memory *data, char **args)
{
	int	i;

	i = 1;
	while (is_flag(args[i]))
		i++;
	if (i > 1)
	{
		while (args[i])
		{
			printf("%s", args[i++]);
			if (args[i])
				printf(" ");
		}
	}
	else
	{
		while (args[i])
		{
			printf("%s", args[i++]);
			if (args[i])
				printf(" ");
		}
		printf("\n");
	}
	free_n_exit(data, 0);
}
