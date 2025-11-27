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
int	build_line(char **tobuild, char *str, int len)
{
	static int	builded_len = 0;
	char	*newstr;
	int		i;

	newstr = malloc (builded_len + len);
	if (*tobuild != NULL)
	{
		i = 0;
		while (i < builded_len)
		{
			newstr[i] = *tobuild[i];
			i++;
		}
	}
	i = 0;
	while (i < len)
	{
		newstr[builded_len + i] = str[i];
		if (str[i] == '\n')
		{
			builded_len += len;
			free(*tobuild);
			*tobuild = newstr;
			return (1);
		}
		i++;
	}
	builded_len += len;
	free(*tobuild);
	*tobuild = newstr;
	if (len < BUFFER_SIZE)
		return (1);
	return (0);
}
char	*get_next_line(int fd)
{
	int		read_bytes;
	char	buffer[BUFFER_SIZE];
	char	*next_line;
	
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	next_line = NULL;
	while (read_bytes != 0)
	{
		if (build_line(&next_line, buffer, read_bytes))
			return (next_line);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	return (next_line);
}
#include "stdio.h"
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
		printf("result: %s\n", next_line);
		free(next_line);
		next_line = get_next_line(fd);
	}
	// read(fd, b, sizeof(b));
	// if(!next_line)
	// while (*b)
	// 	i++;
	// printf("%i", i);

}