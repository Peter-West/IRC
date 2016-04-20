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
	char	*line;
	(void)cs;

	read_ret = 0;
	line = NULL;
	ft_bzero(e->buf_read, BUF_SIZE);
	while ((read_ret = read(0, &e->buf_read, BUF_SIZE)))
	{
		if (check_nl(e->buf_read, &line))
			break ;
		ft_bzero(e->buf_read, BUF_SIZE);
	}
	if (line[0] == '/')
		cmd(e, line);
	send(e->sockfd, line, ft_strlen(line), 0);
	free(line);
	line = NULL;
}

void	rcv_msg(t_env *e, int cs)
{
	int		ret = 0;
	(void)cs;

	ft_bzero(e->buf_write, BUF_SIZE);
	ret = recv(e->sockfd, &e->buf_write, BUF_SIZE, 0);
	if (ret < 0)
	{
		close(e->sockfd);
		printf("Server connection lost\n");
	}
	else
	{
		printf("%s\n", e->buf_write);
		ft_bzero(e->buf_write, BUF_SIZE);
	}
}

void	fd_env(t_env *e)
{
/*	struct rlimit	rlp;
	// int				i;

	getrlimit(RLIMIT_NOFILE, &rlp);
	e->maxfd = rlp.rlim_cur;*/
	e->maxfd = 4;
	e->type = FD_CLIENT;
	e->fct_read = client_accept;
	e->fct_write = NULL;	
/*	e->fds = (t_fd*)malloc(sizeof(t_fd) * e->maxfd);
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}*/
}

void	client_loop(int sockfd)
{
	t_env	e;

	// e.nickname = "user";
	// e.chan = NULL;
	e.sockfd = sockfd;
	// e.fct_read = client_accept;
	fd_env(&e);
	printf("sockfd : %d\n", sockfd);
	while (1)
	{
		init_fd(&e);
		do_select(&e);
		check_fd(&e);
		// input_line(&e);
		// rcv_msg(sockfd);
	}
}
