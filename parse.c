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
	int run;
	int	n;

	i = 1;
	n = 0;
	while (s[i - 1])
	{
		if (s[i - 1] == '\'' || s[i - 1] == '\"')
		{
			run = 1;
			while(s[i - 1 + run] && s[i - 1 + run] != s[i -1])
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
	int run;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i - 1] == '\'' || s[i - 1] == '\"')
		{
			run = 1;
			while(s[i - 1 + run] && s[i - 1 + run] != s[i -1])
				run++;
			i = i + run;
		}
		else
			i++;
	}
	return (i);
}

static void	ft_splitk(char **tab, char *s2, char const *s, char c)
{
	int	i;
	int	j;
	int	wlen;
	int len;

	i = 0;
	j = 0;
	while (s2[j] && i < ft_ntoken(s, c))
	{
		if (s2[j] != c)
		{
			len = ft_tklen(&s2[j], c);
			tab[i] = malloc(sizeof (char) * (len + 1));
			wlen = 0;
			while (wlen < len)
			{
				tab[i][wlen] = s2[j];
				wlen++;
				j++;
			}
			tab[i][wlen] = '\0';
			i++;
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
/*int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *cmd[2];
	cmd[0] = "grep";
	cmd[1] = "\'a b\'";
	execve("/usr/bin/grep", cmd, envp);
	perror("error:" );
}*/