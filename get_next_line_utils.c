/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:17:50 by abkssiba          #+#    #+#             */
/*   Updated: 2019/11/18 17:05:11 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = (char*)s;
	i = 0;
	while (i < len + 1)
	{
		if (str[i] == (char)c)
			return (&str[i+1]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;
	size_t i;

	i = 0;
	len = ft_strlen(s1);
	str = malloc(len + 1);
	bzero(str, len);
	if (str)
	{
		while (i < len)
		{
			str[i] = s1[i];
			i++;
		}
		str[len] = 0;
		return (str);
	}
	return (NULL);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;
	int	j;
	int i;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = (char*)malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (!str)
		return (NULL);
	while (++i < (int) ls1)
		str[i] = s1[i];
	j = 0;
	while (i < (int)(ls1 + ls2))
	{
		str[i++] = s2[j++];
	}
	str[ls1 + ls2] = '\0';
	return (str);
}

char    *ft_substr(char *s, unsigned int start, size_t len)
{
	char    *str;
	char    *p;
	char    *r;
	size_t    l;

	if (!s)
		return (NULL);
	l = ft_strlen(&s[start]);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	l = (l <= len) ? l : len;
	if (!(str = (char *)malloc(l + 1)))
		return (str);
	p = (char*)(s + start);
	r = str;
	while (*p && l--)
		*str++ = *p++;
	*str = '\0';
	return (r);
}
