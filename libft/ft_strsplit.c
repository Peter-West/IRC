/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 18:34:39 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/26 18:34:42 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int    	count_word(const char *str, char c)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i - 1] == c && str[i] != c)
		{
			nb++;
		}
		i++;
	}
	if (str[0] != c && str[0] != '\0')
		nb++;
	return (nb);
}

static size_t	c_stop(const char *s, int start, char c)
{
	size_t	x;

	x = 0;
	while (s[start] && s[start] != c)
	{
		start++;
		x++;
	}
	return (x);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = count_word(s, c);
	tab = (char **)malloc(sizeof(tab) * word + 1);
	if (!tab)
		return (NULL);
	while (i < word)
	{
		while (s[j] && s[j] == c)
			j++;
		tab[i] = ft_strsub(s, j, c_stop(s, j, c));
		i++;
		while (s[j] && s[j] != c)
			j++;
	}
	tab[i] = 0;
	return (tab);
}
