/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:55:30 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/11 20:58:15 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lst_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	printf("lst size: %d\n", i);
}

void	print_t_split(t_list *lst)
{
	int			i;
	long long	spaces;

	printf("--------- Print List ---------\n");
	while (lst)
	{
		spaces = 20;
		if ((((t_split *)lst->content)->arg))
		{
			printf("%s", ((t_split *)lst->content)->arg);
			spaces -= ft_strlen(((t_split *)lst->content)->arg);
		}
		if ((((t_split *)lst->content)->cmd))
		{
			i = -1;
			while (((t_split *)lst->content)->cmd[++i])
			{
				printf("%s ", ((t_split *)lst->content)->cmd[i]);
				spaces -= ft_strlen(((t_split *)lst->content)->cmd[i]) + 1;
			}
		}
		while (spaces-- > 0)
			printf(" ");
		if (((t_split *)lst->content)->token == PIPE)
			printf("\tPIPE\n");
		else if (((t_split *)lst->content)->token == REDIR_APPEND)
			printf("\tREDIR_APPEND\n");
		else if (((t_split *)lst->content)->token == REDIR_OUT)
			printf("\tREDIR_OUT\n");
		else if (((t_split *)lst->content)->token == REDIR_IN)
			printf("\tREDIR_IN\n");
		else if (((t_split *)lst->content)->token == FILEE)
			printf("\tFILEE\n");
		else if (((t_split *)lst->content)->token == COMMAND)
			printf("\tCOMMAND\n");
		lst = lst->next;
	}
	printf("------------------------------\n");
}

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("tab[%d]: %s\n", i, tab[i]);
}
