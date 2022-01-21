/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:32:18 by mlecherb          #+#    #+#             */
/*   Updated: 2022/01/17 10:03:51 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*c_line[255];
	char		buf[BUFFER_SIZE + 1];
	int			pos[2];

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, buf, 0) < 0)
		return (NULL);
	if (c_line[fd])
	{	
		pos[0] = ft_strrchr(c_line[fd], '\n');
		if (pos[0] != -1)
			return (ft_cutstr((&c_line[fd]), pos[0]));
	}
	pos[1] = read(fd, buf, BUFFER_SIZE);
	while (pos[1] > 0)
	{
		c_line[fd] = ft_fixnorm(c_line[fd], buf, pos[1]);
		pos[0] = ft_strrchr(c_line[fd], '\n');
		if (pos[0] != -1)
			return (ft_cutstr((&c_line[fd]), pos[0]));
		pos[1] = read(fd, buf, BUFFER_SIZE);
	}
	if (c_line[fd] == NULL)
		return (NULL);
	return (ft_aret(&c_line[fd]));
}

char	*ft_fixnorm(char *c_line, char *buf, int ret)
{
	buf[ret] = '\0';
	c_line = ft_strjoin(c_line, buf);
	return (c_line);
}

char	*ft_cutstr(char **str, int pos)
{
	char	*reste;
	int		len;

	reste = ft_substr(*str, 0, pos + 1);
	pos++;
	len = ft_strlen((*str) + pos);
	if (len != 0)
		ft_memmove((*str), (*str) + pos, len + 1);
	else
	{
		free(*str);
		*str = NULL;
	}
	return (reste);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (d > s)
		while (len-- > 0)
			d[len] = s[len];
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_aret(char **c_line)
{
	char	*aret;

	aret = ft_strdup(*c_line);
	free(*c_line);
	*c_line = NULL;
	return (aret);
}
