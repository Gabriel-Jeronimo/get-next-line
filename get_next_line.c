/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjeronim <gjeronim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:11:38 by gjeronim          #+#    #+#             */
/*   Updated: 2021/09/22 19:39:50 by gjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
	#include <stdio.h>
	#include <fcntl.h>

char *format_line(char *unformatted_line)
{
	int counter;
	char *formated_line;

	counter = 0;
	while (unformatted_line[counter] && unformatted_line[counter] != '\n')
		counter++;
	formated_line = (char *)malloc(sizeof(char) * (counter + 2));
	ft_strlcpy(formated_line, unformatted_line, counter + 2);
	if (formated_line[0] == '\0')
		return NULL;
	return formated_line;
}

char *format_backup(char *backup)
{
	int counter;
	int newline_ocurrence;
	char *line_remainder;


	counter = 0;
	newline_ocurrence = 0;
	while (backup[newline_ocurrence] && backup[newline_ocurrence] != '\n')
		newline_ocurrence++;
	while (backup[counter])
		counter++;
	line_remainder = malloc(counter + 1);
	ft_strlcpy(line_remainder, backup + newline_ocurrence + 1, counter);
	return line_remainder;
	free(backup);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *backup;
	int reader;
	char *temp;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	if(!(buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1))))
		return ("-1");

	reader = 1;
	while(reader != 0 && !ft_strchr(buffer, '\n'))
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		buffer[reader] = 0;
		backup = ft_strjoin(temp, buffer);
		free(temp);
	}
	line = format_line(backup);
	backup = format_backup(backup);
	return line;
}

int main(void)
{
	int fd;
	char *result;
	// fd = open("aquela_foda_dos_beatles", 02);
	fd = open("passaro", 02);
	while (result = get_next_line(fd))
	{
		printf("%s", result);
	}

	// get_next_line(fd);
	// get_next_line(fd);

}

