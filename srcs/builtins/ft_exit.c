/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:08 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 23:35:57 by edelarbr         ###   ########.fr       */
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

int	check_num(t_shell_memory *data, char **cmd, int i)
{
	if (cmd[1][i] < '0' || cmd[1][i] > '9')
	{
		if (need_exec_to_exec(data))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				cmd[1]);
			return (free_n_exit(data, data->exit_code = 255), 255);
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				cmd[1]);
			return (1);
		}
	}
	return (0);
}

int	ft_exit(t_shell_memory *data, char **cmd)
{
	int	i;

	if (!cmd[1] && need_exec_to_exec(data))
		return (printf("exit\n"), free_n_exit(data, 0), 0);
	else if (!cmd[1] && !need_exec_to_exec(data))
		return (0);
	i = -1;
	while (cmd[1][++i])
	{
		if (i == 0 && (cmd[1][i] == '-' || cmd[1][i] == '+'))
			continue ;
		if (check_num(data, cmd, i) == 1)
			return (1);
	}
	if (cmd[1] && !cmd[2])
	{
		printf("exit\n");
		free_n_exit(data, ft_atoi(cmd[1]));
		return (ft_atoi(cmd[1]));
	}
	if (cmd[0] && cmd[1] && cmd[2])
		return (printf("exit\nminishell: exit: too many arguments\n"), 1);
	return (0);
}
