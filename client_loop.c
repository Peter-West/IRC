#include "client.h"

void		cmd(t_env *e, char *line)
{
	if (!ft_strncmp("/nick ", line, 6))
		change_nick(e, line);
	else if (!ft_strncmp("/join ", line, 6))
		join_chan(e, line);
	else if (!ft_strncmp("/leave ", line, 6))
		leave_chan(e, line);
	else if (!ft_strncmp("/msg ", line, 4))
		msg_user(e, line);
	else if (!ft_strncmp("/who\n", line, 5))
		cmd_who();
	else if (!ft_strncmp("/connect ", line, 9))
		cmd_connect(e, line);
	else
		printf("Command unknown\n");
}

int			check_nl(char *str, char **line)
{
	int			i;

	i = 0;
	if (!(*line))
		*line = "";
	*line = ft_strjoin(*line, str);
	while (str[i] != 0)
	{		
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	input_line(t_env *e, int cs)
{
	int		read_ret;
	(void)cs;

	read_ret = 0;
	ft_bzero(e->buf_read, BUF_SIZE);
	read_ret = read(0, &e->buf_read, BUF_SIZE);
	e->buf_read[read_ret] = '\0';
	if (e->buf_read[0] == '/')
		cmd(e, e->buf_read);
	ft_strcat(e->buf_write, e->buf_read);
}

void	send_msg(t_env *e, int cs)
{
	(void)cs;
	send(e->sockfd, e->buf_write, ft_strlen(e->buf_write), 0);
	ft_bzero(e->buf_write, BUF_SIZE);
}

void	rcv_msg(t_env *e, int cs)
{
	int		ret = 0;
	// char	*line;
	(void)cs;

	ft_bzero(e->buf_read, BUF_SIZE);
	ret = recv(e->sockfd, &e->buf_read, BUF_SIZE, 0);
	/*while ((ret = recv(e->sockfd, &e->buf_read, BUF_SIZE, 0)) > -1)
	{
		printf("ret : %d\n", ret);
		
		e->buf_read[ret] = '\0';
		if (check_nl(e->buf_read, &line))
			break ;
		ft_bzero(e->buf_read, BUF_SIZE);
	}*/
	if (ret < 0)
	{
		close(e->sockfd);
		printf("Server connection lost\n");
	}
	else
	{
		// printf("%s\n", line);
		printf("%s\n", e->buf_read);
		ft_bzero(e->buf_read, BUF_SIZE);
	}
	// free(line);
	// line = NULL;
	
}

void	fd_env(t_env *e)
{
	e->maxfd = e->sockfd;
	e->type = FD_CLIENT;
	e->fct_read = input_line;
	e->fct_recv = rcv_msg;
	e->fct_write = send_msg;
	e->nickname = "user";
	e->chan = NULL;
}

void	rcc(t_env *e)
{
	int	r;

	r = recv(e->sockfd, e->buf_read, BUF_SIZE, 0);
	printf("len read : %d\n", r);
}

void	client_loop(int sockfd)
{
	t_env	e;

	e.sockfd = sockfd;
	fd_env(&e);
	while (1)
	{
		init_fd(&e);
		do_select(&e);
		check_fd(&e);
	}
}
