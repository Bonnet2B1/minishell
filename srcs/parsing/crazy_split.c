/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazy_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:44:26 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/06 01:08:50 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	crazy_split(t_shell_memory *data, char **line)
{
	int		start;
	int		len;
	char	*arg;

	start = 0;
	while (ft_iswhitespace(line[0][start]) && line[1][start] == '0')
		start++;
	while (line[0][start])
	{
		len = get_len(line, start);
		arg = ft_substr(data, line[0], start, len - start);
		if (arg[0] == '\0')
			break ;
		start = get_start(line, len);
		ft_lstadd_back(&data->parsing_lst,
			ft_lstnew(data, create_parsing_node(data, arg)));
	}
}
