/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:56:58 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/24 10:57:03 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	check_envp(envp);
	if (argc != 5)
	{
		ft_putstr_fd("\n\tUsage: ./pipex file1 cmd1 cmd2 file2\n\n", 2);
		exit(EXIT_FAILURE);
	}
	create_pipe(pipefd);
	pid = fork_process(pipefd);
	if (pid == 0)
		setup_child(argv, pipefd, envp);
	else
	{
		if (wait(NULL) == -1)
		{
			perror("Error: wait failed");
			close_fd(pipefd);
			exit(EXIT_FAILURE);
		}
		setup_parent(argv, pipefd, envp);
	}
	return (0);
}
