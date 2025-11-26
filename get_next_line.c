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

// char	*get_next_line(int fd)
// {
// 	char buffer[255];
// 	char 
// }
#include "stdio.h"
#include <fcntl.h>
int main()
{
	char b[100];
	int i = 0;
	int fd = open("test.txt", O_RDONLY);
	if(fd == -1)
		printf("Error opening the file");
	read(fd, b, sizeof(b));
	printf("result: %s\n", b);
	while (*b)
		i++;
	printf("%i", i);

}