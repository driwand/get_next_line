/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkssiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:27:58 by abkssiba          #+#    #+#             */
/*   Updated: 2019/11/19 17:38:00 by abkssiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_new_line(char *str)
{
	int i;
	int len;
	char *res;
	char *tmp;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '\n')
		{
			tmp = str;
			res = ft_substr(str, 0, i);
			return (res);
		}
		i++;
	}
	return (NULL); //should be NULL
}

int get_char_index(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int get_next_line(int fd, char **line)
{
	static char *to_save[4864];
	char *buffer;
	char *res;
	int x;
	int index;
	char *tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || !line)
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
		index = get_char_index(to_save[fd], '\n');
		if (index != -1)
			break;
	}
	if (x == -1)
        return (-1);
	if (x == 0 && !*to_save[fd])
	    return (0);
	if (x == 0)
        index = get_char_index(to_save[fd], '\n');
	if (index == -1 && x == 0)
	    return (0);
    if ((index != -1) || x == 0)
    {
        *line = ft_substr(to_save[fd], 0, index);
        tmp = to_save[fd];
        to_save[fd] = ft_strdup(&to_save[fd][index + 1]);
        free(tmp);
        return (1);
    }
	return (1);
}

int main()
{
    char *str;
    int fd = open("/Users/abkssiba/Desktop/projects/gnl/df", O_RDONLY);
    while (get_next_line(fd, &str) > 0)
    {
        printf("%s\n", str);
        free(str);
    }
	get_next_line(fd, &str);
	printf("%s\n", str);
	free(str);
//    get_next_line(fd, &str);
//    printf("%s\n", str);
//    free(str);
//
//	get_next_line(fd, &str);
//	printf("%s\n", str);
//    free(str);
//
//    get_next_line(fd, &str);
//    printf("%s\n", str);
//    free(str);
//
//    get_next_line(fd, &str);
//    printf("%s\n", str);
//    free(str);
//
//    get_next_line(fd, &str);
//    printf("%s\n", str);
//    free(str);
    return 0;
}
