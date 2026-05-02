/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:43:39 by nkuydin           #+#    #+#             */
/*   Updated: 2025/12/08 21:11:21 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	storage[fd] = ft_read_file(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = ft_get_line(storage[fd]);
	ft_update_storage(&storage[fd]);
	return (line);
}

char	*ft_read_file(int fd, char *storage)
{
	int		bytes;
	char	*buffer;

	bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while ((ft_strchr(storage, '\n') == 0) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
		if (bytes == -1)
			return (free(buffer), ft_free(storage));
	}
	free(buffer);
	return (storage);
}

char	*ft_get_line(char *storage)
{
	char	*newline;
	int		len;

	if (!storage || storage[0] == '\0')
		return (NULL);
	newline = ft_strchr(storage, '\n');
	if (newline != NULL)
		len = newline - storage + 1;
	else
		len = ft_strlen(storage);
	return (ft_substr(storage, 0, len));
}

void	ft_update_storage(char **storage)
{
	char	*newline;
	char	*new_storage;
	size_t	len;

	newline = ft_strchr(*storage, '\n');
	if (newline == NULL)
	{
		free(*storage);
		*storage = NULL;
		return ;
	}
	len = newline - *storage + 1;
	new_storage = ft_substr(*storage, len, ft_strlen(*storage) - len);
	free(*storage);
	*storage = new_storage;
}

char	*ft_free(char *storage)
{
	free(storage);
	storage = NULL;
	return (NULL);
}

// int	main(int argc, char **argv)
// {
// 	int		fd1;
// 	int		fd2;
// 	char	*line1;
// 	char	*line2;

// 	fd1 = open(argv[1], O_RDONLY);
// 	fd2 = open(argv[2], O_RDONLY);

// }