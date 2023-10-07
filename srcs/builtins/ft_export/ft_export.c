/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:04:52 by gloms             #+#    #+#             */
/*   Updated: 2023/10/07 16:29:10 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_tabdup_add_nl(t_shell_memory *data, char **tab, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = calloc_tuning(&data->malloc_chain, sizeof(char *) * (i + 2));
	if (!new_tab)
		return (perror("Malloc"), NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(data, tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(data, str);
	new_tab[i + 1] = NULL;
	return (new_tab);
}

void	swap_str(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

int	ft_export(t_shell_memory *data, char **args)
{
	char	*rp;
	int		i;
	int		occurence;

	i = 0;
	while (args[++i])
	{
		rp = rtn_arg(data, args[i]);
		occurence = find(data, ft_strjoin(data, rp, "="), ft_strlen(rp) + 1);
		if (occurence != -1 && !ft_strchr(args[i], '='))
			continue ;
		if (args[i] && (!is_letter(args[i][0]) || !ft_srch(args[i])))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			if (!args[i + 1])
				return (1);
		}
		else if (find(data, rp, ft_strlen(rp)) == -1)
			data->env = ft_tabdup_add_nl(data, data->env, args[i]);
		else if (find(data, rp, ft_strlen(rp)) != -1)
			swap_str(&data->env[find(data, rp, ft_strlen(rp))], &args[i]);
	}
	return (0);
}
