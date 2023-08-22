/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:32:39 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/22 21:59:42 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_gestion(t_shell_memory *data)
{
	current_cmd_init(data);
	ast(data);
	print_ast(data);
}

void	reader(t_shell_memory *data)
{
	while (1)
	{
		data->cmd_line = readline("minishell> ");
		add_history(data->cmd_line);
		input_gestion(data);
		free(data->cmd_line);
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
	data.ev = env;
	reader(&data);
}
