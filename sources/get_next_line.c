/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:02:09 by imisumi           #+#    #+#             */
/*   Updated: 2023/04/08 16:36:24 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(char *s)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * gnl_strlen(s) + 1);
	if (!dup)
		return (NULL);
	dup[0] = '\0';
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	i = -1;
	j = 0;
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	if (s1_len + s2_len == 0)
		return (NULL);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (free(s1), str);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	char	*str;

	s_len = gnl_strlen(s);
	i = start;
	j = 0;
	if (!s)
		return (0);
	if (len > s_len && (size_t)start < s_len)
		len = s_len - start;
	if ((size_t)start > s_len)
		len = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s_len > start && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((char)c == '\0')
	{
		while (s[i] != '\0')
			i++;
		return ((char *) s + i);
	}
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *) s + i);
		i++;
	}
	return (NULL);
}

// recreates str without the current \n NO
char	*trim_line(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	if (!str)
		return (free(str), NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			temp = gnl_strdup(str + (i + 1));
			free(str);
			if (!temp)
				return (NULL);
			str = temp;
			return (str);
		}
		i++;
	}
	if (!str[i])
		return (free(str), NULL);
	return (NULL);
}

// return the current \n NO
char	*sub_line(char *str)
{
	char	*temp;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	temp = gnl_substr(str, 0, i + 1);
	return (temp);
}

// reads file
char	*read_fd(int fd, char *str)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		i;

	i = 1;
	buffer[0] = '\0';
	while (i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (free(str), NULL);
		buffer[i] = '\0';
		temp = gnl_strjoin(str, buffer);
		if (!temp)
			return (free(str), NULL);
		str = temp;
		if (str[0] == '\0')
			return (free(str), NULL);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	if (!str[0])
		return (free(str), NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!str)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	str = read_fd(fd, str);
	if (!str)
		return (NULL);
	current_line = sub_line(str);
	if (!current_line)
		return (NULL);
	str = trim_line(str);
	return (current_line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	printf("BUFFER = %i\n", BUFFER_SIZE);
// 	fd = open("giant_line.txt", O_RDONLY);
// 	while (i < 10)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	system("leaks -q a.out");
// 	close(fd);
// 	return (0);
// }