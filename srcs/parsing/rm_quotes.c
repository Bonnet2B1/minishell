/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:10:13 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/02 21:31:06 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_quotes_arg(char **arg)
{
	if (*arg[0] == '\"' || *arg[0] == '\'')
		*arg = ft_substr_free(*arg, 1, ft_strlen(*arg) - 2);
}

void	rm_quotes_cmd(char ***cmd)
{
	int	i;

	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i][0] == '\"' || cmd[0][i][0] == '\'')
			cmd[0][i] = ft_substr_free(cmd[0][i], 1, ft_strlen(cmd[0][i]) - 2);
	}
}

void	rm_quotes(t_list *parsing_lst)
{
	while (parsing_lst)
	{
		if (((t_parsing *)parsing_lst->content)->arg)
			rm_quotes_arg(&((t_parsing *)parsing_lst->content)->arg);
		if (((t_parsing *)parsing_lst->content)->cmd)
			rm_quotes_cmd(&((t_parsing *)parsing_lst->content)->cmd);
		parsing_lst = parsing_lst->next;
	}
}
