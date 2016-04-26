/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_serv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:14:39 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:14:45 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void		leave_chan(t_env *e, int cs, char *line)
{
	char	*channel_name;

	channel_name = ret_string_split(line, 1);
	channel_name = ft_strtrim(channel_name);
	if (!ft_strcmp(e->fds[cs].channel, channel_name))
		e->fds[cs].channel = NULL;
	else
	{
		printf(">> %s in channel : %s\n", e->fds[cs].nickname,
			e->fds[cs].channel);
	}
}

void		msg_user(t_env *e, int cs, char *line)
{
	char	*to;
	char	*msg;
	int		i;

	i = 0;
	to = ret_string_split(line, 1);
	msg = ret_string_split(line, 2);
	msg = ft_strtrim(msg);
	while (i < e->maxfd)
	{
		if (e->fds[i].nickname && !ft_strcmp(e->fds[i].nickname, to))
		{
			ft_strcat(e->fds[cs].buf_write, "#");
			ft_strcat(e->fds[cs].buf_write, ft_itoa(i));
			ft_strcat(e->fds[cs].buf_write, " ");
			ft_strcat(e->fds[cs].buf_write, msg);
			printf(">> to : %s, msg : %s\n", to, msg);
			return ;
		}
		i++;
	}
	printf(">> Message wasn't sent : User unknown\n");
}

void		cmd_connect(t_env *e, int cs)
{
	printf("connect **\n");
	close(cs);
	clean_fd(&e->fds[cs]);
	printf("client #%d gone away\n", cs);
	e->fds[cs].type = FD_FREE;
	e->fds[cs].nickname = NULL;
	e->fds[cs].channel = NULL;
	ft_bzero(e->fds[cs].buf_write, BUF_SIZE);
	ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
	clean_fd(&e->fds[cs]);
}

void		cmd(t_env *e, int cs, char *line)
{
	if (!ft_strncmp("/nick ", line, 6))
		change_nick_serv(e, cs, line);
	else if (!ft_strncmp("/who\0", line, 5))
		cmd_who(e, cs);
	else if (!ft_strncmp("/join ", line, 6))
		join_chan(e, cs, line);
	else if (!ft_strncmp("/leave ", line, 6))
		leave_chan(e, cs, line);
	else if (!ft_strncmp("/msg ", line, 4))
		msg_user(e, cs, line);
	else if (!ft_strncmp("/connect ", line, 9))
		cmd_connect(e, cs);
}
