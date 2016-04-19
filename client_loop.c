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
		cmd_connect();
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

void	input_line(t_env *e, int sockfd)
{
	int		read_ret;
	char	*line;

	read_ret = 0;
	line = NULL;
	ft_bzero(e->buf, BUFF_SIZE);
	while ((read_ret = read(0, &e->buf, BUFF_SIZE)))
	{
		if (check_nl(e->buf, &line))
			break ;
		ft_bzero(e->buf, BUFF_SIZE);
	}
	if (line[0] == '/')
		cmd(e, line);
	send(sockfd, line, ft_strlen(line), 0);
	free(line);
	line = NULL;
}

void	rcv_msg(int sockfd)
{
	char	buf[BUFF_SIZE + 1];
	int		ret = 0;

	ft_bzero(buf, BUFF_SIZE);
	ret = recv(sockfd, &buf, BUFF_SIZE, 0);
	if (ret <= 0)
	{
		close(sockfd);
		printf("Server connection lost\n");
	}
	else
	{
		printf("%s\n", buf);
		ft_bzero(buf, BUFF_SIZE);
	}
}

void	client_loop(int sockfd)
{
	t_env	e;

	e.nickname = "user";
	printf("sockfd : %d\n", sockfd);
	while (1)
	{
		input_line(&e, sockfd);
		// rcv_msg(sockfd);
	}
}
