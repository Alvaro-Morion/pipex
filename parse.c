/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:17:06 by amorion-          #+#    #+#             */
/*   Updated: 2021/09/18 12:17:08 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_ntoken(char const *s, char c)
{
	int	i;
	int	run;
	int	n;

	i = 1;
	n = 0;
	while (s[i - 1])
	{
		if (s[i - 1] == '\'' || s[i - 1] == '\"')
		{
			run = 1;
			while (s[i - 1 + run] && s[i - 1 + run] != s[i - 1])
				run++;
			i = i + run;
		}
		if (s[i - 1] != c && (s[i] == '\0' || s[i] == c))
			n++;
		i++;
	}
	return (n);
}

static int	ft_tklen(char *s, char c)
{
	int	i;
	int	run;
	int	size;

	size = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i - 1] == '\'' || s[i - 1] == '\"')
		{
			size--;
			run = 1;
			while (s[i - 1 + run] && s[i - 1 + run] != s[i - 1])
				run++;
			size = i + run - 2;
			i = i + run;
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

int	ft_write_tab(char *tab, char *s, int len)
{
	int	wlen;

	wlen = 0;
	while (wlen < len)
	{
		tab[wlen] = s[wlen];
		wlen++;
	}
	tab[wlen] = 0;
	return (wlen);
}

static void	ft_splitk(char **tab, char *s2, char const *s, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s2[j] && i < ft_ntoken(s, c))
	{
		if (s2[j] != c)
		{
			len = ft_tklen(&s2[j], c);
			tab[i] = malloc(sizeof (char) * (len + 1));
			if (s2[j] == '\'' || s2[j] == '\"')
				j++;
			j = j + ft_write_tab(tab[i], &s2[j], len);
			i++;
			if (s2[j] == '\'' || s2[j] == '\"')
				j++;
		}
		else
			j++;
	}
	tab[i] = NULL;
}

char	**ft_split_cmd(char const *s, char c)
{
	char	**tab;
	char	*s2;

	s2 = (char *)s;
	tab = malloc(sizeof (char *) * (ft_ntoken(s, c) + 1));
	if (!tab)
		return (0);
	ft_splitk(tab, s2, s, c);
	return (tab);
}
