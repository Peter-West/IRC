#include "irc_server.h"

void			srv_accept(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	cs = accept(s, (struct sockaddr*)&csin, &csin_len);
	printf("New client #%d from %s:%d\n", cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clean_fd(&e->fds[cs]);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	e->fds[cs].nickname = "user";
	e->fds[cs].channel = NULL;

	// send(cs, "yo\n", 3, 0);
}
