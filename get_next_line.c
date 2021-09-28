/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjeronim <gjeronim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:11:38 by gjeronim          #+#    #+#             */
/*   Updated: 2021/09/23 21:16:27 by gjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
	#include <stdio.h>
	#include <fcntl.h>

char *read_file(int fd, char *backup, char *buffer)
{
	int reader;
	char *temp;

	reader = 1;
	while(reader != 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buffer);
			return NULL;
		}
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		buffer[reader] = '\0';
		backup = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return backup;
}

char *format_line(char *unformatted_line)
{
	int counter;
	char *formated_line;

	counter = 0;
	while (unformatted_line[counter] && unformatted_line[counter] != '\n')
		counter++;
	formated_line = (char *)malloc(counter + 2);
	if (!formated_line)
		return (NULL);
	ft_strlcpy(formated_line, unformatted_line, counter + 2);
	if (formated_line[0] == '\0')
	{
		free(formated_line);
		return NULL;
	}
	return formated_line;
}

char *format_backup(char *backup)
{
	int newline_ocurrence;
	char *line_remainder;

	newline_ocurrence = 0;
	while (backup[newline_ocurrence] != '\n' && backup[newline_ocurrence])
		newline_ocurrence++;
	if (backup[newline_ocurrence] == '\0')
	{
		free(backup);
		return (NULL);
	}
	line_remainder = malloc((ft_strlen(backup) - newline_ocurrence) + 1);
	if (!line_remainder)
		return (NULL);
	ft_strlcpy(line_remainder, backup + newline_ocurrence + 1, ft_strlen(backup) - newline_ocurrence + 1);
	free(backup);
	return line_remainder;
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if(!(buffer = (char *)malloc((BUFFER_SIZE + 1))))
	{
		free(buffer);
		return (NULL);
	}
	backup = read_file(fd, backup, buffer);
	if (!backup)
		return (NULL);
	line = format_line(backup);
	backup = format_backup(backup);
	return (line);
}

// int main(void)
// {
// 	int fd;
// 	char *result;
// 	fd = open("nl", 02);


// 	get_next_line(fd);
// 	// get_next_line(fd);

// }

