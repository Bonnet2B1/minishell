/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:26:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/06 01:10:16 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**take_exitcode(t_shell_memory *data, char **line, char **var)
{
	char	**exitcode;

	exitcode = calloc_tuning(&data->malloc_chain, sizeof(char *) * 2);
	if (exitcode == NULL)
		return (NULL);
	if (there_is_exitcode(line) == -1)
	{
		exitcode[0] = ft_strdup(data, "");
		exitcode[1] = ft_strdup(data, "");
		return (exitcode);
	}
	exitcode[0] = ft_itoa(data, data->exit_code);
	exitcode[1] = ft_memset(
			ft_calloc(data, sizeof(char),
				ft_strlen(exitcode[0]) + 1), var[1][0], ft_strlen(exitcode[0]));
	exitcode[1][ft_strlen(exitcode[0])] = '\0';
	return (exitcode);
}

char	**take_replacement(t_shell_memory *data, char **var, char **env)
{
	char	**replacement;
	char	*joined;
	int		index;

	replacement = calloc_tuning(&data->malloc_chain, sizeof(char *) * 2);
	if (replacement == NULL)
		return (NULL);
	if (var[0][0] == '?' && var[1][0] != '\'')
		var[0]++;
	joined = ft_strjoin(data, var[0], "=");
	index = find(data, joined, ft_strlen(joined));
	if (index == -1)
	{
		replacement[0] = ft_strdup(data, "");
		replacement[1] = ft_strdup(data, "");
		return (replacement);
	}
	replacement[0] = ft_substr(data, env[index],
			ft_strlen(joined), ft_strlen(env[find(data, joined,
					ft_strlen(joined))]) - ft_strlen(joined));
	replacement[1] = ft_memset(ft_calloc(data, sizeof(char),
				(ft_strlen(replacement[0]) + 1)), var[1][0],
			ft_strlen(replacement[0]));
	return (replacement);
}

char	**take_after(t_shell_memory *data, char **line)
{
	char	**after;

	after = calloc_tuning(&data->malloc_chain, sizeof(char *) * 2);
	if (after == NULL)
		return (NULL);
	after[0] = ft_substr(data, line[0], there_is_a_env_var(line)
			+ env_var_len(line) + 1, 2147483647);
	after[1] = ft_substr(data, line[1], there_is_a_env_var(line)
			+ env_var_len(line) + 1, 2147483647);
	return (after);
}

void	env_var_gestion(t_shell_memory *data, char **line)
{
	char	**before;
	char	**var;
	char	**replacement;
	char	**after;

	while (there_is_a_env_var(line) != -1)
	{
		before = take_before(data, line);
		var = take_var(data, line);
		if (there_is_exitcode(line) != -1)
			replacement = take_exitcode(data, line, var);
		else
			replacement = take_replacement(data, var, data->env);
		after = take_after(data, line);
		line[0] = ft_strjoin(data, before[0], replacement[0]);
		line[0] = ft_strjoin(data, line[0], after[0]);
		line[1] = ft_strjoin(data, before[1], replacement[1]);
		line[1] = ft_strjoin(data, line[1], after[1]);
	}
}
