/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:26:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/10 22:22:20 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	there_is_a_env_var(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '$' && ft_isenvchar(arg[i + 1]))
			return (1);
	}
	return (0);
}

char	*identify_env_var(char *arg)
{
	int		start;
	int		len;
	char	*var;

	start = -1;
	while (arg[++start])
		if (arg[start] == '$' && ft_isenvchar(arg[start + 1]))
			break ;
	if (arg[start] == '$')
		start++;
	len = 0;
	while (ft_isenvchar(arg[start + len]))
		len++;
	var = ft_substr(arg, start, len);
	return (var);
}

char	*identify_replacement(t_shell_memory *data, char *var)
{
	int		i;
	char	*joined;
	char	*replacement;

	joined = ft_strjoin(var, "=");
	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(joined, data->env[i], ft_strlen(joined)) == 0)
		{
			replacement = ft_substr(data->env[i], ft_strlen(joined),
					ft_strlen(data->env[i] - ft_strlen(joined)));
			break ;
		}
		else
			replacement = "";
	}
	return (free(joined), replacement);
}

char	*replacement_of_var(char *arg, char *var, char *replacement)
{
	int		i;
	char	*new_arg;
	char	*before_var;
	char	*after_var;

	i = -1;
	while (arg[++i])
		if (arg[i] == '$' && ft_isenvchar(arg[i + 1]))
			break ;
	before_var = ft_substr(arg, 0, i);
	after_var = ft_substr(
			arg, ft_strlen(before_var) + ft_strlen(var) + 1, 2147483647);
	new_arg = before_var;
	new_arg = ft_strjoin_free_s1(new_arg, replacement);
	new_arg = ft_strjoin_free_s1(new_arg, after_var);
	free(after_var);
	return (new_arg);
}

void	env_var_gestion(t_shell_memory *data, t_list *lst)
{
	char	*var;
	char	*replacement;

	while (lst)
	{
		while (there_is_a_env_var(((t_split *)lst->content)->arg))
		{
			var = identify_env_var(((t_split *)lst->content)->arg);
			replacement = identify_replacement(data, var);
			((t_split *)lst->content)->arg = replacement_of_var(
					((t_split *)lst->content)->arg, var, replacement);
			free(var);
			free(replacement);
		}
		lst = lst->next;
	}
}
