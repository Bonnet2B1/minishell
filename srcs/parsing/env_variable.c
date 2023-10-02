/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:26:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/02 18:12:51 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	there_is_a_env_var(char **line)
{
	int	i;

	i = -1;
	while (line[0][++i])
	{
		if (line[0][i] == '$' && ft_isenvchar(line[0][i + 1])
			&& ((line[1][i] == '0' && line[1][i + 1] == '0') || (line[1][i] == '\"' && line[1][i + 1] == '\"')))
			return (1);
	}
	return (0);
}

char	**take_before(char **line)
{
	int		len;
	char	**before;

	len = -1;
	before = malloc(sizeof(char *) * 2);
	while (line[0][++len] && line[1][len] != '\0')
	{
		if (line[0][len] == '$' && ft_isenvchar(line[0][len + 1])
			&& ((line[1][len] == '0' && line[1][len + 1] == '0') || (line[1][len] == '\"' && line[1][len + 1] == '\"')))
			break ;
	}
	before[0] = ft_substr(line[0], 0, len);
	before[1] = ft_substr(line[1], 0, len);
	return (before);
}

char	**take_var(char **line)
{
	int		start;
	int		len;
	char	**var;

	var = malloc(sizeof(char *) * 3);
	var[2] = NULL;
	start = -1;
	while (line[0][++start])
		if (line[0][start] == '$' && ft_isenvchar(line[0][start + 1])
			&& ((line[1][start] == '0' && line[1][start + 1] == '0') || (line[1][start] == '\"' && line[1][start + 1] == '\"')))
			break ;
	if (line[0][start] == '$')
		start++;
	len = 0;
	while (ft_isenvchar(line[0][start + len]) && (line[1][start + len] == '0' || line[1][start + len] == '\"'))
		len++;
	var[0] = ft_substr(line[0], start, len);
	var[1] = ft_substr(line[1], start, len);
	return (var);
}

char	**take_replacement(t_shell_memory *data, char **var, char **env)
{
	int		i;
	char	*joined;
	char	**replacement;

	replacement = malloc(sizeof(char *) * 2);
	replacement[0] = NULL;
	if (ft_strcmp(var[0], "?") == 0)
	{
		replacement[0] = ft_itoa(data->exit_code);
		replacement[1] = ft_memset(ft_calloc(sizeof(char), (ft_strlen(replacement[0]) + 1)), var[1][0], ft_strlen(replacement[0]));
		return (replacement);
	}
	joined = ft_strjoin(var[0], "=");
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(joined, env[i], ft_strlen(joined)) == 0)
		{
			replacement[0] = ft_substr(env[i], ft_strlen(joined),
					ft_strlen(env[i]) - ft_strlen(joined));
			replacement[1] = ft_memset(ft_calloc(sizeof(char), (ft_strlen(replacement[0]) + 1)), var[1][0], ft_strlen(replacement[0]));
			replacement[1][ft_strlen(replacement[0])] = '\0';
			return (free(joined), replacement);
		}
	}
	replacement[0] = ft_strdup("");
	replacement[1] = ft_strdup("");
	freetab(var);
	return (free(joined), replacement);
}

char	**take_after(char **line)
{
	int		start;
	char	**after;
	char	**var;

	after = malloc(sizeof(char *) * 2);
	start = -1;
	while (line[0][++start])
	{
		if (line[0][start] == '$' && ft_isenvchar(line[0][start + 1])
			&& ((line[1][start] == '0' && line[1][start + 1] == '0') || (line[1][start] == '\"' && line[1][start + 1] == '\"')))
			break ;
	}
	if (line[0][start] == '$')
	{
		var = take_var(line);
		start += ft_strlen(var[0]) + 1;
		freetab(var);
	}
	after[0] = ft_substr(line[0], start, 2147483647);
	after[1] = ft_substr(line[1], start, 2147483647);
	return (after);
}

void	env_var_gestion(t_shell_memory *data, char **line)
{
	char **before;
	char **replacement;
	char **after;

	while (there_is_a_env_var(line))
	{
		before = take_before(line);
		replacement = take_replacement(data, take_var(line), data->env);
		after = take_after(line);
		// printf("before: %s\n", before[0]);
		// printf("before: %s\n", before[1]);
		// printf("var: %s\n", take_var(line)[0]);
		// printf("var: %s\n", take_var(line)[1]);
		// printf("replacement: %s\n", replacement[0]);
		// printf("replacement: %s\n", replacement[1]);
		// printf("after: %s\n", after[0]);
		// printf("after: %s\n", after[1]);
		free(line[0]);
		free(line[1]);
		line[0] = ft_strjoin_freeall(before[0], replacement[0]);
		line[0] = ft_strjoin_freeall(line[0], after[0]);
		line[1] = ft_strjoin_freeall(before[1], replacement[1]);
		line[1] = ft_strjoin_freeall(line[1], after[1]);
	}
}
