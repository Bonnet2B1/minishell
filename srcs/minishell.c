/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:32:39 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/27 17:29:29 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reader(t_shell_memory *data)
{
	while (1)
	{
		data->input_line = readline("minishell> ");
		add_history(data->input_line);
		input_gestion(data);
		free(data->input_line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell_memory	data;

	(void)argv;
	if (argc != 1)
	{
		while (argc--)
			printf("%s\n", *argv++);
	}
	data.env = env;
	reader(&data);
}
