/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:32:39 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/31 00:08:43 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reader(t_shell_memory *data)
{
	while (1)
	{
		data->input_line = readline("minishell-1.0$ ");
		add_history(data->input_line);
		input_gestion(data);
		data_init(data);
		free(data->input_line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell_memory	data;

	(void)argc;
	(void)argv;
	data.env = env;
	reader(&data);
}
