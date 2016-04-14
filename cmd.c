#include "client.h"

void	change_nick(t_env *e, char *line)
{
	char	**split;
	char	*nick;
	int		i;

	i = 0;
	split = ft_strsplit(line, ' ');
	if (ft_strlen(split[1]) > 9)
		nick = ft_strsub(split[1], 0, 9);
	else
		nick = ft_strdup(split[1]);
	e->nickname = nick;
	printf("your nickname has been changed to : %s\n", e->nickname);
	ft_bzero(line, BUFF_SIZE);
	while (split[i])
		free(split[i++]);
}

void	join_chan(t_env *e, char *line)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_strsplit(line, ' ');
	e->chan = ft_strdup(split[1]);
	printf("You've joined : %s\n", e->chan);
	ft_bzero(line, BUFF_SIZE);
	while (split[i])
		free(split[i++]);
}

void	leave_chan(t_env *e)
{
	e->chan = NULL;
}
/*
void	msg_user(t_env *e, char *line)
{

}*/