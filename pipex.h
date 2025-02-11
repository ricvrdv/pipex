/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:29:49 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/11 18:41:47 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include "./libft/libft.h"

void	create_pipe(int *pipefd);
pid_t	fork_process(void);
void	setup_child(char *argv[], int *pipefd, char *envp[]);
void	setup_parent(char *argv[], int *pipefd, char *envp[]);
void	close_fd(int *pipefd);
void	ft_free(char *str[]);
void	execute_command(char *cmd, char *envp[]);
void	check_envp(char *envp[]);

#endif
