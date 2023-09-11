/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:13:02 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/11 21:44:22 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_separate_whitespaces(t_shell_memory *data)
{
	int	i;

	data->cmd_line_split = ft_split_white_space(data->input_line);
	i = -1;
	while (data->cmd_line_split[++i])
		ft_lstadd_back(&data->parsing_lst,
			ft_lstnew(create_split_node(data->cmd_line_split[i])));
	free(data->cmd_line_split);
}

void	lst_separate_operator(t_shell_memory *data, char operator)
{
	int		i;
	t_list	*lst;
	t_list	*to_del;

	lst = data->parsing_lst;
	while (lst)
	{
		to_del = lst;
		data->cmd_line_split = ft_split_keep_char(
				((t_split *)lst->content)->arg, operator);
		i = -1;
		while (data->cmd_line_split[++i])
		{
			ft_lstadd_here(lst,
				ft_lstnew(create_split_node(data->cmd_line_split[i])));
			lst = lst->next;
		}
		free(data->cmd_line_split);
		ft_lstdel_here(&data->parsing_lst, to_del, (void *)free_split_node);
		lst = lst->next;
	}
}

void	tokenization(t_list *lst)
{
	while (lst)
	{
		if (!ft_strncmp(((t_split *)lst->content)->arg, "|", 1))
			((t_split *)lst->content)->token = PIPE;
		else if (!ft_strncmp(((t_split *)lst->content)->arg, ">>", 2))
			((t_split *)lst->content)->token = REDIR_APPEND;
		else if (!ft_strncmp(((t_split *)lst->content)->arg, ">", 1))
			((t_split *)lst->content)->token = REDIR_OUT;
		else if (!ft_strncmp(((t_split *)lst->content)->arg, "<", 1))
			((t_split *)lst->content)->token = REDIR_IN;
		else if (lst->prev
			&& (((t_split *)lst->prev->content)->token == REDIR_IN
				|| ((t_split *)lst->prev->content)->token == REDIR_OUT
				|| ((t_split *)lst->prev->content)->token == REDIR_APPEND))
			((t_split *)lst->content)->token = FILEE;
		else
			((t_split *)lst->content)->token = COMMAND;
		lst = lst->next;
	}
}

void	input_gestion(t_shell_memory *data)
{
	if (!ft_strcmp(data->input_line, ""))
		return ;
	lst_separate_whitespaces(data);
	env_var_gestion(data, data->parsing_lst);
	lst_separate_operator(data,'|');
	lst_separate_operator(data,'>');
	lst_separate_operator(data,'<');
	tokenization(data->parsing_lst);
	stack_cmd_args(data, data->parsing_lst);
	stake_redirections(data, data->parsing_lst);
	if (data->error)
		return ;
	print_t_split(data->parsing_lst);
}
