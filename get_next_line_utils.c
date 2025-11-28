/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberrami <aberrami@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:05:36 by aberrami          #+#    #+#             */
/*   Updated: 2025/11/28 22:05:36 by aberrami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	extend_and_copy(char **tobuild, int builded_len, int read_bytes,
	char **remaining_str)
{
	char	*newstr;
	int		i;

	i = -1;
	newstr = malloc(builded_len + read_bytes + 1);
	if (*tobuild != NULL)
	{
		while (++i < builded_len)
			newstr[i] = (*tobuild)[i];
		free(*tobuild);
	}
	else if (*remaining_str != NULL)
	{
		i = -1;
		while ((*remaining_str)[++i] != '\0')
			newstr[i] = (*remaining_str)[i];
		free(*remaining_str);
		*remaining_str = NULL;
	}
	*tobuild = newstr;
}

void	stash_str(char **remaining_str, char *buffer, int reached_i,
		int read_bytes)
{
	char	*newstr;
	int		j;

	newstr = malloc(read_bytes - reached_i - 1 + 1);
	j = 0;
	while ((reached_i + j) < read_bytes)
	{
		newstr[j] = buffer[reached_i + j];
		j++;
	}
	newstr[j] = '\0';
	*remaining_str = newstr;
}

int	build_line(char **tobuild, char *buffer, int read_bytes,
		char **remaining_str)
{
	static int	builded_len = 0;
	int			i;

	builded_len += ft_strlen(*remaining_str);
	extend_and_copy(tobuild, builded_len, read_bytes, remaining_str);
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
