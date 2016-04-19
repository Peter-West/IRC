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
		printf(">> enter a 9 character nickname\n");
		return ;
	}
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
	e->chan = ft_strdup(split[1]);
	printf(">> You've joined : %s\n", e->chan);
	while (split[i])
		free(split[i++]);
}

void	leave_chan(t_env *e, char *line) //Probleme : wrong...
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
	if (split[1] == e->chan)
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
	(void)e;

	split = ft_strsplit(line, ' ');
	printf(">> Message send to %s\n", split[1]);
}

void	cmd_who()
{

}

void	cmd_connect()
{

}