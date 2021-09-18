/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 09:51:00 by amorion-          #+#    #+#             */
/*   Updated: 2021/09/06 09:51:01 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include<fcntl.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<sys/wait.h>

char	*ft_get_path(char **path, char *cmd);
char	**ft_split(char const *s, char c);
char	**ft_split_comand(char *cmd);
void	ft_free_split(char **split);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_get_comand(char *cmd);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcat(char *dest, char const *src, size_t size);
size_t	ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);
#endif