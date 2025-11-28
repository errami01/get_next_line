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
#include <stdio.h>

// void	line_concat(char **tobuild, int start, char *newpart, len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		*tobuild[start + i] = newpart[i];
// 		i++;
// 	}
// }

//allocate new memory to fit new read bytes
void	extend_and_copy(char **tobuild, int builded_len, int read_bytes)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc (builded_len + read_bytes);
	if (*tobuild != NULL)
	{
		while (i < builded_len)
		{
			newstr[i] = (*tobuild)[i];
			i++;
		}
		free(*tobuild);
	}
	*tobuild = newstr;
}
void	stash_str(char **remaining_str, char *buffer, int reached_i, int read_bytes)
{
	char	*newstr;
	int		j;

	newstr = malloc(read_bytes - reached_i - 1);
	j = 0;
	while ((reached_i + j) < read_bytes)
	{
		newstr[j] = buffer[reached_i + j];
		j++;
	}
	// free(*remaining_str);
	*remaining_str = newstr;
	printf("remainings: %s", *remaining_str);
}
int	build_line(char **tobuild, char *buffer, int read_bytes, char **remaining_str)
{
	static int	builded_len = 0;
	int		i;
	
	extend_and_copy(tobuild, builded_len, read_bytes);
	i = 0;
	while (i < read_bytes)
	{
		(*tobuild)[builded_len + i] = buffer[i];
		if (buffer[i] == '\n')
		{
			if ((i + 1) < read_bytes)
				stash_str(remaining_str, buffer, (i + 1), read_bytes);
			builded_len = 0;
			return (1);
		}
		i++;
	}
	builded_len += read_bytes;
	if (read_bytes < BUFFER_SIZE)
	{
		builded_len = 0;
		return (1);
	}
	return (0);
}
char	*get_next_line(int fd)
{
	int		read_bytes;
	char	buffer[BUFFER_SIZE];
	static	char	*remaining_str = NULL;
	char	*next_line;
	
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	next_line = NULL;
	// printf("read bytes: %i", read_bytes);
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
#include <fcntl.h>
int main()
{
	// char b[100];
	// int i = 0;
	int fd = open("test.txt", O_RDONLY);
	char *next_line = get_next_line(fd);
	if(fd == -1)
		printf("Error opening the file");
	while (next_line != NULL)
	{
		printf("%s", next_line);
		free(next_line);
		next_line = NULL;
		next_line = get_next_line(fd);
	}
	// printf("%s", "hello\n new line\n");

	// read(fd, b, sizeof(b));
	// if(!next_line)
	// while (*b)
	// 	i++;
	// printf("%i", i);
	close(fd);
}