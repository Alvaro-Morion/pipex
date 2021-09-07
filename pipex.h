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

char	**ft_get_path(char **env);
char	**ft_split(char const *s, char c);
void	ft_free_split(char **split);
#endif