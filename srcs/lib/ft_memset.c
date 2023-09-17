/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:16:40 by edelarbr          #+#    #+#             */
/*   Updated: 2022/10/31 18:16:40 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *memory, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*char_str;

	i = 0;
	char_str = (unsigned char *)memory;
	while (i < len)
		char_str[i++] = (unsigned char)c;
	memory = (void *)char_str;
	return (memory);
}
