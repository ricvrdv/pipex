/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:29:49 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/19 14:13:13 by applecore        ###   ########.fr       */
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
pid_t	fork_process(void);
void	setup_child(char *argv[], int *pipefd, char *envp[]);
void	setup_parent(char *argv[], int *pipefd, char *envp[]);

// COMMANDS
void	execute_command(char *cmd, char *envp[]);

// UTILS
void	close_fd(int *pipefd);
void	ft_free(char *str[]);
void	check_envp(char *envp[]);

#endif
