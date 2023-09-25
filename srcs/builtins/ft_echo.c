/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:05:06 by gloms             #+#    #+#             */
/*   Updated: 2023/09/25 13:58:01 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_no_nl(char **args, int ac)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (i == ac - 1)
		{
			printf("%s", args[i]);
			break ;
		}
		printf("%s ", args[i]);
		i++;
	}
	return ;
}

int	lentab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_echo(char **args)
{
	int	ac;
	int	i;

	i = 0;
	ac = lentab(args);
	if (ac == 1)
		return (write (1, "\n", 1), 0);
	else if (ac == 2 && !ft_strcmp(args[1], "-n"))
		return (0);
	else if (ac > 2 && !ft_strcmp(args[1], "-n"))
	{
		print_no_nl(args, ac);
		return (0);
	}
	while (args[++i] && i < ac - 1)
		printf("%s ", args[i]);
	printf("%s\n", args[i]);
	return (0);
}
