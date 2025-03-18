/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:57:45 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/24 10:57:56 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include "./libft/libft.h"

// PROCESSES
void	create_pipe(int *pipefd);
pid_t	fork_process(int *pipefd);
void	setup_child(char *argv[], int *pipefd, char *envp[]);
void	setup_parent(char *argv[], int *pipefd, char *envp[]);

// COMMANDS
void	execute_command(char *cmd, char *envp[]);

// UTILS
void	close_fd(int *pipefd);
void	ft_free(char *str[]);
void	check_envp(char *envp[]);

#endif
