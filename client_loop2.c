#include "client.h"

void			check_fd(t_env *e)
{
	if (FD_ISSET(e->sockfd, &e->readfds))
	{
		printf("fct recv ptr :  %p\n", e->fct_recv);
		printf("fct recv ptr :  %p\n", &e->fct_recv);
		e->fct_recv(e, e->sockfd);
	}
	if (FD_ISSET(0, &e->readfds))
	{
		printf("fct read ptr :  %p\n", e->fct_read);
		printf("fct read ptr :  %p\n", &e->fct_read);
		e->fct_read(e, e->sockfd);
	}
	if (FD_ISSET(e->sockfd, &e->writefds))
	{
		e->fct_write(e, e->sockfd);
	}
}

void			do_select(t_env *e)
{
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	e->ret_sel = select(e->sockfd + 1, &e->readfds, &e->writefds, NULL, &timeout);
}

void			client_accept(t_env *e, int s)
{
	(void)s;
	e->type = FD_CLIENT;
	e->fct_read = input_line;
	e->fct_recv = rcv_msg;
	e->fct_write = send_msg;
	printf("ACCPT, fct recv ptr :  %p\n", e->fct_recv);
	printf("ACCPT, fct recv ptr :  %p\n", &e->fct_recv);
	e->nickname = "user";
	e->chan = NULL;
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