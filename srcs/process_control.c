/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:39:10 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/06 14:00:27 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	create_pipe(int pipefd[])
{
	if (pipe(pipefd) == -1)
	{
		perror("Error: Failed opening pipe");
		exit(EXIT_FAILURE);
	}
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: Failed forking the process");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	setup_child(int infile, int pipefd[], char *cmd1, char **envp)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	execute_command(cmd1, envp, pipefd);
}

void	setup_parent(int outfile, int pipefd[], char *cmd2, char **envp)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	execute_command(cmd2, envp, pipefd);
}
