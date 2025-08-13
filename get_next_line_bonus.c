/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbano <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:03:03 by aalbano           #+#    #+#             */
/*   Updated: 2025/08/07 13:32:48 by aalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*new_rest(char **rest)
{
	char	*line;

	if (*rest)
	{
		line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	else
		line = NULL;
	return (line);
}

static char	*read_line(int fd, char *line, char *buffer)
{
	char	*ptr;
	char	*tmp;
	ssize_t	bytes;

	ptr = ft_strchr(line, '\n');
	bytes = 1;
	if (!line)
		line = ft_strdup("");
	while (!ptr && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
		if (!tmp)
			return (NULL);
		ptr = ft_strchr(line, '\n');
	}
	return (line);
}

void	update_line(char **line, char **rest)
{
	char	*ptr;

	ptr = ft_strchr(*line, '\n');
	if (ptr)
	{
		*rest = ft_strdup(ptr + 1);
		*(ptr + 1) = '\0';
	}
}

char	*get_next_line(int fd)
{
	static char	*rest[MAX_FD];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = new_rest(&rest[fd]);
	line = read_line(fd, line, buffer);
	free(buffer);
	if (!line || *line == '\0')
	{
		free(line);
		free(rest[fd]);
		rest[fd] = NULL;
		return (NULL);
	}
	update_line(&line, &rest[fd]);
	return (line);
}

/*int main()
{
	char *line;

	int fd = open("1.txt", O_RDONLY);
	int fd1 = open("2.txt", O_RDONLY);
	int fd2 = open("3.txt", O_RDONLY);

	while((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	while((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	while((line = get_next_line(fd2)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	close(fd1);
	close(fd2);
	return (0);
}*/
