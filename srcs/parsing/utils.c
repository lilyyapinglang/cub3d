#include "../../includes/cub3d.h"

char	*ft_join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	free(text);
	return (temp);
}

char	*ft_next(char *text)
{
	int		i;
	int		j;
	char	*new_text;

	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (text[i] == '\0')
		return (free(text), NULL);
	i++;
	j = 0;
	while (text[i + j])
		j++;
	new_text = ft_calloc(j + 1, sizeof(char));
	if (!new_text)
		return (free(text), NULL);
	j = 0;
	while (text[i + j] != '\0')
	{
		new_text[j] = text[i + j];
		j++;
	}
	free(text);
	return (new_text);
}

char	*ft_line(char *text)
{
	char	*line;
	int		i;

	i = 0;
	if (!text[0])
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (text[i] && text[i] != '\n')
	{
		line[i] = text[i];
		i++;
	}
	if (text[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_first_line(int fd, char *text)
{
	char	*buffer;
	int		bytes_read;

	if (!text)
		text = ft_calloc(1, 1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free (buffer), free (text), NULL);
		buffer[bytes_read] = '\0';
		text = ft_join_and_free(text, buffer);
		if (!text)
			return (free(buffer), NULL);
		if (ft_strchr(text, '\n'))
			break ;
	}
	free (buffer);
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (text)
		{
			free(text);
			text = NULL;
		}
		return (NULL);
	}
	text = read_first_line(fd, text);
	if (!text)
		return (NULL);
	line = ft_line(text);
	text = ft_next(text);
	return (line);
}
