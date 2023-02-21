/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:07:48 by yoonslee          #+#    #+#             */
/*   Updated: 2022/11/03 16:25:27 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	out = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	out[i] = '\0';
	return (out);
}
