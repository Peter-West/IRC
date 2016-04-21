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
		e->fds[cs].type = FD_FREE;
		e->fds[cs].nickname = NULL;
		e->fds[cs].channel = NULL;
		clean_fd(&e->fds[cs]);
	}
	else
	{
		line = ft_strtrim(line);
		printf("line : %s\n", line);
		if (line[0] == '/')
		{
			printf("CMD\n");
			cmd(e, cs, line);
		}
		else
		{	
			i = 0;
			while (i < e->maxfd)
			{
				if ((e->fds[i].type == FD_CLIENT) &&
					(i != cs))
				{
					send(i, line, ft_strlen(line), 0);
					printf("to : %d, line sent : %s\n", i, line);
				}
				i++;
			}
		}
	}
	if (line)
		free(line);
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
	printf("Hmmmm ** fd srv : %d et CS :%d\n", srv, cs);
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