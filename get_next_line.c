/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:06:18 by aberrami          #+#    #+#             */
/*   Updated: 2025/11/26 11:06:18 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include <stdio.h>

char	*get_next_line(int fd)
{
	int			read_bytes;
	char		buffer[BUFFER_SIZE];
	char		*next_line;
	static char	*remaining_str = NULL;

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	next_line = NULL;
	while (read_bytes != 0)
	{
		if (build_line(&next_line, buffer, read_bytes, &remaining_str))
			return (next_line);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (remaining_str != NULL)
	{
		next_line = remaining_str;
		remaining_str = NULL;
	}
	return (next_line);
}
// #include "stdio.h"
// #include <fcntl.h>
// int main()
// {
// 	// char b[100];
// 	// int i = 0;
// 	// int fd = open("test.txt", O_RDONLY);
// 	int fd = 0;
// 	char *next_line = get_next_line(STDIN_FILENO);
// 	if(fd == -1)
// 		printf("Error opening the file");
// 	while (next_line != NULL)
// 	{
// 		printf("next line: %s", next_line);
// 		free(next_line);
// 		next_line = NULL;
// 		next_line = get_next_line(fd);
// 		// printf("another call\n");
// 	}
// 	// close(fd);
// }