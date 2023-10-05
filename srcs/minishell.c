/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:32:39 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/05 22:22:43 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reader(t_shell_memory *data)
{
	char *temp;

	data->input_line = calloc_tuning(&data->malloc_chain, sizeof(char *) * 3);
	while (1)
	{
		temp = readline("minishell-3.2$ ");
		data->input_line[0] = ft_strdup(data, temp);
		free(temp);
		if (!data->input_line[0])
		{
			printf("\033[1A\033[15Cexit\n");
			return ;
		}
		data_init(data);
		add_history(data->input_line[0]);
		if (parsing(data))
			execution(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell_memory	data;

	(void)argc;
	(void)argv;
	ft_signal(ON);
	if (!env || !env[0])
		return (printf("Error: no environment\n"));
	data.malloc_chain = NULL;
	data.env = ft_tabdup(&data, env);
	reader(&data);
	free_n_exit(&data, 0);
}
