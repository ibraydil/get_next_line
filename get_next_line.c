/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dibrayev <dibrayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 17:13:27 by dibrayev          #+#    #+#             */
/*   Updated: 2026/10/30 19:45:01 by dibrayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*leftover;
	char *tmp;
	char *final_line;

	leftover = read_to_leftover(fd, leftover);
	if (leftover == NULL)
		return (NULL);
	final_line = get_line(leftover);
	tmp = leftover;
	leftover = cut_leftover(leftover);
	free(tmp);
	return (final_line);
}

char *get_line(char *leftover)
{
	char *line;
	int i;
	int j;

	i = index_position(leftover);
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = leftover[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char *cut_leftover(char *leftover)
{
	int i;
	int j;
	char *next_line;

	i = index_position(leftover);
	if (leftover[i] == '\0')
    	return (NULL);
	next_line = malloc(sizeof(char) * (ft_strlen(leftover) - i + 1));
	if (next_line == NULL)
		return (NULL);
	j = 0;
	while (leftover[i])
	{
		next_line[j] = leftover[i];
		j++;
		i++;
	}
	next_line[j] = '\0';
	return (next_line);
}

int index_position(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	if (str[i] == '\n')
		i++;
	return (i);
}

char *read_to_leftover(int fd, char *leftover)
{
	char    buf[BUFFER_SIZE + 1];
	ssize_t n;
	char *tmp;

	while (!ft_strchr(leftover, '\n'))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
		{
			free(leftover);
			return (NULL);
		}
		if (n == 0)
			break ;
		buf[n] = '\0';
		tmp = leftover;
		leftover = ft_strjoin(tmp, buf);
		free(tmp);
	}
	return (leftover);
}
