/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stake_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:47:48 by edelarbr          #+#    #+#             */
/*   Updated: 2023/09/11 22:09:07 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_error(t_shell_memory *data, t_list *lst)
{
	data->error = 1;
	if (!lst->next)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(((t_split *)lst->next->content)->arg, 2);
		ft_putstr_fd("'\n", 2);
	}
}

void	stake_redir_in(t_shell_memory *data, t_list *lst)
{
	int fd;

	if (!lst->next || ((t_split *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_split *)lst->next->content)->arg, O_RDONLY);
	if (fd == -1)
		return (data->error = 1, perror("minishell: file"));
	else
		close(fd);
	free(((t_split *)lst->content)->arg);
	((t_split *)lst->content)->arg = ft_strdup(((t_split *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_split_node);
}

void	stake_redir_out(t_shell_memory *data, t_list *lst)
{
	int fd;

	if (!lst->next || ((t_split *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_split *)lst->next->content)->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (data->error = 1, perror("minishell: file"));
	else
		close(fd);
	free(((t_split *)lst->content)->arg);
	((t_split *)lst->content)->arg = ft_strdup(((t_split *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_split_node);
}

void	stake_redir_append(t_shell_memory *data, t_list *lst)
{
	int fd;

	if (!lst->next || ((t_split *)lst->next->content)->token != FILEE)
		return (redir_error(data, lst));
	fd = open(((t_split *)lst->next->content)->arg,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (data->error = 1, perror("minishell: file"));
	else
		close(fd);
	free(((t_split *)lst->content)->arg);
	((t_split *)lst->content)->arg = ft_strdup(((t_split *)lst->next->content)->arg);
	ft_lstdel_here(&data->parsing_lst, lst->next, (void *)free_split_node);
}

void	stake_redirections(t_shell_memory *data, t_list *lst)
{
	while (lst && !data->error)
	{
		if (((t_split *)lst->content)->token == REDIR_IN)
			stake_redir_in(data, lst);
		else if (((t_split *)lst->content)->token == REDIR_OUT)
			stake_redir_out(data, lst);
		else if (((t_split *)lst->content)->token == REDIR_APPEND)
			stake_redir_append(data, lst);
		lst = lst->next;
	}
}
