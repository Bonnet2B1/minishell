/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:55:30 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/17 21:31:11 by edelarbr         ###   ########.fr       */
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

int	print_token(enum e_token token)
{
	if (token == NONE)
		return (printf("NONE"));
	else if (token == PIPE)
		return (printf("PIPE"));
	else if (token == REDIR_APPEND)
		return (printf("REDIR_APPEND"));
	else if (token == REDIR_OUT)
		return (printf("REDIR_OUT"));
	else if (token == REDIR_IN)
		return (printf("REDIR_IN"));
	else if (token == FILEE)
		return (printf("FILEE"));
	else if (token == COMMAND)
		return (printf("COMMAND"));
	return (0);
}

void	print_t_exec(t_list *lst)
{
	int			i;
	long long	spaces;

	(void)spaces;
	if (!lst)
		return ;
	printf("=============== Print Execution List ===============\n");
	while(lst)
	{
		if (((t_exec *)lst->content)->cmd)
		{
			printf("commande  : ");
			spaces = 15;
			i = -1;
			while (((t_exec *)lst->content)->cmd[++i])
			{
				printf("%s ", ((t_exec *)lst->content)->cmd[i]);
				spaces -= ft_strlen(((t_exec *)lst->content)->cmd[i]) + 1;
			}
		}
		if (((t_exec *)lst->content)->in_struct)
		{
			printf("\n|_entree  : ");
			spaces = 12;
			spaces -= printf("%s ", (((t_parsing *)((t_exec *)lst->content)->in_struct)->arg));
			while (spaces-- > 0)
				printf(" ");
			spaces = 13;
			spaces -= print_token(((t_parsing *)((t_exec *)lst->content)->in_struct)->token);
			while (spaces-- > 0)
				printf(" ");
			printf("%p", (((t_exec *)lst->content)->in_struct));
			if (((t_parsing *)((t_exec *)lst->content)->in_struct)->token == PIPE)
				printf("   %d", ((t_parsing *)((t_exec *)lst->content)->in_struct)->pipe_fd[1]);
			else if (((t_parsing *)((t_exec *)lst->content)->in_struct)->token == REDIR_IN || ((t_parsing *)((t_exec *)lst->content)->in_struct)->token == REDIR_OUT || ((t_parsing *)((t_exec *)lst->content)->in_struct)->token == REDIR_APPEND)
				printf("   %d", ((t_parsing *)((t_exec *)lst->content)->in_struct)->file_fd);
		}
		else
			printf("\n|_entree  :             TERMINAL/SPACE             %d", ((t_exec *)lst->content)->in_fd);
		printf("\n| |_fd_in : %d\n|", ((t_exec *)lst->content)->in_fd);
		if (((t_exec *)lst->content)->out_struct)
		{
			printf("\n|_sortie  : ");
			spaces = 12;
			spaces -= printf("%s ", (((t_parsing *)((t_exec *)lst->content)->out_struct)->arg));
			while (spaces-- > 0)
				printf(" ");
			spaces = 13;
			spaces -= print_token(((t_parsing *)((t_exec *)lst->content)->out_struct)->token);
			while (spaces-- > 0)
				printf(" ");
			printf("%p", (((t_exec *)lst->content)->out_struct));
			if (((t_parsing *)((t_exec *)lst->content)->out_struct)->token == PIPE)
				printf("   %d", ((t_parsing *)((t_exec *)lst->content)->out_struct)->pipe_fd[0]);
			else if (((t_parsing *)((t_exec *)lst->content)->out_struct)->token == REDIR_IN || ((t_parsing *)((t_exec *)lst->content)->out_struct)->token == REDIR_OUT || ((t_parsing *)((t_exec *)lst->content)->out_struct)->token == REDIR_APPEND)
				printf("   %d", ((t_parsing *)((t_exec *)lst->content)->out_struct)->file_fd);
		}
		else
			printf("\n|_sortie  :             TERMINAL/SPACE             %d", ((t_exec *)lst->content)->out_fd);
		printf("\n  |_fd_out: %d", ((t_exec *)lst->content)->out_fd);
		if (lst->next)
			printf("\n");
		printf("\n");
		lst = lst->next;
	}
	printf("====================================================\n");
}

void	print_t_parsing(t_list *lst)
{
	int			i;
	long long	spaces;

	if (!lst)
		return ;
	printf("================ Print Parsing List ================\n");
	while (lst)
	{
		spaces = 20;
		if ((((t_parsing *)lst->content)->arg))
		{
			printf("%s", ((t_parsing *)lst->content)->arg);
			spaces -= ft_strlen(((t_parsing *)lst->content)->arg);
		}
		if ((((t_parsing *)lst->content)->cmd))
		{
			i = -1;
			while (((t_parsing *)lst->content)->cmd[++i])
			{
				printf("%s ", ((t_parsing *)lst->content)->cmd[i]);
				spaces -= ft_strlen(((t_parsing *)lst->content)->cmd[i]) + 1;
			}
		}
		while (spaces-- > 0)
			printf(" ");
		print_token(((t_parsing *)lst->content)->token);
		printf("\n");
		lst = lst->next;
	}
	printf("====================================================\n");
}

void	print_input_line(char **input_line)
{
	printf("==================== INPUT LINE ====================\n");
	if (input_line[1])
		printf("quotes    : %s\n", input_line[1]);
	if (input_line[0])
		printf("input_line: %s\n", input_line[0]);
	printf("====================================================\n");
}

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("tab[%d]: %s\n", i, tab[i]);
}
