#ifndef CLIENT_H
# define CLIENT_H
# define BUF_SIZE 5

# define FD_FREE		0
# define FD_CLIENT		1

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <netinet/in.h>

typedef struct		s_env
{
	int				type;
	char			*nickname;
	char			*chan;
	int				sockfd;
	int				maxfd;
	int				ret_sel;
	fd_set			readfds;
	fd_set			writefds;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read[BUF_SIZE + 1];
	char			buf_write[BUF_SIZE + 1];
}					t_env;

void		check_args(int argc, char **argv);
void		ft_error(int i, char *s);
int			init(char **argv);
void		client_loop(int sockfd);
void		input_line(t_env *e, int cs);
void		change_nick(t_env *e, char *line);
void		cmd(t_env *e, char *line);
void		join_chan(t_env *e, char *line);
void		leave_chan(t_env *e, char *line);
void		msg_user(t_env *e, char *line);
void		cmd_who();
void		cmd_connect(t_env *e, char *line);
void		connect_serv(int argc, char **argv);
void		do_select(t_env *e);
void		check_fd(t_env *e);
void		client_accept(t_env *e, int s);
void		init_fd(t_env *e);
void		rcv_msg(t_env *e, int cs);

#endif