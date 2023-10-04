/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stake_n_open_redirections_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:47:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 23:24:22 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_error(t_shell_memory *data, t_list *lst)
{
	data->fatal_error = 1;
	if (!lst->next)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%s'\n",
			((t_parsing *)lst->next->content)->arg);
}

void	stake_redir_in(t_shell_memory *data, t_list *lst)
{
	int		fd;
	char	*error_msg;

	if (!lst->next || ((t_parsing *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_parsing *)lst->next->content)->arg, O_RDONLY);
	if (fd == -1)
	{
		((t_parsing *)lst->content)->open_error = 1;
		data->exit_code = 1;
		error_msg = ft_strjoin("minishell: ",
				((t_parsing *)lst->next->content)->arg);
		perror(error_msg);
		return (free(error_msg));
	}
	else
		((t_parsing *)lst->content)->file_fd = fd;
	free(((t_parsing *)lst->content)->arg);
	((t_parsing *)lst->content)->arg
		= ft_strdup(((t_parsing *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_parsing_node);
}

void	stake_redir_out(t_shell_memory *data, t_list *lst)
{
	int		fd;
	char	*error_msg;

	if (!lst->next || ((t_parsing *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_parsing *)lst->next->content)->arg,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_msg = ft_strjoin("minishell: ",
				((t_parsing *)lst->next->content)->arg);
		((t_parsing *)lst->content)->open_error = 1;
		data->exit_code = 1;
		perror(error_msg);
		return (free(error_msg));
	}
	else
		((t_parsing *)lst->content)->file_fd = fd;
	free(((t_parsing *)lst->content)->arg);
	((t_parsing *)lst->content)->arg
		= ft_strdup(((t_parsing *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_parsing_node);
}

void	stake_redir_append(t_shell_memory *data, t_list *lst)
{
	int		fd;
	char	*error_msg;

	if (!lst->next || ((t_parsing *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_parsing *)lst->next->content)->arg,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		error_msg = ft_strjoin("minishell: ",
				((t_parsing *)lst->next->content)->arg);
		((t_parsing *)lst->content)->open_error = 1;
		data->exit_code = 1;
		perror(error_msg);
		return (free(error_msg));
	}
	else
		((t_parsing *)lst->content)->file_fd = fd;
	free(((t_parsing *)lst->content)->arg);
	((t_parsing *)lst->content)->arg
		= ft_strdup(((t_parsing *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_parsing_node);
}
