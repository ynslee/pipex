/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:45:30 by yoonslee          #+#    #+#             */
/*   Updated: 2022/12/01 14:29:59 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*out;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	out = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!out)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			out[i] = s1[i];
	while (s2[j] != '\0')
		out[i++] = s2[j++];
	out[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	s1 = NULL;
	return (out);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
	{
		str = malloc (1);
		if (!str)
			return (NULL);
		return (str);
	}
	if (count * size / size != count)
		return (NULL);
	str = (void *)malloc(count * size);
	if (!str)
		return (0);
	while (i < count * size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
