/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:32:39 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 19:42:26 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reader(t_shell_memory *data)
{
	while (1)
	{
		data->input_line = malloc(sizeof(char *) * 3);
		data->input_line[0] = readline("minishell-3.2$ ");
		if (!data->input_line[0])
			break ;
		data_init(data);
		add_history(data->input_line[0]);
		if (parsing(data))
			execution(data);
		freetab(data->input_line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell_memory	data;

	(void)argc;
	(void)argv;
	ft_signal(ON);
	data.env = ft_tabdup(env);
	reader(&data);
}
