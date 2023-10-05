/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:26:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/05 01:59:19 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	there_is_a_env_var(char **line)
{
	int	i;

	i = -1;
	while (line[0][++i])
	{
		if (line[0][i] == '$' && (ft_isenvchar(line[0][i + 1]) || line[0][i
				+ 1] == '?') && line[1][i] != '\'' && line[1][i + 1] != '\'')
			return (i);
	}
	return (-1);
}

int	there_is_exitcode(char **line)
{
	int	i;

	i = -1;
	while (line[0][++i])
	{
		if (line[0][i] == '$' && line[0][i + 1] == '?' && line[1][i] != '\''
			&& line[1][i + 1] != '\'')
			return (1);
	}
	return (-1);
}

int	env_var_len(char **line)
{
	int	start;
	int	len;

	start = there_is_a_env_var(line) + 1;
	len = 0;
	if (line[0][start + len] && line[0][start + len] == '?' && line[1][start
		+ len] != '\'')
		return (1);
	while (line[0][start + len] && ft_isenvchar(line[0][start + len])
		&& line[1][start + len] != '\'')
		len++;
	return (len);
}

char	**take_before(t_shell_memory *data, char **line)
{
	char	**before;

	before = calloc_tuning(&data->malloc_chain, sizeof(char *) * 2);
	if (before == NULL)
		return (NULL);
	before[0] = ft_substr(data, line[0], 0, there_is_a_env_var(line));
	before[1] = ft_substr(data, line[1], 0, there_is_a_env_var(line));
	return (before);
}

char	**take_var(t_shell_memory *data, char **line)
{
	char	**var;

	var = calloc_tuning(&data->malloc_chain, sizeof(char *) * 2);
	if (var == NULL)
		return (NULL);
	var[0] = ft_substr(data, line[0], there_is_a_env_var(line) + 1,
			env_var_len(line));
	var[1] = ft_substr(data, line[1], there_is_a_env_var(line) + 1,
			env_var_len(line));
	return (var);
}
