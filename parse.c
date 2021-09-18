/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:56:06 by amorion-          #+#    #+#             */
/*   Updated: 2021/09/12 15:56:07 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_ntok(char *s, char c)
{
	int	i;
	int	n;
	int sc;
	int dc;

	i = 1;
	n = 0;
	sc = -1;
	dc = -1;
	while (s[i - 1])
	{
		if (s[i - 1] == '\'')
			sc = -sc;
		if (s[i - 1] == '\"')
			dc = -dc;
		if (s[i - 1] != c && (s[i] == '\0' || (s[i] == c && sc + dc == -2)))
			n++;
		i++;
	}
	return (n);
}

int	ft_toklen(char *s, char c)
{
	int	i;
	int sc;
	int dc;

	sc = -1;
	dc = -1;
	i = 0;
	while (s[i] && (s[i] != c || (s[i] == c && sc + dc != -2)))
	{
		if (s[i] == '\'')
			sc = -sc;
		if (s[i] == '\"')
			dc = -dc;
		i++;
	}
	return (i);
}

void	ft_split_tok(char **tab, char *s, char c)
{
	int	i;
	int	j;
	int	wlen;
	int sc;
	int dc;

	sc = -1;
	dc = -1;
	i = 0;
	j = 0;
	while (s[j] && i < ft_ntok(s, c))
	{
		if(s[j] == '\'')
			sc = -sc;
		if(s[j] == '\"')
			dc = -dc;
		if (s[j] != c)
		{
			tab[i] = malloc(sizeof (char) * (ft_toklen(&s[j], c) + 2));
			wlen = 0;
			while (s[j] && (s[j] != c || (s[j] == c && sc + dc != -2)))
			{
				tab[i][wlen] = s[j];
				wlen++;
				j++;
				if(s[j] == '\'')
					sc = -sc;
				if(s[j] == '\"')
					dc = -dc;
			}
			tab[i][wlen] = '\0';
			i++;
		}
		else
			j++;
	}
	tab[i] = NULL;
}

char	**ft_split_comand(char *cmd)
{
	char **tab;

	tab = malloc(ft_ntok(cmd, ' ') + 2);
	if(!tab)
		return(NULL);
	ft_split_tok(tab, cmd, ' ');
	return(tab);
}

/*int main(int argc, char **argv, char **envp)
{
	(void)argc;
	ft_exec(argv[1], envp);
}*/