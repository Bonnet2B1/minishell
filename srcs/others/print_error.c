/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 01:51:32 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/06 01:54:03 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *obj, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(obj, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
