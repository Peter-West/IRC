#include "irc_server.h"

void			srv_accept(t_env *e, int s)
{
	int			cs;
	struct sockaddr_in	csin;
	socklen_t		csin_len;

	csin_len = sizeof(csin);
	cs = accept(s, (struct sockaddr*)&csin, &csin_len);
	printf("New client #%d from %s:%d\n", cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clean_fd(&e->fds[cs]);
	e->fds[cs].type = FD_CLIENT;
	printf("e->fds[cs].type : %d\n", e->fds[cs].type);
	e->fds[cs].fct_read = client_read;
  	printf("e->fds[e->sockfd].fct_write0 : %p\n", e->fds[cs].fct_write);
	e->fds[cs].fct_write = client_write;
  	printf("e->fds[e->sockfd].fct_write1 : %p\n", e->fds[cs].fct_write);
}
