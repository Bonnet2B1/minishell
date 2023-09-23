/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:04:31 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/23 17:56:05 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **rm_tab_index(char **tab, int index)
{
	char	**new_tab;
	int		size;
	int		i;
	int		j;

	size = -1;
	while (tab && tab[++size])
		continue ;
	if (index > size)
		return (tab);
	new_tab = malloc(sizeof(char *) * size);
	if (!new_tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (j == index)
			j++;
		else
			tab[i++] = tab[j++];
	}
	new_tab[i - 1] = NULL;
	free(tab[index]);
	free(tab);
	return(new_tab);
}

char	there_is_banned_char(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if ((str[0] >= '0' && str[0] <= '9')
			|| !((str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| str[i] == '_'))
			return (1);
	return (0);
}

int	env_find_correlation(char **env, char *str)
{
	char	*prompt;
	int		i;

	prompt = ft_strjoin(str, "=");
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(prompt, env[i], ft_strlen(prompt)))
			return (free(prompt), i);
	}
	return (free(prompt), -1);
}

void	ft_unset(char **cmd, t_shell_memory *data)
{
	int	i;
	int	exit_value;

	exit_value = 0;
	i = 0;
	while (cmd[++i])
	{
		if (there_is_banned_char(cmd[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			exit_value = 1;
		}
		else if (env_find_correlation(data->env, cmd[i]) != -1)
			data->env = rm_tab_index(data->env, env_find_correlation(data->env, cmd[i]));
	}
	exit(exit_value);
}
