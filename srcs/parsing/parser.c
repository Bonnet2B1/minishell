/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:13:02 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/02 21:30:04 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_shell_memory *data)
{
	if (is_empty_or_whitespaces(data->input_line[0]))
		return (0);
	if (!quotes_gestion(data->input_line))
		return (0);
	// print_input_line(data->input_line);
	env_var_gestion(data, data->input_line);
	if (forbiddens_chars(data->input_line))
		return (0);
	crazy_split(data, data->input_line);
	// print_t_parsing(data->parsing_lst);
	tokenization(data->parsing_lst);
	stack_cmd_args(data, data->parsing_lst);
	rm_quotes(data->parsing_lst);
	stake_n_open_files(data, data->parsing_lst);
	if (!here_doc_gestion(data, data->parsing_lst))
		return (0);
	if (data->fatal_error)
		return (0);
	setup_execution_lst(data, data->parsing_lst);
	setup_fd(data, data->exec_lst);
	// print_t_exec(data->exec_lst);
	return (1);
}
