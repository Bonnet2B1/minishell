/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:20:07 by gloms             #+#    #+#             */
/*   Updated: 2023/09/26 17:19:47 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler_quit(void)
{
	return ;
}

void	sig_handler_int(void)
{
	write(1,"\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler_int_hd()
{
	write(1,"\n", 1);
	ft_exit(NULL, 0); // ! leaks
}

void	ft_signal(int i)
{
	if (i == OFF)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == ON)
	{
		rl_catch_signals = 0;
		signal(SIGINT, (void *)sig_handler_int);
		signal(SIGQUIT, (void *)sig_handler_quit);
	}
	else if (i == DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (i == SIG_HERE_DOC)
	{
		rl_catch_signals = 1;
		signal(SIGINT, (void *)sig_handler_int_hd);
		signal(SIGQUIT, (void *)sig_handler_quit);
	}
}