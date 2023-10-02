/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:08 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/01 21:24:12 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	need_exec_to_exec(t_shell_memory *data)
{
	t_exec	*node;

	node = data->exec_lst->content;
	if (node->execute == 1 && node->cmd
		&& ft_strncmp(node->cmd[0], "exit", 5) == 0
		&& data->exec_lst->next == NULL && data->exec_lst->prev == NULL)
		return (1);
	else
		return (0);
}

int	ft_exit(t_shell_memory *data, char **cmd)
{
	int	i;

	if (!cmd[1] && need_exec_to_exec(data))
		return (printf("exit\n"), free_n_exit(data, 0), 0);
	else if (!cmd[1] && !need_exec_to_exec(data))
		return 0;
	i = -1;
	while (cmd[1][++i])
	{
		if (cmd[1][i] == '-' && i == 0)
			continue ;
		if (cmd[1][i] < '0' || cmd[1][i] > '9')
		{
			if (need_exec_to_exec(data))
				return (printf("exit\nminishell: exit: %s: numeric argument required\n", cmd[1]), free_n_exit(data, data->exit_code = 255), 255);
			else
				return (printf("minishell: exit: %s: numeric argument required\n", cmd[1]), 1);
		}
	}
	if (cmd[1] && !cmd[2])
		return (printf("exit\n"), free_n_exit(data, ft_atoi(cmd[1])) , ft_atoi(cmd[1]));
	if (cmd[0] && cmd[1] && cmd[2])
		return (printf("exit\nminishell: exit: too many arguments\n"), 1);
	return (0);
}

// void	ft_exit(t_shell_memory *data, char **cmd)
// {
// 	int	exit_code;

// 	if (!cmd[1])
// 		free_n_exit(data, 0);
// 	if (cmd[1] && cmd[2])
// 	{
// 		printf("minishell: exit: too many arguments\n");
// 		return ;
// 	}
// 	exit_code = ft_atoi(cmd[1]);
// 	if (exit_code < 0 || exit_code > 255)
// 	{
// 		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
// 		free_n_exit(data, 2);
// 	}
// 	else
// 		free_n_exit(data, exit_code);
// }
