/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:13:02 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/14 17:49:48 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_separate_whitespaces(t_shell_memory *data)
{
	int	i;

	data->cmd_line_split = ft_parsing_white_space(data->input_line);
	i = -1;
	while (data->cmd_line_split[++i])
		ft_lstadd_back(&data->parsing_lst,
			ft_lstnew(create_parsing_node(data->cmd_line_split[i])));
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
		data->cmd_line_split = ft_parsing_keep_char(
				((t_parsing *)lst->content)->arg, operator);
		i = -1;
		while (data->cmd_line_split[++i])
		{
			ft_lstadd_here(lst,
				ft_lstnew(create_parsing_node(data->cmd_line_split[i])));
			lst = lst->next;
		}
		free(data->cmd_line_split);
		ft_lstdel_here(&data->parsing_lst, to_del, (void *)free_parsing_node);
		lst = lst->next;
	}
}

void	tokenization(t_list *lst)
{
	while (lst)
	{
		if (!ft_strncmp(((t_parsing *)lst->content)->arg, "|", 1))
			((t_parsing *)lst->content)->token = PIPE;
		else if (!ft_strncmp(((t_parsing *)lst->content)->arg, ">>", 2))
			((t_parsing *)lst->content)->token = REDIR_APPEND;
		else if (!ft_strncmp(((t_parsing *)lst->content)->arg, ">", 1))
			((t_parsing *)lst->content)->token = REDIR_OUT;
		else if (!ft_strncmp(((t_parsing *)lst->content)->arg, "<", 1))
			((t_parsing *)lst->content)->token = REDIR_IN;
		else if (lst->prev
			&& (((t_parsing *)lst->prev->content)->token == REDIR_IN
				|| ((t_parsing *)lst->prev->content)->token == REDIR_OUT
				|| ((t_parsing *)lst->prev->content)->token == REDIR_APPEND))
			((t_parsing *)lst->content)->token = FILEE;
		else
			((t_parsing *)lst->content)->token = COMMAND;
		lst = lst->next;
	}
}

int	forbiddens_chars(char *input_line)
{
	int	i;

	i = -1;
	while (input_line[++i])
	{
		if (input_line[i] == ';' || input_line[i] == '\\')
		{
			printf("minishell: syntax error near unexpected token `");
			printf("%c'\n", input_line[i]);
			return (1);
		}
	}
	return (0);
}

void	parsing(t_shell_memory *data)
{
	if (!ft_strcmp(data->input_line, "") || forbiddens_chars(data->input_line))
		return ;
	lst_separate_whitespaces(data);
	env_var_gestion(data, data->parsing_lst);
	lst_separate_operator(data,'|');
	lst_separate_operator(data,'>');
	lst_separate_operator(data,'<');
	tokenization(data->parsing_lst);
	stack_cmd_args(data, data->parsing_lst);
	stake_n_open_files(data, data->parsing_lst);
	print_t_parsing(data->parsing_lst);
	if (data->fatal_error)
		return ;
	setup_execution_lst(data, data->parsing_lst);
	setup_fd(data, data->exec_lst);
	print_t_parsing(data->parsing_lst);
	print_t_exec(data->exec_lst);
}
