/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:13:02 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/17 22:18:59 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!ft_strcmp(data->input_line[0], ""))
		return ;
	if (!quotes_gestion(data->input_line))
		return ;
	rm_quotes(data->input_line);
	print_input_line(data->input_line);
	env_var_gestion(data, data->input_line);
	print_input_line(data->input_line);
	if (forbiddens_chars(data->input_line[0]))
		return ;
	crazy_split(data, data->input_line);
	tokenization(data->parsing_lst);
	stack_cmd_args(data, data->parsing_lst);
	stake_n_open_files(data, data->parsing_lst);
	print_t_parsing(data->parsing_lst);
	if (data->fatal_error)
		return ;
	setup_execution_lst(data, data->parsing_lst);
	setup_fd(data, data->exec_lst);
	print_t_exec(data->exec_lst);
}
