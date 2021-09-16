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

size_t	ft_nparam(char *cmd)
{
	int		sc;
	int		dc;
	size_t	i;
	size_t	n;

	sc = -1;
	dc = -1;
	n = 0;
	i = 1;
	while (cmd[i])
	{
		if (cmd[i - 1] == '\'')
			sc = -sc;
		if (cmd[i - 1] == '\"')
			dc = -dc;
		if (cmd[i - 1] && cmd[i] == ' ' && sc < 0 && dc < 0)
			n++;
		i++;
	}
	if (!cmd[i] && cmd[i - 1] != ' ')
		n++;
	return (n);
}

size_t	ft_paramlen(char *cmd)
{
	size_t	i;
	int		sc;
	int		dc;

	dc = -1;
	sc = -1;
	i = 0;
	while (cmd[i] && (cmd[i] != ' ' || (cmd[i] == ' ' && (sc > 0 || dc > 0))))
	{
		if (cmd[i] == '\'')
			sc = -sc;
		if (cmd[i] == '\"')
			dc = -dc;
		i++;
	}
	return (i);
}

void	ft_split_param(char ***tab,char *cmd)
{
	size_t	i;
	size_t	j;
	size_t	wdnum;
	size_t	len;

	j = 0;
	wdnum = 0;
	while (cmd[j] && cmd[j] != ' ')
	{
		len = ft_paramlen(&cmd[j]);
		
		*tab[wdnum] = malloc(sizeof(char *) * (len + 1));
		i = 0;
		while (i < len)
		{
			*tab[wdnum][i] = cmd[j + i];
			i++;
			printf("%zu %zu %c\n", len, i, cmd[0]);
		}
		*tab[wdnum][i] = 0;
		wdnum++;
		j = j + i +1;
	}
	*tab[wdnum] = 0;
}

char	**ft_parse_comand(char *cmd)
{
	char	**tab;

	tab = malloc(ft_nparam(cmd) + 1);
	if (!tab)
		return (NULL);
	ft_split_param(&tab, cmd);
	return (tab);
}

int main(int argc, char **argv)
{
	char  **cmd;
	int i;

	(void)argc;
	i = 0;
	cmd = ft_parse_comand(argv[1]);
	/*while(cmd[i])
	{
		printf("%s\n", cmd[i]);
		i++;
	}*/
}
