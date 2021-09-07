/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 17:25:50 by amorion-          #+#    #+#             */
/*   Updated: 2021/09/05 18:57:52 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execve(char *cmd, char **paths, char **envp)
{
		
}
void	ft_command1(char **argv, char **paths, int *tub, char **envp)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Input file error: ");
		exit(-1);
	}
	dup2(fd, STDIN_FILENO);
	dup2(tub[1], STDOUT_FILENO);
	close(tub[0]);
	close(fd);
	ft_execve(argv[2], paths, envp);
}

void	ft_command2(char **argv, char **paths, int *tub, char **envp)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_TRUNC);
	if (fd < 0)
	{
		perror("Output file error: ");
		exit(-1);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(tub[0], STDIN_FILENO);
	close(tub[0]);
	close(fd);
	ft_execve(argv[3], paths, envp);
}

void	ft_pipex(char **argv, char **paths, char **envp)
{
	int		tub[2];
	int		status;
	pid_t	pid;

	if (pipe(tub) == -1)
	{
		perror("Pipe error: ");
		exit(-1);
	}
	if (pid < 0)
	{
		perror("Fork error: ");
		exit(-1);
	}
	else if (!pid)
		ft_comand1(argv, paths, tub, envp);
	else
	{
		wait(&status);
		if (status < 0)
			exit(-1);
		ft_comand2(argv, paths, tub, envp);
	}
	ft_free_split(paths);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (write(1, "Invalid number of arguments\n", 28));
	ft_pipex(argv, ft_get_path(envp), envp);
}
