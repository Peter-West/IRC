/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:12:23 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:12:25 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

int			check_nl(char *str, char **line)
{
	int			i;

	i = 0;
	if (!(*line))
		*line = "";
	*line = ft_strjoin(*line, str);
	while (str[i] != 0)
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void		client_close(t_env *e, int cs)
{
	close(cs);
	clean_fd(&e->fds[cs]);
	printf("client #%d gone away\n", cs);
	e->fds[cs].type = FD_FREE;
	e->fds[cs].nickname = NULL;
	e->fds[cs].channel = NULL;
	clean_fd(&e->fds[cs]);
}

void		process_line(t_env *e, int cs, char *line)
{
	int	i;

	line = ft_strtrim(line);
	printf("line : %s\n", line);
	if (line[0] == '/')
		cmd(e, cs, line);
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) && e->fds[cs].channel
				&& e->fds[i].channel && (i != cs)
				&& !ft_strcmp(e->fds[i].channel, e->fds[cs].channel))
			{
				send(i, line, ft_strlen(line), 0);
				printf("sent to %s, on %s\n", e->fds[i].nickname,
					e->fds[i].channel);
			}
			i++;
		}
	}
}

void		client_read(t_env *e, int cs)
{
	int		r;
	char	*line;

	line = NULL;
	ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
	while ((r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)))
	{
		if (check_nl(e->fds[cs].buf_read, &line))
			break ;
		ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
	}
	if (!line)
		client_close(e, cs);
	else
		process_line(e, cs, line);
	if (line)
		free(line);
}

int			ret_fd_value(char *s)
{
	int		i;
	int		j;
	char	fd[4];

	i = 0;
	j = 0;
	while (s[i] != ' ')
	{
		if (s[i] != '#')
		{
			fd[j] = s[i];
			j++;
		}
		i++;
	}
	return (ft_atoi(fd));
}
