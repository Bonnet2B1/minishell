/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:26:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 20:36:35 by edelarbr         ###   ########.fr       */
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

char	**take_before(char **line)
{
	char	**before;

	before = malloc(sizeof(char *) * 2);
	if (before == NULL)
		return (NULL);
	before[0] = ft_substr(line[0], 0, there_is_a_env_var(line));
	before[1] = ft_substr(line[1], 0, there_is_a_env_var(line));
	return (before);
}

char	**take_var(char **line)
{
	char	**var;

	var = malloc(sizeof(char *) * 2);
	if (var == NULL)
		return (NULL);
	var[0] = ft_substr(line[0], there_is_a_env_var(line) + 1,
			env_var_len(line));
	var[1] = ft_substr(line[1], there_is_a_env_var(line) + 1,
			env_var_len(line));
	return (var);
}

char	**take_exitcode(t_shell_memory *data, char **line, char **var)
{
	char	**exitcode;

	exitcode = malloc(sizeof(char *) * 2);
	if (exitcode == NULL)
		return (NULL);
	if (there_is_exitcode(line) == -1)
	{
		exitcode[0] = ft_strdup("");
		exitcode[1] = ft_strdup("");
		return (exitcode);
	}
	exitcode[0] = ft_itoa(data->exit_code);
	exitcode[1] = ft_memset(ft_calloc(sizeof(char), (ft_strlen(exitcode[0])
					+ 1)), var[1][0], ft_strlen(exitcode[0]));
	exitcode[1][ft_strlen(exitcode[0])] = '\0';
	return (exitcode);
}

char	**take_replacement(t_shell_memory *data, char **var, char **env)
{
	char	**replacement;
	char	*joined;
	int		index;

	replacement = malloc(sizeof(char *) * 2);
	if (replacement == NULL)
		return (NULL);
	if (var[0][0] == '?' && var[1][0] != '\'')
		var[0]++;
	joined = ft_strjoin(var[0], "=");
	index = find(data, joined, ft_strlen(joined));
	if (index == -1)
	{
		replacement[0] = ft_strdup("");
		replacement[1] = ft_strdup("");
		return (replacement);
	}
	replacement[0] = ft_substr(env[index],
			ft_strlen(joined), ft_strlen(env[find(data, joined,
					ft_strlen(joined))]) - ft_strlen(joined));
	replacement[1] = ft_memset(ft_calloc(sizeof(char),
				(ft_strlen(replacement[0]) + 1)), var[1][0],
			ft_strlen(replacement[0]));
	return (replacement);
}

char	**take_after(char **line)
{
	char	**after;

	after = malloc(sizeof(char *) * 2);
	if (after == NULL)
		return (NULL);
	after[0] = ft_substr(line[0], there_is_a_env_var(line) + env_var_len(line)
			+ 1, 2147483647);
	after[1] = ft_substr(line[1], there_is_a_env_var(line) + env_var_len(line)
			+ 1, 2147483647);
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
		before = take_before(line);
		var = take_var(line);
		if (there_is_exitcode(line) != -1)
			replacement = take_exitcode(data, line, var);
		else
			replacement = take_replacement(data, var, data->env);
		after = take_after(line);
		free(line[0]);
		free(line[1]);
		line[0] = ft_strjoin_freeall(before[0], replacement[0]);
		line[0] = ft_strjoin_freeall(line[0], after[0]);
		line[1] = ft_strjoin_freeall(before[1], replacement[1]);
		line[1] = ft_strjoin_freeall(line[1], after[1]);
		free(before);
		free(var);
		free(replacement);
		free(after);
	}
}
