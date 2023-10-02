/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:05:06 by gloms             #+#    #+#             */
/*   Updated: 2023/10/02 18:28:46 by edelarbr         ###   ########.fr       */
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

void	ft_echo(t_shell_memory *data, char  **args)
{
	int	ac;
	int	i;

	i = 0;
	ac = ft_tablen(args);
	if (ac == 1)
		return (write (1, "\n", 1), free_n_exit(data, 0));
	else if (ac == 2 && !ft_strcmp(args[1], "-n"))
		return (free_n_exit(data, 0));
	else if (ac > 2 && !ft_strcmp(args[1], "-n"))
	{
		print_no_nl(args, ac);
		free_n_exit(data, 0);
	}
	while (args[++i] && i < ac - 1)
		printf("%s ", args[i]);
	printf("%s\n", args[i]);
	free_n_exit(data, 0);
}
