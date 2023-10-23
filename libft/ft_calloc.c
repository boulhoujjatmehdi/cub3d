/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:24:17 by rarraji           #+#    #+#             */
/*   Updated: 2022/10/13 18:59:05 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size == SIZE_MAX)
		return (NULL);
	p = (void *)malloc(count * size);
	if (!p)
		return (0);
	ft_bzero (p, (count * size));
	return (p);
}
