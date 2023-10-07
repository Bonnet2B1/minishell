/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 01:51:32 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/07 16:48:08 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	p_err(char *obj1, char *obj2, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (obj1)
	{
		ft_putstr_fd(obj1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (obj2)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(obj2, 2);
		ft_putstr_fd("': ", 2);
	}
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
	}
}
