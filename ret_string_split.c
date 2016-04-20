#include "irc_server.h"

char		*ret_string_split(char *line, int s)
{
	char	**split;
	char	*str;
	int		i;

	i = 0;
	split = ft_strsplit(line, ' ');
	str = ft_strdup(split[s]);
	if (split)
	{
		while(split[i])
		{
			if (split[i])
				free(split[i]);
			i++;
		}
	}
	return(str);
}