/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:11:41 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:11:50 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_error(int i, char *s)
{
	printf("ERROR : %s\n", s);
	exit(i);
}

void	check_args(int argc, char **argv)
{
	int		i;

	i = 0;
	if (argc != 3)
		ft_error(-1, "Usage: ./client [adresse machine] [port]");
	while (argv[2][i] != 0)
	{
		if (!ft_isdigit(argv[2][i]))
			ft_error(-1, "Usage: ./client [adresse machine] [port]");
		i++;
	}
}

int		init(char **argv)
{
	int						sock_fd;
	struct sockaddr_in		addr;
	struct hostent			*server_ad;

	ft_bzero(&addr, sizeof(addr));
	printf("machine %s\nport %s\n", argv[1], argv[2]);
	if ((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		ft_error(1, "Can't open socket");
	printf("sock fd : %d\n", sock_fd);
	if (!(server_ad = gethostbyname(argv[1])))
		ft_error(1, "No such a host");
	addr.sin_family = AF_INET;
	ft_memcpy((void*)&addr.sin_addr.s_addr, (void*)server_ad->h_addr,
		server_ad->h_length);
	addr.sin_port = htons(ft_atoi(argv[2]));
	if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		ft_error(1, "Can't connect");
	return (sock_fd);
}

void	connect_serv(int argc, char **argv)
{
	int		sock_fd;

	check_args(argc, argv);
	sock_fd = init(argv);
	client_loop(sock_fd);
}

int		main(int argc, char **argv)
{
	connect_serv(argc, argv);
	return (0);
}
