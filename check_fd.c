#include "irc_server.h"

void	check_fd(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->ret_sel > 0))
	{
		if (FD_ISSET(i, &e->readfds))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->writefds)) {
			printf("check fd i : %d\n", i);
			e->fds[i].fct_write(e, i);
		}
		if (FD_ISSET(i, &e->readfds) || FD_ISSET(i, &e->writefds))
			e->ret_sel--;
		i++;
	}
}