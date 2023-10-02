/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:04:52 by gloms             #+#    #+#             */
/*   Updated: 2023/10/03 00:05:43 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//- traiter les arguments
//- ajouter les arguments dans l'env mais ne pas les afficher si ils sont pas setup

void	swap_str(char **s1, char **s2, int fre)
{
	char *temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
	if (fre == 1)
		free(*s2);
}

int	ft_export(t_shell_memory *data, char **args)
{
	char	*rp;

	rp = rtn_arg(args[1]);
	if (args[1] && (!is_letter(args[1][0]) || !ft_srch(args[1])))
	{
		printf("minishell: export: `%s': not a valid identifier", args[1]);
		return (1);
	}
	else if (!find(data, rp, ft_strlen(rp)))
		data->env = ft_tabdup_add_nl_free(data->env, args[1]);
	else if (find(data, rp, ft_strlen(rp)))
		swap_str(&data->env[find(data, rp, ft_strlen(rp))], &args[1], 1);
	return (0);
}
