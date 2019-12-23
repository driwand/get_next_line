/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:27:58 by abkssiba          #+#    #+#             */
/*   Updated: 2019/12/17 17:52:13 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int		get_line(int x, char **to_save, char **line, int index)
{
	char *tmp;

	if (x < 0)
		return (-1);
	if ((x == 0 && !*to_save))
	{
		*line = ft_strdup("");
		return (0);
	}
	index = (x == 0) ? get_char_index(*to_save, '\n') : index;
	tmp = *to_save;
	*line = ft_substr(*to_save, 0, index);
	if (*(*to_save + index) == '\0')
	{
		*to_save = NULL;
		free(tmp);
		return (0);
	}
	*to_save = ft_strdup(&tmp[index + 1]);
	free(tmp);
	if (!*to_save || !*line)
		return (-1);
	if (*to_save != NULL)
		return (1);
	return (-1);
}

int		error_handle(int fd, char **line, char **buffer)
{
	if (BUFFER_SIZE <= 0 || !line || fd < 0 || fd > 256
			|| !(*buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*to_save[256];
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
	return (get_line(x, &to_save[fd], line, index));
}
