/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:55:30 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/28 21:35:47 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_t_split(t_list *lst)
{
	int	spaces;

	while (lst)
	{
		printf("%s", ((t_split *)lst->content)->arg);
		spaces = 20 - ft_strlen(((t_split *)lst->content)->arg);
		while (spaces-- > 0)
			printf(" ");
		if (((t_split *)lst->content)->token == PIPE)
			printf("PIPE\n");
		else if (((t_split *)lst->content)->token == REDIR_APPEND)
			printf("REDIR_APPEND\n");
		else if (((t_split *)lst->content)->token == REDIR_OUT)
			printf("REDIR_OUT\n");
		else if (((t_split *)lst->content)->token == REDIR_IN)
			printf("REDIR_IN\n");
		else if (((t_split *)lst->content)->token == COMMAND)
			printf("COMMAND\n");
		else if (((t_split *)lst->content)->token == FILEE)
			printf("FILEE\n");
		lst = lst->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("print_tab: %s\n", tab[i]);
}
