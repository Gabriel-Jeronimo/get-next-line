/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjeronim <gjeronim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:11:38 by gjeronim          #+#    #+#             */
/*   Updated: 2021/10/07 13:22:39 by gjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_file(int fd, char *backup, char *buffer);
static char	*format_line(char *unformatted_line);
static char	*format_backup(char *backup);

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*backup[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	backup[fd] = read_file(fd, backup[fd], buffer);
	if (!backup[fd])
		return (NULL);
	line = format_line(backup[fd]);
	backup[fd] = format_backup(backup[fd]);
	return (line);
}

static char	*read_file(int fd, char *backup, char *buffer)
{
	int		reader;
	char	*temp;

	reader = 1;
	while (reader != 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buffer);
			return (NULL);
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
	return (backup);
}

static char	*format_line(char *unformatted_line)
{
	int		counter;
	char	*formated_line;

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
		return (NULL);
	}
	return (formated_line);
}

static char	*format_backup(char *backup)
{
	int		newline_ocurrence;
	char	*line_remainder;

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
	ft_strlcpy(line_remainder, backup + newline_ocurrence
		+ 1, ft_strlen(backup) - newline_ocurrence + 1);
	free(backup);
	return (line_remainder);
}
