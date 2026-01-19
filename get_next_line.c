/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbastos- <bbastos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:18:10 by bbastos-          #+#    #+#             */
/*   Updated: 2026/01/19 14:57:43 by bbastos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	uc;

	uc = (unsigned char) c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((unsigned char) s[i] == uc)
			return ((char *)(s + i));
		i++;
	}
	if (uc == '\0')
		return ((char *)(s + i));
	return (NULL);
}

static char	*fill_line_buffer(int fd, char *backup)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(backup), NULL);
	while (!ft_strchr(backup, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(backup), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free(temp);
		if (!backup)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (backup);
}

static char	*set_line(char *backup)
{
	char	*newline_pos;
	size_t	len;

	if (!backup || backup[0] == '\0')
		return (NULL);
	newline_pos = ft_strchr(backup, '\n');
	if (newline_pos)
		len = newline_pos - backup + 1;
	else
		len = ft_strlen(backup);
	return (ft_substr(backup, 0, len));
}

static char	*update_backup(char *backup)
{
	char	*newline_pos;
	char	*new_backup;

	newline_pos = ft_strchr(backup, '\n');
	if (! newline_pos)
	{
		free(backup);
		return (NULL);
	}
	new_backup = ft_strdup(newline_pos + 1);
	free(backup);
	return (new_backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!backup)
		backup = ft_strdup("");
	if (!backup)
		return (NULL);
	backup = fill_line_buffer(fd, backup);
	if (!backup)
		return (NULL);
	line = set_line(backup);
	backup = update_backup(backup);
	return (line);
}
