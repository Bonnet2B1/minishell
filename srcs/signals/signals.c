/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:20:07 by gloms             #+#    #+#             */
/*   Updated: 2023/09/21 23:02:54 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../minishell.h"

void	sig_handler_quit(void)
{
	return ;
}

void	sig_handler_int(void)
{
	//printf("\n\033[1;35mminishell\033[0m-\033[1;31m3.2$ \033[0m");
	write(1,"\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(int i)
{
	if (i == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 1)
	{
		signal(SIGINT, (void *)sig_handler_int);
		signal(SIGQUIT, (void *)sig_handler_quit);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
*/
