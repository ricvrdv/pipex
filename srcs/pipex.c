/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:39:50 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/19 18:36:34 by applecore        ###   ########.fr       */
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
	pid = fork_process();
	if (pid == 0)
		setup_child(argv, pipefd, envp);
	else
	{
		wait(NULL);
		setup_parent(argv, pipefd, envp);
	}
	return (0);
}
