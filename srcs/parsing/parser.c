/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:13:02 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 00:43:21 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_shell_memory *data, t_list *parsing_lst)
{
	t_parsing *node;

	while (parsing_lst)
	{
		node = (t_parsing *)parsing_lst->content;
		if (node->token == PIPE && (!parsing_lst->next || !parsing_lst->prev || ((t_parsing *)parsing_lst->next->content)->token == PIPE))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (data->exit_code = 258);
		}
		parsing_lst = parsing_lst->next;
	}
	return (0);
}

int	parsing(t_shell_memory *data)
{
	if (is_empty_or_whitespaces(data->input_line[0]))
		return (0);
	if (!quotes_gestion(data->input_line))
		return (0);
	rm_quotes(data->input_line);
	// print_input_line(data->input_line); //! PRINT
	env_var_gestion(data, data->input_line);
	if (forbiddens_chars(data->input_line))
		return (0);
	crazy_split(data, data->input_line);
	tokenization(data->parsing_lst);
	// print_t_parsing(data->parsing_lst); //! PRINT
	stack_cmd_args(data, data->parsing_lst);
	stake_n_open_files(data, data->parsing_lst);
	if (data->fatal_error)
		return (0);
	if (syntax_error(data, data->parsing_lst))
		return (0);
	if (!here_doc_gestion(data, data->parsing_lst))
		return (0);
	if (data->fatal_error)
		return (0);
	setup_execution_lst(data, data->parsing_lst);
	setup_fd(data, data->exec_lst);
	// print_t_exec(data->exec_lst); //! PRINT
	return (1);
}
