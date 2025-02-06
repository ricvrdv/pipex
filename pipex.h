/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:29:49 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/06 15:25:07 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "./libft/libft.h"

int		open_file(char *filename, int flags, mode_t mode);
int		create_file(char *filename, int flags, mode_t mode);

void	create_pipe(int pipefd[]);
pid_t	fork_process(void);
void	setup_child(int infile, int pipefd[], char *cmd1, char **envp);
void	setup_parent(int outfile, int pipefd[], char *cmd2, char **envp);

void	ft_free(char *str[]);
char	*find_dir(char *cmd, char **envp);
void	execute_command(char *cmd, char **envp, int pipefd[]);

#endif
