/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:04:31 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/07 19:13:42 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**rm_tab_index(t_shell_memory *data, char **tab, int index)
{
	char	**new_tab;
	int		i;
	int		j;

	if (!tab)
		return (NULL);
	if (index > ft_tablen(tab) - 1)
		return (tab);
	new_tab = calloc_tuning(&data->malloc_chain, sizeof(char *)
			* ft_tablen(tab));
	if (!new_tab)
		return (NULL);
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (i == index)
			i++;
		else
			new_tab[j++] = tab[i++];
	}
	new_tab[j] = NULL;
	return (new_tab);
}

char	there_is_banned_char(char *str)
{
	int	i;

	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	i = -1;
	while (str[++i])
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| str[i] == '_'))
			return (1);
	return (0);
}

int	env_find_correlation(t_shell_memory *data, char **env, char *str)
{
	char	*prompt;
	int		i;

	prompt = ft_strjoin(data, str, "=");
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(prompt, env[i], ft_strlen(prompt)) == 0)
			return (i);
	}
	return (-1);
}

int	ft_unset(t_shell_memory *data, t_list *node, char **cmd)
{
	int	i;
	int	exit_value;

	exit_value = 0;
	i = 0;
	if (node->prev || node->next)
		return (exit_value);
	while (cmd[++i])
	{
		if (there_is_banned_char(cmd[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_value = 1;
		}
		else if (env_find_correlation(data, data->env, cmd[i]) != -1)
			data->env = rm_tab_index(data, data->env,
					env_find_correlation(data, data->env, cmd[i]));
	}
	return (exit_value);
}
