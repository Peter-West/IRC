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

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[cs].channel && e->fds[i].channel && !ft_strcmp(e->fds[i].channel, e->fds[cs].channel))
		{
			printf(">>%d. %s is on %s\n", i, e->fds[i].nickname,e->fds[i].channel);
		}
		printf(">>%d. %s is on %s\n", i, e->fds[i].nickname,e->fds[i].channel);
		i++;
	}
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

void		leave_chan(t_env *e, int cs, char *line)
{
	char	*channel_name;

	channel_name = ret_string_split(line, 1);
	channel_name = ft_strtrim(channel_name);
	if (!ft_strcmp(e->fds[cs].channel, channel_name))
	{
		e->fds[cs].channel = NULL;
	}
	else
	{
		printf(">> %s in channel : %s\n", e->fds[cs].nickname,
		 		e->fds[cs].channel);
	}
}

void		msg_user(t_env *e, char *line)
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
		if (!ft_strcmp(e->fds[i].nickname, to))
		{
			printf(">> to : %s, msg : %s\n", to, msg);
			return ;
		}
		i++;
	}
	printf(">> User unknown\n");
}

void		cmd_connect(t_env *e, int cs)
{
	printf("connect\n");
	close(cs);
	clean_fd(&e->fds[cs]);
	printf("client #%d gone away\n", cs);
	e->fds[cs].type = FD_FREE;
	e->fds[cs].nickname = NULL;
	e->fds[cs].channel = NULL;
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
		msg_user(e, line);
	else if (!ft_strncmp("/connect ", line, 9))
		cmd_connect(e, cs);
}

