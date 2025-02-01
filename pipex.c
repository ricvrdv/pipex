#include "pipex.h"

static int	open_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("Opening the file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	create_pipe(int pipefd[])
{
	if (pipe(pipefd) == -1)
	{
		perror("Opening the pipe");
		exit(EXIT_FAILURE);
	}
}

static pid_t	fork_process()
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Forking the process");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	execute_command(char *cmd, char **envp)
{
	char **arg_split;

	arg_split = ft_split(cmd, ' ');
	if (!arg_split)
	{
		perror("Splitting the command into arguments");
		exit(EXIT_FAILURE);
	}
	execve(arg_split[0], arg_split, envp);
	perror("execv failed");
	free_all(arg_split, count_words(cmd, ' '));
	exit(EXIT_FAILURE);
}

static void	setup_child1(int infile, int pipefd[], char *cmd1, char **envp)
{
	close(pipefd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_command(cmd1, envp);
}

static void	setup_child2(int outfile, int pipefd[], char *cmd2, char **envp)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[0]);
	execute_command(cmd2, envp);
}

int main (int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: [executable] file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	infile = open_file(argv[1], O_RDONLY, 0);
	outfile = open_file(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	create_pipe(pipefd);
	pid1 = fork_process();
	if (pid1 == 0)
	{
		setup_child1(infile, pipefd, argv[2], envp);
	}
	pid2 = fork_process();
	if (pid2 == 0)
	{
		setup_child2(outfile, pipefd, argv[3], envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}