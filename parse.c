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

static void	ft_flag(int **flag, char c)
{
	if(c == '\'')
		*flag[0] = -*flag[0];
	if(c == '\"')
		*flag[1] = -*flag[1];
}
static size_t	ft_tokens(char *cmd)
{
	int		*flag;
	size_t	i;
	size_t	n;

	flag = malloc(2);
	if (!flag)
		return (0);
	flag[0]=-1;
	flag[1]=-1;
	i = 1;
	n = 0;
	while(cmd[i - 1])
	{
		ft_flag(&flag, cmd[i - 1]);
		if (cmd[i - 1] != ' ' && (!cmd[i] || (cmd[i] == ' ' && flag[0] + flag[1] == -2)))
			n++;
		i++;
	}
	free(flag);
	return(n);
}

static size_t	ft_toklen(char *s, char c)
{
	size_t	i;
	int		*flag;

	flag = malloc(2);
	flag[0] = -1;
	flag[1] = -1;
	i = 0;
	while (s[i] && (s[i] != c || flag[0] + flag[1] != -2))
		i++;
	free(flag);
	return (i);
}

static void	ft_sptok(char **tab,char *s)
{
	size_t	i;
	size_t	j;
	int		*flag;
	size_t	wlen;

	flag = malloc(2);
	flag[0] = -1;
	flag[1] = -1;
	i = 0;
	j = 0;
	while (s[j] && i < ft_tokens(s))
	{
		if (s[j] != ' '|| flag[0] + flag[1] != -2)
		{
			ft_flag(&flag, s[j]);
			tab[i] = malloc(sizeof (char) * (ft_toklen(&s[j], ' ') + 2));
			wlen = 0;
			while (s[j] && (s[j] != ' ' || flag[0] + flag[1] != -2))
			{
				tab[i][wlen] = s[j];
				wlen++;
				j++;
				ft_flag(&flag, s[j]);
			}
			tab[i][wlen] = '\0';
			i++;
		}
		else
			j++;
	}
	tab[i] = NULL;
	free(flag);
}

char	**parse(char *cmd)
{
	char	**tab;

	tab = malloc(ft_tokens(cmd) + 1);
	if (!tab)
		return (0);
	ft_sptok(tab, cmd);
	return(tab);
}