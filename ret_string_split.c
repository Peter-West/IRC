#include "irc_server.h"

char	*ft_strdupp(const char *src0)
{
	int		i;
	char	*tmp;
	(void)src0;

	char	*src;
	src = malloc(38);
	src = "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj\n";
	i = 0;
	tmp = NULL;

	printf("strdup src0 : %s**\n", src);
	printf("strdup len src ft : %zu\n", ft_strlen(src));
	// tmp = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1));
	printf("0. tmp ptr : %p, src : %p\n", tmp, src);
	tmp = malloc(50);
	printf("1. tmp ptr : %p, src : %p\n", tmp, src);
	printf("strdup len src ft : %zu\n", ft_strlen(src));
	printf("strdup src1 : %s**\n", src);
	// if (tmp == NULL || src == NULL)
		// return (NULL);
	while (src[i] != '\0')
	{
		tmp[i] = src[i];
		i++;
	}
	printf("strdup i : %d\n", i);
	tmp[i] = 0;
	printf("strdup tmp : %s**\n", tmp);
	return (tmp);
}


char		*ret_string_split(char *line, int s)
{
	char	**split;
	char	*str;
	int		i;

	i = 0;
	split = ft_strsplit(line, ' ');
	printf("ret_string_split : %s**\n", split[s]);
	str = ft_strdupp(split[s]);
	printf("ret_string_split str : %s**\n", str);
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