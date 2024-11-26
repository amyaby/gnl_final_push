/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabasala <iabasala@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:25:03 by iabasala          #+#    #+#             */
/*   Updated: 2024/11/25 20:36:26 by iabasala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_concat(int fd, char *leftover)
{
	int		read_bytes;
	char	*buff;
	char	*temp;

	buff = malloc((BUFFER_SIZE * sizeof(char)) + 1);
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while ((!leftover || !ft_strchr(leftover, '\n')) && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			return (free(leftover), leftover = NULL, NULL);
		}
		buff[read_bytes] = '\0';
		temp = ft_strjoin(leftover, buff);
		free(leftover);
		leftover = temp;
		if (!leftover)
			return (free(buff), NULL);
	}
	free(buff);
	return (leftover);
}

char	*extract_line(char *leftover)
{
	int		i;
	char	*str;

	i = 0;
	if (!leftover || !leftover[i])
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, leftover, i);
	str[i] = '\0';
	return (str);
}

char	*new_leftover(char *leftover)
{
	int		i;
	char	*str;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	if (!leftover[i])
	{
		return (free(leftover), NULL);
	}
	str = ft_strdup(leftover + i);
	free(leftover);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(leftover), leftover = NULL, NULL);
	leftover = read_and_concat(fd, leftover);
	if (!leftover)
		return (NULL);
	line = extract_line(leftover);
	leftover = new_leftover(leftover);
	return (line);
}
