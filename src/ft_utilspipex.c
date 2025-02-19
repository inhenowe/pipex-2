/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilspipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:50 by aleortiz          #+#    #+#             */
/*   Updated: 2025/02/19 14:00:49 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_path(char **envp, char *command)
{
	int	ctu;

	ctu = 0;
	if (!envp)
		perror("comand not found");
	while (envp[ctu] != NULL)
	{
		if (ft_strncmp(envp[ctu], "PATH=", 5) == 0)
			break;
		ctu++;
	}
	if (envp[ctu] == 0)
	{
		perror("path not found");
		exit(1);
	}
	return (create_path(envp[ctu] + 5, command));
}

char	*create_path(char *key_word, char *command)
{
	char	*path;
	char	**pos_key;
	int		ctu;
	char	*temp;

	ctu = -1;
	path = NULL;
	temp = NULL;
	pos_key = ft_split(key_word, ':');
	while (pos_key[++ctu] != 0)
	{
		temp = ft_strjoin(pos_key[ctu], "/");
		path = ft_strjoin(temp, command);
		if (access(path,F_OK) == 0)
			break;
		else
			free(path);
	}
	while(pos_key[ctu++] != NULL)
		free(pos_key[ctu]);
	free(pos_key);
	return (path);
}

void	offspring_read(char **data, char **envp, char *path, int fd1[2])
{
	char	**args;
	int		fd2;

	fd2 = 0;
	close(fd1[READ_SIDE]);
	if (access(data[1], F_OK) == -1)
		ft_printf("archivo %s inexistente", data[1]);
	else
		fd2 = open(data[1], O_RDONLY);
	dup2(fd2,STDIN_FILENO);
	close(fd2);
	dup2(fd1[WRITE_SIDE], STDOUT_FILENO);
	close(fd1[WRITE_SIDE]);
	args = ft_split_pipex(data[2]);
	execve(path, args, envp);
	perror("exceve1");
	exit(1);

}

void	offspring_write(char **data, char **envp, char *path, int fd1[2])
{
	char	**args;
	int		fd2;

	fd2 = 0;
	if (access(data[4], F_OK) == -1)
		fd2 = open(data[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd2 = open(data[4], O_WRONLY | O_TRUNC);
	dup2(fd1[READ_SIDE], STDIN_FILENO);
	close(fd1[READ_SIDE]);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);
	args = ft_split_pipex(data[3]);
	execve(path, args, envp);
	perror("execve2");
	exit(1);
}
