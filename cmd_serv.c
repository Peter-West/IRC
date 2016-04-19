#include "irc_server.h"

void		change_nick_serv(t_env *e, int cs, char *line)
{
	char	*nick;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ret_string_split(line, 1);
	printf("nick tmp : %s**\n", tmp);
	if (ft_strlen(tmp) > 9)
		nick = ft_strsub(tmp, 0, 9);
	else
		nick = ft_strdup(tmp);
	e->fds[cs].nickname = nick;
}

void		cmd_who(t_env *e, int cs) // nl dans nickname
{
	int		i;

	i = 0;
	printf("channel : %s\n", e->fds[cs].channel);
	while (i < e->maxfd)
	{
		if (e->fds[cs].channel && e->fds[i].channel == e->fds[cs].channel)
		{
			printf("%s is on %s\n", e->fds[i].nickname,e->fds[cs].channel);
		}
		i++;
	}
}

void		join_chan(t_env *e, int cs, char *line)
{
	char	*channel_name;

	channel_name = ret_string_split(line, 1);
	if (e->fds[cs].channel)
	{
		printf("%s already in channel : %s\n", e->fds[cs].nickname,
		 e->fds[cs].channel);
	}
	else
		e->fds[cs].channel = channel_name;
}

void		leave_chan(t_env *e, int cs, char *line)
{
	char	*channel_name;

	channel_name = ret_string_split(line, 1);
	if (e->fds[cs].channel == channel_name)
	{
		e->fds[cs].channel = NULL;
	}
	else
	{
		printf("%s in channel : %s\n", e->fds[cs].nickname,
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
	while (i < e->maxfd)
	{
		if (e->fds[i].nickname == to)
		{
			printf("to : %s, msg : %s\n", to, msg);
			return ;
		}
		i++;
	}
	printf("User unknown\n");
}

void		cmd_connect(t_env *e, int cs)
{
	e->fds[cs].type = FD_FREE;
	e->fds[cs].nickname = "user";
	clean_fd(&e->fds[cs]);
}

void		cmd(t_env *e, int cs, char *line)
{
	if (!ft_strncmp("/nick ", line, 6))
		change_nick_serv(e, cs, line);
	else if (!ft_strncmp("/who\n", line, 5))
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

