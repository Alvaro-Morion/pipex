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

char	**ft_get_path(char **env)
{
	char	**split;
	char	**paths;
	int		i;

	while (*env)
	{
		split = ft_split(*env, '=');
		if (ft_strnstr(split[0], "PATH", ft_strlen("PATH")))
			break ;
		ft_free_split(split);
		env++;
	}
	paths = ft_split(split[1], ':');
	ft_free_split(split);
	i = 0;
	while (paths[i])
	{
		ft_strlcat(paths[i], "/", ft_strlen(paths[i]) + 2);
		i++;
	}
	return (paths);
}
