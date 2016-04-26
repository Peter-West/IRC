/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_serv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:14:51 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:14:55 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void		change_nick_serv(t_env *e, int cs, char *line)
{
	char	*nick;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ret_string_split(line, 1);
	tmp = ft_strtrim(tmp);
	printf(">> client #%d change nickname to :%s\n", cs, tmp);
	if (ft_strlen(tmp) > 9)
		nick = ft_strsub(tmp, 0, 9);
	else
		nick = ft_strdup(tmp);
	e->fds[cs].nickname = nick;
}

void		cmd_who(t_env *e, int cs)
{
	int		i;
	int		len;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[cs].channel && e->fds[i].channel
			&& !ft_strcmp(e->fds[i].channel, e->fds[cs].channel))
		{
			ft_strcat(e->fds[cs].buf_write, e->fds[i].nickname);
			ft_strcat(e->fds[cs].buf_write, " is on ");
			ft_strcat(e->fds[cs].buf_write, e->fds[i].channel);
			ft_strcat(e->fds[cs].buf_write, "\n");
			printf(">>%d. %s is on %s\n", i, e->fds[i].nickname,
				e->fds[i].channel);
		}
		i++;
	}
	len = ft_strlen(e->fds[cs].buf_write);
	e->fds[cs].buf_write[len - 1] = '\0';
}

void		join_chan(t_env *e, int cs, char *line)
{
	char	*channel_name;

	channel_name = ret_string_split(line, 1);
	channel_name = ft_strtrim(channel_name);
	if (e->fds[cs].channel)
	{
		printf(">> %s already in channel : %s\n", e->fds[cs].nickname,
			e->fds[cs].channel);
	}
	else
	{
		e->fds[cs].channel = channel_name;
		printf(">>cs : %d, chan : %s\n", cs, e->fds[cs].channel);
	}
}
