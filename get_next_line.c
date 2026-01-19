/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbastos- <bbastos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:18:10 by bbastos-          #+#    #+#             */
/*   Updated: 2026/01/16 16:26:44 by bbastos-         ###   ########.fr       */
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

	while (!ft_strchr(backup, '/n')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == NULL)
		return
	}	
}

static char	*set_line(char *line_buffer)
{
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	if (!backup)
		backup = ft_strdup("");
	if (backup == NULL)
	{
		free(buffer);
		return (NULL);
	}	
}
