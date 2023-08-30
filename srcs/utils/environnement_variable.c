/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:26:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/30 02:39:36 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isenvchar(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 123)
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

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

	start = 0;
	while (arg[start] == '$' && ft_isenvchar(arg[start + 1]))
		start++;
	len = 0;
	while (ft_isenvchar(arg[start + len]))
		len++;
	var = ft_substr(arg, start, len);
	return (var);
}

char	*identify_replacement(t_shell_memory *data, char *var)
{
	// - join un '='
	// - strncmp dans **env
	// - si homologue, return homologue
	// - sinon, return '\n'
}

// fonction qui remplace
// {
// 	- dup l'avant var (avec le '$')
// 	- dup l'apres var
// 	- join remplacement a l'avant var
// 	- join l'apres var a cette addition
// 	- free l'avant var, l'apres var, arg
// 	- return le resulatat du join (new_arg ?)
// }

void	env_var_gestion(t_shell_memory *data, t_list *lst)
{
	char	*var;
	char	*replacement;

	while (lst)
	{
		while (there_is_a_env_var(((t_split *)lst->content)->arg))
		{
			var = identify_env_var(data, ((t_split *)lst->content)->arg);
			replacement = identify_replacement(data, var);
			// - fonction qui remplace la variable dans arg
			// - free var et replacement
		}
		lst = lst->next;
	}
}
