#include "client.h"

void	send_msg(int sockfd)
{
	int		ret;
	int		read_ret = 0;
	char	buf[BUFF_SIZE + 1];

	ret = 0;
	ft_bzero(buf, BUFF_SIZE);
	if ((read_ret = read(0, &buf, BUFF_SIZE)))
	{
		ret = send(sockfd, &buf, read_ret, 0);
	/*	if (ret > 0)
			printf("ret = %d\n", ret);*/
		printf("%s\n", buf);
		ft_bzero(buf, BUFF_SIZE);
	}
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
		printf("Connection to server lost\n");
	}
	else
	{
		printf("%s\n", buf);
		ft_bzero(buf, BUFF_SIZE);
	}
}

void	client_loop(int sockfd)
{

	printf("sockfd : %d\n", sockfd);
	while (1)
	{
		send_msg(sockfd);
		rcv_msg(sockfd);
	}
}
