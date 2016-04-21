#include "client.h"

void			check_fd(t_env *e)
{
	if (FD_ISSET(e->sockfd, &e->readfds))
		e->fct_recv(e, e->sockfd);
	if (FD_ISSET(0, &e->readfds))
		e->fct_read(e, e->sockfd);
	if (FD_ISSET(e->sockfd, &e->writefds))
		e->fct_write(e, e->sockfd);
}

void			do_select(t_env *e)
{
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	e->ret_sel = select(e->sockfd + 1, &e->readfds, &e->writefds, NULL, &timeout);
}

void			init_fd(t_env *e)
{
	FD_ZERO(&e->readfds);
	FD_ZERO(&e->writefds);
	if (e->type != FD_FREE)
	{
		FD_SET(e->sockfd, &e->readfds);
		FD_SET(0, &e->readfds);
		if (ft_strlen(e->buf_read) > 0)
			FD_SET(e->sockfd, &e->writefds);
	}
}