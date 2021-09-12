/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 09:41:21 by amorion-          #+#    #+#             */
/*   Updated: 2021/09/06 09:41:22 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			while (i + j < len && big[i + j] && big[i + j] == little[j]
				&& little[j])
				j++;
			if (!little[j])
				return ((char *)big + i);
			j = 0;
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	r;

	i = 0;
	j = 0;
	r = 0;
	while (dest[i])
		i++;
	while (src[r])
		r++;
	if (size <= i)
		r += size;
	else
		r += i;
	while (src[j] && i + 1 < size)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (r);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

// Devuelve el path del comando especificado
char	*find_path(char *cmd, char **envp)
{
	int i;
	char *paths;
	char **path;

	i = 0;
	paths = NULL;
	while(!paths)
	{
		paths = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	paths = paths + ft_strlen("PATH=");
	path = ft_split(paths, ':');
	i = 0;
	while(path[i])
	{
		ft_strlcat(path[i], "/", ft_strlen(path[i]) + 2);
		paths=ft_strjoin(path[i], cmd);
		if (access(paths, F_OK) == 0)
		{
			ft_free_split(path);
			return(paths);
		}
		free(paths);
		i++;
	}
	ft_putstr_fd("Comand not found: ", 0);
	ft_putstr_fd(cmd, 0);
	exit(-1);
}