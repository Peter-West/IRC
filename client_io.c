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

void	client_read(t_env *e, int cs)
{
	int		r;
	int		i;
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
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		if (line[0] == '/')
			cmd(e, cs, line);
		else
		{	
			i = 0;
			while (i < e->maxfd)
			{
				if ((e->fds[i].type == FD_CLIENT) &&
					(i != cs))
					send(i, line, r, 0);
				i++;
			}
		}
	}
	// ft_bzero(line, BUF_SIZE);
}

void	client_write(t_env *e, int cs)
{
	/*int tmp = cs;
	int tmp0 = e->maxfd;
	tmp++;
	tmp0++;*/
	int	r;
	int	i;
	int srv;

	srv = 0;
	while (srv < e->maxfd)
	{
		if (e->fds[srv].type == FD_SERV)
			break ;
		srv++;
	}
	printf("fd srv : %d et CS :%d\n", srv, cs);
	i = 0;
	if ((r = read(0, &e->fds[srv].buf_write, BUF_SIZE)))
	{
		printf("debug : %s\n", e->fds[srv].buf_write);
		while (i < e->maxfd) {
			if (e->fds[i].type == FD_CLIENT && i != srv)
				send(i, e->fds[srv].buf_write, r, 0);
			i++;
		}
	}
}