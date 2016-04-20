#include "client.h"

void	change_nick(t_env *e, char *line)
{
	char	**split;
	char	*nick;
	int		i;

	i = 0;
	split = ft_strsplit(line, ' ');
	if (!split[1])
	{
		printf(">> enter a 9 characters nickname\n");
		return ;
	}
	split[1] = ft_strtrim(split[1]);
	if (ft_strlen(split[1]) > 9)
		nick = ft_strsub(split[1], 0, 9);
	else
		nick = ft_strdup(split[1]);
	e->nickname = nick;
	printf(">> your nickname has been changed to : %s\n", e->nickname);
	while (split[i])
		free(split[i++]);
}

void	join_chan(t_env *e, char *line)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_strsplit(line, ' ');
	if (!split[1])
	{
		printf(">> enter a channel name\n");
		return ;
	}
	if (!e->chan)
	{
		split[1] = ft_strtrim(split[1]);
		e->chan = ft_strdup(split[1]);
		printf(">> You've joined : %s\n", e->chan);
	}
	else
	{
		printf(">> You must leave %s before joining a new channel\n", e->chan);
	}
	while (split[i])
		free(split[i++]);
}

void	leave_chan(t_env *e, char *line)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_strsplit(line, ' ');
	if (!split[1])
	{
		printf(">> enter a channel name\n");
		return ;
	}
	split[1] = ft_strtrim(split[1]);
	if (!ft_strcmp(split[1],e->chan))
	{
		printf(">> You left %s\n", e->chan);
		if (e->chan)
			free(e->chan);
		e->chan = NULL;
	}
	else
		printf(">> Wrong channel name\n");
	while (split[i])
		free(split[i++]);
}

void	msg_user(t_env *e, char *line)
{
	char	**split;
	int		i;
	(void)e;

	i = 0;
	split = ft_strsplit(line, ' ');
	printf(">> Message send to %s\n", split[1]);
	while (split[i])
		free(split[i++]);
}


void	cmd_connect(t_env *e, char *line)
{
	char	**split;
	int		i;


	i = 0;
	send(e->sockfd, "/connect ", 10, 0);
	split = ft_strsplit(line, ' ');
	while (split[i])
		i++;
	split[2] = ft_strtrim(split[2]);
	connect_serv(i, split);
}

void	cmd_who()
{

}