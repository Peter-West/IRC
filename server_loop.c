#include "irc_server.h"
#include <unistd.h>

void		init_fd(t_env *e)
{
	int		i;

	i = 0;
	// e->max = 0;
	FD_ZERO(&e->readfds);
	FD_ZERO(&e->writefds);
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->readfds);
			if (ft_strlen(e->fds[i].buf_write) > 0)
			{
				FD_SET(i, &e->writefds);
			}
			// e->max = (e->max > i ? e->max : i);
		}
		i++;
	}
}

void		do_select(t_env *e)
{
	if ((e->ret_sel = select (MAX_FD + 1, &e->readfds, &e->writefds, NULL, NULL)) < 0)
		ft_error(-1, "select ERROR");
}

void		write_client(t_env *e) {
	int r;
int srv;

	srv = 0;
	while (srv < e->maxfd)
	{
		if (e->fds[srv].type == FD_SERV)
			break ;
		srv++;
	}
	r = read(0, &e->fds[srv].buf_write, BUF_SIZE);
	/*if (r > 0) {
		send()
	}*/
}

void		server_loop(t_env *e)
{
	printf("port : %d\n", e->port);	
	printf("sockfd : %d\n", e->sockfd);
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
		// write_client(e);
	}
}
