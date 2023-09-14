/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stake_n_open_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:47:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/14 15:33:29 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_error(t_shell_memory *data, t_list *lst)
{
	data->fatal_error = 1;
	if (!lst->next)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(((t_parsing *)lst->next->content)->arg, 2);
		ft_putstr_fd("'\n", 2);
	}
}

void	stake_redir_in(t_shell_memory *data, t_list *lst)
{
	int 	fd;
	char	*error_msg;

	if (!lst->next || ((t_parsing *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_parsing *)lst->next->content)->arg, O_RDONLY);
	if (fd == -1)
	{
		error_msg = ft_strjoin("minishell: ", ((t_parsing *)lst->next->content)->arg);
		data->fatal_error = 1;
		perror(error_msg);
		return (free(error_msg));
	}
	else
		((t_parsing *)lst->content)->file_fd = fd;
	free(((t_parsing *)lst->content)->arg);
	((t_parsing *)lst->content)->arg = ft_strdup(((t_parsing *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_parsing_node);
}

void	stake_redir_out(t_shell_memory *data, t_list *lst)
{
	int 	fd;
	char	*error_msg;

	if (!lst->next || ((t_parsing *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_parsing *)lst->next->content)->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_msg = ft_strjoin("minishell: ", ((t_parsing *)lst->next->content)->arg);
		data->fatal_error = 1;
		perror(error_msg);
		return (free(error_msg));
	}
	else
		((t_parsing *)lst->content)->file_fd = fd;
	free(((t_parsing *)lst->content)->arg);
	((t_parsing *)lst->content)->arg = ft_strdup(((t_parsing *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_parsing_node);
}

void	stake_redir_append(t_shell_memory *data, t_list *lst)
{
	int 	fd;
	char	*error_msg;

	if (!lst->next || ((t_parsing *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_parsing *)lst->next->content)->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		error_msg = ft_strjoin("minishell: ", ((t_parsing *)lst->next->content)->arg);
		data->fatal_error = 1;
		perror(error_msg);
		return (free(error_msg));
	}
	else
		((t_parsing *)lst->content)->file_fd = fd;
	free(((t_parsing *)lst->content)->arg);
	((t_parsing *)lst->content)->arg = ft_strdup(((t_parsing *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_parsing_node);
}

void	stake_n_open_files(t_shell_memory *data, t_list *lst)
{
	while (lst && !data->fatal_error)
	{
		if (((t_parsing *)lst->content)->token == REDIR_IN)
			stake_redir_in(data, lst);
		else if (((t_parsing *)lst->content)->token == REDIR_OUT)
			stake_redir_out(data, lst);
		else if (((t_parsing *)lst->content)->token == REDIR_APPEND)
			stake_redir_append(data, lst);
		lst = lst->next;
	}
}
