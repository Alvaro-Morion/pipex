/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:43:41 by amorion-          #+#    #+#             */
/*   Updated: 2021/09/12 17:43:46 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
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
	return (path);
}

void	ft_exec(char *cmd, char **envp)
{
	char	**path;
	char	**comand;
	char	*p;
	int		i;

	i = 0;
	comand = ft_split(cmd, ' ');
	path = find_path(envp);
	while (path[i])
	{
		p = ft_strjoin(ft_strjoin(path[i], "/"), comand[0]);
		execve(p, comand, envp);
		i++;
	}
	perror(comand[0]);
	free(p);
	ft_free_split(comand);
	exit(EXIT_FAILURE);
}

void	ft_child_process(char **argv, char **envp, int *pip)
{
	int	fin;

	fin = open(argv[1], O_RDONLY);
	if (fin < 0)
	{
		perror("File 1: ");
		exit(EXIT_FAILURE);
	}
	close(pip[0]);
	dup2(fin, STDIN_FILENO);
	close(fin);
	dup2(pip[1], STDOUT_FILENO);
	ft_exec(argv[2], envp);
}

void	ft_parent_process(char **argv, char **envp, int *pip)
{
	int	fout;

	fout = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG
			| S_IRWXO);
	if (fout < 0)
	{
		perror("File 2: ");
		exit(EXIT_FAILURE);
	}
	close(pip[1]);
	dup2(fout, STDOUT_FILENO);
	close(fout);
	dup2(pip[0], STDIN_FILENO);
	ft_exec(argv[3], envp);
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
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (status == EXIT_FAILURE)
			return (-1);
		ft_parent_process(argv, envp, pip);
	}
	return (0);
}
