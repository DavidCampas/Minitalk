/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:56:07 by dcampas-          #+#    #+#             */
/*   Updated: 2025/01/10 15:57:41 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strncpy(char *dst, const char *src, size_t dstsize)
{
	size_t		srcsize;
	const char	*src_ptr;
	char		*dst_ptr;
	size_t		p;

	srcsize = 0;
	src_ptr = src;
	dst_ptr = dst;
	while (*src_ptr != '\0')
	{
		srcsize++;
		src_ptr++;
	}
	if (dstsize == 0 || dst == NULL)
		return (srcsize);
	p = 0;
	while (p < (dstsize - 1) && *src != '\0')
	{
		*dst_ptr = *src;
		dst_ptr++;
		src++;
		p++;
	}
	*dst_ptr = '\0';
	return (srcsize);
}
