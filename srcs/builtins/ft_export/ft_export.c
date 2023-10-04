/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:04:52 by gloms             #+#    #+#             */
/*   Updated: 2023/10/04 19:26:48 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	swap_str(char **s1, char **s2, int fre)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
	if (fre == 1)
		free(*s2);
}

int	ft_export(t_shell_memory *data, char **args)
{
	char	*rp;
	int		i;

	i = 1;
	while (args[i])
	{
		rp = rtn_arg(args[i]);
		if (args[i] && (!is_letter(args[i][0]) || !ft_srch(args[i])))
		{
			printf("minishell: export: `%s': not a valid identifier\n", args[i]);
			if (!args[i + 1])
				return (1);
		}
		else if (find(data, rp, ft_strlen(rp)) == -1)
			data->env = ft_tabdup_add_nl_free(data->env, args[i]);
		else if (find(data, rp, ft_strlen(rp)) != -1)
			swap_str(&data->env[find(data, rp, ft_strlen(rp))], &args[i], 1);
		free(rp);
		i++;
	}
	return (0);
}
