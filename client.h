#ifndef CLIENT_H
# define CLIENT_H
# define BUFF_SIZE 5

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <netinet/in.h>
/*
typedef struct		s_chan
{
	char			*name;
	struct s_chan	*next;
}					t_chan;*/

typedef struct		s_env
{
	char			*nickname;
	char			*chan;
	char			buf[BUFF_SIZE + 1];
}					t_env;

void		check_args(int argc, char **argv);
void		ft_error(int i, char *s);
int			init(char **argv);
void		client_loop(int sockfd);
void		input_line(t_env *e, int sockfd);
void		change_nick(t_env *e, char *line);
void		cmd(t_env *e, char *line);
void		join_chan(t_env *e, char *line);
void		leave_chan(t_env *e, char *line);
void		msg_user(t_env *e, char *line);
void		cmd_who();
void		cmd_connect();


#endif