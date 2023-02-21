/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:15:18 by yoonslee          #+#    #+#             */
/*   Updated: 2022/11/17 08:10:23 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
	{
		str = malloc (1);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	if (count * size % size != 0)
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (0);
	while (i < count * size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
