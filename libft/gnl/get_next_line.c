/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:05:40 by krepo             #+#    #+#             */
/*   Updated: 2025/07/17 11:52:38 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		if (!buffer[0])
		{
			if (!read_buffer(fd, buffer, &line))
				return (line);
		}
		line = extract_line(line, buffer);
		if (!line)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
		{
			shift_buffer(buffer);
			return (line);
		}
		buffer[0] = '\0';
	}
}

int	read_buffer(int fd, char *buffer, char **line)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		if (!(*line)[0])
		{
			free(*line);
			*line = NULL;
		}
		return (0);
	}
	buffer[bytes_read] = '\0';
	return (1);
}

char	*extract_line(char *line, char *buffer)
{
	char	*joined;
	char	*tmp;
	size_t	newline;

	newline = ft_strchr(buffer, '\n') - buffer + 1;
	if (newline)
		tmp = ft_substr(buffer, 0, newline);
	else
		tmp = ft_strdup(buffer);
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(line, tmp);
	if (!joined)
		return (NULL);
	free(tmp);
	free(line);
	return (joined);
}

char	*shift_buffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strchr(buffer, '\n') - buffer + 1;
	while (buffer[j + i] != '\0')
	{
		buffer[i] = buffer[j + i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
