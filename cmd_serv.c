#include "irc_server.h"

void		change_nick_serv(t_env *e, int cs, char *line)
{
	char	*nick;
	char	**split;
	int		i;

	i = 0;
	split = ft_strsplit(line, ' ');
	if (ft_strlen(split[1]) > 9)
		nick = ft_strsub(split[1], 0, 9);
	else
		nick = ft_strdup(split[1]);
	e->fds[cs].user.nickname = nick;
	// ft_bzero(line, BUFF_SIZE);
	while (split[i])
		free(split[i++]);
}

void		cmd_who(t_env *e, int cs)
{
	int		i;
	t_chan	*tmp;

	i = 0;
	tmp = e->chan;
	printf("channel : %s\n", e->fds[cs].user.chan);
	while (i < e->maxfd)
	{
		if (e->fds[i].user.chan == e->fds[cs].user.chan)
			printf("user : %s\n", e->fds[i].user.chan);
		i++;
	}
}


void		cmd(t_env *e, int cs, char *line)
{
	if (!ft_strncmp("/nick ", line, 6))
		change_nick_serv(e, cs, line);
	else if (!ft_strncmp("/who\0", line, 5))
		cmd_who(e, cs);
/*	else if (!ft_strncmp("/join ", line, 6))
	else if (!ft_strncmp("/leave ", line, 6))
	else if (!ft_strncmp("/msg ", line, 4))
	else if (!ft_strncmp("/connect ", line, 9))*/
}

