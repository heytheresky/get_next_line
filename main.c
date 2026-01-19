/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbastos- <bbastos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:52:29 by bbastos-          #+#    #+#             */
/*   Updated: 2026/01/19 15:02:59 by bbastos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Erro ao abrir ficheiro!\n");
		return (1);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Linha %d: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
