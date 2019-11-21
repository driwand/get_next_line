/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:27:58 by abkssiba          #+#    #+#             */
/*   Updated: 2019/11/21 14:07:27 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		get_char_index(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == '\0')
		return (i);
	return (-1);
}

int		get_line(int x, int index, char **to_save, char **line)
{
	char *tmp;

	if (index == -1 && x == 0)
	{
		if (*(*to_save + index) == '\0')
		{
			*line = ft_substr(*to_save, 0, index);
			*to_save[0] = '\0';
			return (1);
		}
		free(*to_save);
		return (0);
	}
	if ((index != -1) || x == 0)
	{
		*line = ft_substr(*to_save, 0, index);
		tmp = *to_save;
		*to_save = ft_strdup(&tmp[index + 1]);
		free(tmp);
		return (1);
	}
	return (0);
}

int		get_rest(int x, char **to_save, char **line, int index)
{
	if (x < 0)
		return (-1);
	if (!*to_save)
		return (-1);
	if ((x == 0 && !*to_save[0]))
		return (0);
	if (x == 0)
		index = get_char_index(*to_save, '\n');
	if (get_line(x, index, to_save, line) == 1)
		return (1);
	return (0);
}

int		error_handle(int fd, char **line, char **buffer)
{
	if (!(*buffer = malloc(BUFFER_SIZE + 1)) || fd < 0 || !line)
		return (-1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*to_save[4864];
	char		*buffer;
	int			x;
	char		*tmp;
	int			index;

	if (error_handle(fd, line, &buffer) == -1)
		return (-1);
	while ((x = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[x] = '\0';
		if (!to_save[fd])
			to_save[fd] = ft_strdup(buffer);
		else
		{
			tmp = to_save[fd];
			to_save[fd] = ft_strjoin(to_save[fd], buffer);
			free(tmp);
		}
		if ((index = get_char_index(to_save[fd], '\n')) != -1 &&
				to_save[fd][index])
			break ;
	}
	free(buffer);
	return (get_rest(x, &to_save[fd], line, index));
}
