/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:39:50 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/06 13:41:39 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	infile = open_file(argv[1], 0_RDONLY, 0);
	outfile = create_file(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	create_pipe(pipefd);
	pid = fork_process();
	if (pid == 0)
		setup_child(infile, pipefd, argv[2], envp);
	setup_parent(outfile, pipefd, argv[3], envp);
	close(infile);
	close(outfile);
	return (0);
}
