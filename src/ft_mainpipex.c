 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mainpipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:44:53 by aleortiz          #+#    #+#             */
/*   Updated: 2025/02/14 15:00:15 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	pip_menu(char **argv,char **envp)
// {
// 	int 	fd1[2];
// 	int 	procesor_id;
// 	char	*sourcepath;
// 	char	**candf;
// 	int		i;

// 	candf = ft_split(argv[2], ' ');
// 	sourcepath = search_path(envp, candf[0]);
// 	i = 0;
// 	while (candf[i])
// 		free(candf[i++]);
// 	free(candf);
// 	if (pipe(fd1) == -1)
// 		perror("pipe");
// 	procesor_id = fork();
// 	if (procesor_id == 0)
// 		offspring_read(argv, envp, sourcepath, fd1);
// 	else
// 	{
// 		close(fd1[WRITE_SIDE]);
// 		procesor_id = fork();
// 		candf = ft_split(argv[3], ' ');
// 		sourcepath = search_path(envp, candf[0]);
// 		if (procesor_id == 0)
// 			offspring_write(argv, envp, sourcepath, fd1);
// 		else
// 			close(fd1[READ_SIDE]);
// 		i = 0;
// 		while (candf[i])
// 			free(candf[i++]);
// 		free(candf);
// 	}
// 	free(sourcepath);
// }

void	pip_menu(char **argv,char **envp)
{
	int	fd1[2];
	int	procesor_id;
	char	**candf;

	if (pipe(fd1) == -1)
		perror("pipe");
	procesor_id = fork();
	if (procesor_id == 0)
	{
		candf = ft_split_pipex(argv[2]);
		offspring_read(argv, envp, search_path(envp,candf[0]), fd1);
	}
	else
	{
		close(fd1[WRITE_SIDE]);
		procesor_id = fork();
		if (procesor_id == 0)
		{
			candf = ft_split_pipex(argv[3]);
			offspring_write(argv, envp, search_path(envp,candf[0]), fd1);
		}
		else
			close(fd1[READ_SIDE]);
	}
}
