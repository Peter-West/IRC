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
				printf("write isset\n");
			}
			// e->max = (e->max > i ? e->max : i);
		}
		i++;
	}
}

void		do_select(t_env *e)
{
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	if ((e->ret_sel = select (MAX_FD + 1, &e->readfds, &e->writefds, NULL, &timeout)) < 0)
		ft_error(-1, "select ERROR");
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
	}
}
