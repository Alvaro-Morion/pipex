/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:12:17 by amorion-          #+#    #+#             */
/*   Updated: 2021/09/12 15:12:19 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Devuelve el path del comando especificado
char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*paths;
	char	**path;

	i = 0;
	paths = NULL;
	while (!paths)
	{
		paths = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	paths = paths + ft_strlen("PATH=");
	path = ft_split(paths, ':');
	i = 0;
	paths = ft_get_path(path, cmd);
	if (!paths)
	{
		ft_putstr_fd("Comand not found: ", 0);
		ft_putstr_fd(cmd, 0);
		exit(-1);
	}
	return (paths);
}

void	ft_exec(char *cmd, char **envp)
{
	char	*path;
	char	**comand;

	comand = ft_parse_comand(cmd);
	path = find_path(comand[0], envp);
	if (execve(path, comand, envp) == -1)
	{
		perror("Comand: ");
	}
}

void	ft_child_process(char **argv, char **envp, int *pip)
{
	int	fin;

	fin = open(argv[1], O_RDONLY);
	if (fin < 0)
	{
		perror("File 1: ");
		exit(-1);
	}
	dup2(pip[1], STDOUT_FILENO);
	dup2(fin, STDIN_FILENO);
	close(pip[0]);
	ft_exec(argv[2], envp);
	close(fin);
}

void	ft_parent_process(char **argv, char **envp, int *pip)
{
	int	fout;

	close(pip[1]);
	fout = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG
			| S_IRWXO);
	if (fout < 0)
	{
		perror("File 2: ");
		return ;
	}
	dup2(pip[0], STDIN_FILENO);
	dup2(fout, STDOUT_FILENO);
	close(pip[1]);
	ft_exec(argv[3], envp);
	close(fout);
}

int	main(int argc, char **argv, char **envp)
{
	int		pip[2];
	int		status;
	pid_t	pid;

	if (argc != 5)
		return (write(1, "Invalid number of arguments\n", 28));
	if (pipe(pip) == -1)
	{
		perror("Pipe: ");
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		perror("Fork: ");
	else if (pid == 0)
		ft_child_process(argv, envp, pip);
	else
	{
		wait(&status);
		ft_parent_process(argv, envp, pip);
	}
	close(pip[0]);
	close(pip[1]);
}
