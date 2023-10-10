/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:05:06 by gloms             #+#    #+#             */
/*   Updated: 2023/10/10 16:34:20 by gloms            ###   ########.fr       */
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

void	do_nl(char **args)
{
	if (!&args[1] || !args[1])
		printf("\n");
	if (!is_flag(args[1]))
		printf("\n");
}

void	ft_echo(t_shell_memory *data, char **args)
{
	int	i;

	i = 1;
	while (&args[i] && args[i] && is_flag(args[i]))
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
	}
	do_nl(args);
	free_n_exit(data, 0);
}
