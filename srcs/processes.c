/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:57:09 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/24 10:57:10 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("Error: Failed opening pipe");
		exit(EXIT_FAILURE);
	}
}

pid_t	fork_process(int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: Failed forking the process");
		close_fd(pipefd);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	setup_io(int input_fd, int output_fd, int *pipefd, int pipe_end)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("Error: dup2 failed for input_fd");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("Error: dup2 failed for output_fd");
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
	close(pipefd[pipe_end]);
	if (pipe_end == 0)
		close(pipefd[1]);
	else
		close(pipefd[0]);
}

void	setup_child(char *argv[], int *pipefd, char *envp[])
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0444);
	if (infile == -1)
	{
		perror("Error: Failed to open file");
		close_fd(pipefd);
		exit(EXIT_FAILURE);
	}
	setup_io(infile, pipefd[1], pipefd, 0);
	execute_command(argv[2], envp);
}

void	setup_parent(char *argv[], int *pipefd, char *envp[])
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("Error: Failed to create or open file");
		close_fd(pipefd);
		exit(EXIT_FAILURE);
	}
	setup_io(pipefd[0], outfile, pipefd, 1);
	execute_command(argv[3], envp);
}
