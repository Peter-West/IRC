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

typedef struct		s_chan
{
	char			*name;
	struct s_chan	*next;
}					t_chan;

typedef struct		s_env
{
	char			*nickname;
	t_chan			chan;
}					t_env;

void		check_args(int argc, char **argv);
void		ft_error(int i, char *s);
int			init(char **argv);
void		client_loop(int sockfd);
void		send_msg(int sockfd);


#endif