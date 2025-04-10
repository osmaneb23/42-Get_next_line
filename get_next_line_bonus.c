/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/01/06 23:34:02 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*stash[4096];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 4095 || read(fd, &line, 0) < 0)
		return (NULL);
	add_buffer(stash, fd);
	if (!stash[fd])
		return (NULL);
	line = add_line(stash[fd]);
	clear_stash(&stash[fd]);
	return (line);
}

void	add_buffer(t_list **stash, int fd)
{
	size_t	nb_bytes;
	char	*buffer;

	while (!search_nl(stash[fd]))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		nb_bytes = read(fd, buffer, BUFFER_SIZE);
		if (nb_bytes <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[nb_bytes] = 0;
		add_stash(buffer, stash, fd);
	}
}

void	add_stash(char *buffer, t_list **stash, int fd)
{
	t_list	*node;
	t_list	*last;

	last = last_node(stash[fd]);
	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	node->content = buffer;
	node->next = NULL;
	if (!last)
		stash[fd] = node;
	else
		last->next = node;
}

char	*add_line(t_list *stash)
{
	char	*line;

	if (!stash)
		return (NULL);
	line = malloc(len_for_line(stash) + 1);
	if (!line)
		return (NULL);
	copy_str(stash, line);
	return (line);
}

void	clear_stash(t_list **stash)
{
	t_list	*node;
	t_list	*last;
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	node = malloc(sizeof(t_list));
	if (!buffer || !node)
		return ;
	last = last_node(*stash);
	while (last->content[i] && last->content[i] != '\n')
		i++;
	while (last->content[i] && last->content[i++])
		buffer[j++] = last->content[i];
	buffer[j] = 0;
	node->content = buffer;
	node->next = NULL;
	lstclear(stash, node, buffer);
}
