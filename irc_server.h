#ifndef IRC_SERVER_H
# define IRC_SERVER_H
# define MAX_FD			10
# define BUF_SIZE		5

# define FD_FREE		0
# define FD_SERV		1
# define FD_CLIENT		2

# include "libft.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdio.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/resource.h>

typedef struct			s_fd
{
	int					type;
	void				(*fct_read)();
	void				(*fct_write)();
	char				buf_read[BUF_SIZE + 1];
	char				buf_write[BUF_SIZE + 1];
	char				*nickname;
	char				*channel;	
}						t_fd;

typedef struct			s_env
{
	int					port;
	int					sockfd;
	int					sock_cli;
	int					ret_sel;
	socklen_t			cli_len;
	struct sockaddr_in	serv_ad;
	struct sockaddr_in	cli_ad;
	fd_set				readfds;
	fd_set				writefds;
	int					maxfd;
	t_fd				*fds;
}						t_env;

void		fd_env(t_env *e);
void		init_env(t_env *e);
void		clean_fd(t_fd *fd);
void		check_fd(t_env *e);
void		ft_check_port(t_env *e, char *port);
void		ft_error(int i, char *s);
void		server_loop(t_env *e);
int			msg_received(t_env *e, int fd);
void		init_fd(t_env *e);
void		srv_accept(t_env *e, int s);
void		do_select(t_env *e);
void		client_read(t_env *e, int cs);
void		client_write(t_env *e, int cs);
int			check_nl(char *str, char **line);
void		cmd(t_env *e, int cs, char *line);
void		change_nick_serv(t_env *e, int cs, char *line);
void		cmd_who(t_env *e, int cs);
void		join_chan(t_env *e, int cs, char *line);
void		leave_chan(t_env *e, int cs, char *line);
void		msg_user(t_env *e, char *line);
void		cmd_connect(t_env *e, int cs);
char		*ret_string_split(char *line, int s);


#endif