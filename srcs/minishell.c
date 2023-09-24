/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:32:39 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/24 19:37:41 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reader(t_shell_memory *data)
{
	while (1)
	{
		data->input_line = malloc(sizeof(char *) * 3);
		data->input_line[0] = readline("\033[1;35mminishell\033[0m-\033[1;31m3.2$ \033[0m");
		if (!data->input_line[0])
			break ;
		add_history(data->input_line[0]);
		data_init(data);
 		parsing(data);
		execution(data);
		freetab(data->input_line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell_memory	data;

	(void)argc;
	(void)argv;

	ft_signal(1);
	data.env = ft_tabdup(env);
	reader(&data);
}
