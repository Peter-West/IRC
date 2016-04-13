#include "irc_server.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	printf("%s", e->fds[cs].buf_read);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) &&
				(i != cs))
				send(i, e->fds[cs].buf_read, r, 0);
			i++;
		}
	}
	ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
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