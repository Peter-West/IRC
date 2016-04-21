#include "client.h"

void			check_fd(t_env *e)
{
/*	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->ret_sel > 0))
	{*/
		printf("FD_ISSET(e->sockfd, &e->readfds) : %d\n", FD_ISSET(e->sockfd, &e->readfds));
		if (FD_ISSET(e->sockfd, &e->readfds))
		{
			printf("fd isset !\n");
			e->fct_read(e, e->sockfd);
		}
		if (FD_ISSET(e->sockfd, &e->writefds))
		{
			// printf("check fd writefds i : %d\n", i);
			e->fct_write(e, e->sockfd);
		}
		if (FD_ISSET(e->sockfd, &e->readfds) || FD_ISSET(e->sockfd, &e->writefds))
			e->ret_sel--;
/*		i++;
	}*/
}

void			do_select(t_env *e)
{
	struct timeval timeout;

	e->ret_sel = select(e->maxfd + 1, &e->readfds, &e->writefds, NULL, timeout);
	printf("e->ret_sel : %d\n", e->ret_sel);
}
/*
void			clean_fd(t_env	*e)
{
	e->type = FD_FREE;
	e->fct_read = NULL;
	e->fct_write = NULL;
}*/

void			client_accept(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	cs = accept(s, (struct sockaddr*)&csin, &csin_len);
	printf("New connection #%d from %s:%d\n", cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	// clean_fd(e);
	e->type = FD_CLIENT;
	e->fct_read = input_line;
	e->fct_write = rcv_msg;
	e->nickname = "user";
	e->chan = NULL;
}

void			init_fd(t_env *e)
{
	// int		i;

	// i = 0;
	// e->max = 0;
	FD_ZERO(&e->readfds);
	FD_ZERO(&e->writefds);
/*	while (i < e->maxfd)
	{*/
		if (e->type != FD_FREE)
		{
			printf("type : %d\n", e->type);
			FD_SET(e->sockfd, &e->readfds);
			if (ft_strlen(e->buf_write) > 0)
			{
				FD_SET(e->sockfd, &e->writefds);
			}
			// e->max = (e->max > i ? e->max : i);
		}
		/*i++;
	}*/
}