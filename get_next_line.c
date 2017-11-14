/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburnouf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:30:09 by tburnouf          #+#    #+#             */
/*   Updated: 2017/10/28 15:30:10 by tburnouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strjoinch(char const *s1, char c)
{
	char	*str;
	size_t	i;
	size_t	len;
	
	if (!s1 || !c)
		return (NULL);
	len = ft_strlen(s1);
	str = ft_strnew(len + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len)
		*(str + i) = *(s1 + i);
	*(str + i) = c;
	return (str);
}

int				ft_copyuntil(char **dst, char *src, char c)
{
	int	i;
	int	count;
	int	pos;
	
	i = -1;
	count = 0;
	while (src[++i])
		if (src[i] == c)
			break ;
	pos = i;
	if (!(*dst = ft_strnew(i)))
		return (0);
	while (src[count] && count < i)
	{
		if (!(*dst = ft_strjoinch(*dst, src[count])))
			return (0);
		count++;
	}
	return (pos);
}

static t_list	*correct_file(t_list **file, int fd)
{
	t_list	*tmp;
	
	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*file;
	int				i;
	int				ret;
	t_list			*curr;
	
	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		|| !(*line = ft_strnew(1)))
		return (-1);
	curr = correct_file(&file, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		curr->content = ft_strjoin(curr->content, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !(ft_strlen(curr->content)))
		return (0);
	i = ft_copyuntil(line, curr->content, '\n');
	if (i < (int)ft_strlen(curr->content))
		curr->content += (i + 1);
	else
		ft_strclr(curr->content);
	return (1);
}
