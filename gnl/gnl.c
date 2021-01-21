/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:11:24 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/20 20:22:22 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_getpos(char *str, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free(char *buffer)
{
	if (buffer)
		free(buffer);
}


int		ft_rallocat(char **buffer, int buffer_offset, char *src, int src_len)
{
	char *dest;
	int	i;
	int	y;
	dest = malloc((buffer_offset + src_len + 1) * sizeof(char));
	if (!dest)
		return (-1);
	i = 0;
	while (i < buffer_offset)
	{
		dest[i] = (*buffer)[i];
		i++;
	}
	y = 0;
	while (y < src_len)
		dest[i++] = src[y++];
	ft_free(*buffer);
	*buffer = dest;
	return (buffer_offset + src_len);
}

int		ft_rallocut(char **buffer, int buffer_offset, char **line, int cut)
{
	char *dest;
	int	i;
	int	y;
	
	dest = malloc((buffer_offset - cut) * sizeof(char));
	if (!dest)
		return (-1);
	*line = malloc((cut + 1) * sizeof(char));
	if (!line)
	{
		free(dest);
		return (-1);
	}
	i = 0;
	while (i < cut)
	{
		(*line)[i] = (*buffer)[i];
		i++;
	}
	(*line)[i++] = '\0';
	y = 0;
	while (i < buffer_offset)
		dest[y++] = (*buffer)[i++];
	ft_free(*buffer);
	*buffer = dest;
	return (buffer_offset - cut - 1);
}

int ft_gnl(char **line)
{
	char		buff[5];
	static char	*buffer = NULL;
	static int	buffer_offset = 0;
	int			pos;
	int			readed;


	while((pos = ft_getpos(buffer, buffer_offset)) == -1 && (readed = read(0, buff, sizeof(buff))) >= 0)
	{
		if (readed < 0)
		{
			ft_free(buffer);
			return (-1);
		}
		if (readed == 0)
		{
			ft_rallocut(&buffer, buffer_offset, line, buffer_offset);
			ft_free(buffer);
			return (0);
		}
		if ((buffer_offset = ft_rallocat(&buffer, buffer_offset, buff, readed)) == -1)
		{
			ft_free(buffer);
			return (-1);
		}
	}
	if ((buffer_offset = ft_rallocut(&buffer, buffer_offset, line, pos)) == -1)
	{
		ft_free(buffer);
		return (-1);
	}
	return (1);
}
