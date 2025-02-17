/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:25:24 by aleortiz          #+#    #+#             */
/*   Updated: 2025/02/12 19:13:55 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_SIDE 0
# define WRITE_SIDE 1

# include "../utils/src/ft_printf.h"
# include "../utils/libftb/libft.h"
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

void	pip_menu(char **argv,char **envp);
void	offspring_write(char **data, char **envp, char *path, int fd1[2]);
void	offspring_read(char **data, char **envp, char *path, int fd1[2]);
char	*search_path(char **envp, char *command);
char	*create_path(char *key_word, char *command);

#endif


