/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvolikov <pvolikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:54:03 by pvolikov          #+#    #+#             */
/*   Updated: 2025/07/22 15:00:14 by pvolikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft.h>
#include "get_next_line.h"

//helper for helper
static void	correctly_update_buf(const char *newline, char **buf)
{
	char	*rest;

	if (newline)
	{
		rest = ft_strdup(newline + 1);
		free(*buf);
		*buf = rest;
	}
	else
	{
		free(*buf);
		*buf = NULL;
	}
}

// Helper: Extract line from buffer and update buffer pointer
static char	*extract_line(char **buf)
{
	char	*newline;
	char	*line;
	size_t	len;
	size_t	i;

	newline = ft_strchr(*buf, '\n');
	if (newline)
		len = newline - *buf + 1;
	else
		len = ft_strlen(*buf);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = (*buf)[i];
		i++;
	}
	line[len] = '\0';
	correctly_update_buf(newline, buf);
	return (line);
}

int	nl_in_buf(char *buf)
{
	if (! buf)
		return (0);
	if (ft_strchr(buf, '\n'))
		return (1);
	return (0);
}

static void	carefully_update_buf_with_tmp(char **buf, char *tmp)
{
	char	*joined;

	if (!*buf)
		*buf = ft_strdup(tmp);
	else
	{
		joined = ft_strjoin(*buf, tmp);
		free(*buf);
		*buf = joined;
	}
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		tmp[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!nl_in_buf(buf))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), buf = NULL, NULL);
		if (bytes_read == 0)
			break ;
		tmp[bytes_read] = '\0';
		carefully_update_buf_with_tmp(&buf, tmp);
	}
	if (buf && *buf)
		return (extract_line(&buf));
	return (free(buf), buf = NULL, NULL);
}
