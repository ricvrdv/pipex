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

static void	ft_free(char *str[])
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	*find_dir(char *cmd, char **envp)
{
	char	*half_path;
	char	**full_path;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	full_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (full_path[i])
	{
		half_path = ft_strjoin(full_path[i], "/");
		path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free(full_path);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(full_path);
	return (NULL);
}

static void	execute_command(char *cmd, char **envp, int pipefd[])
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split)
	{
		perror("Splitting the command into arguments");
		exit(EXIT_FAILURE);
	}
	path = find_dir(cmd_split[0], envp);
	if (!path)
	{
		ft_free(cmd_split);
		perror("invalid path");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd_split, envp) == -1)
	{
		ft_free(cmd_split);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
}

static void	setup_child(int infile, int pipefd[], char *cmd1, char **envp)
{
	close(pipefd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	//close(pipefd[1]);
	execute_command(cmd1, envp, pipefd);
}

static void	setup_parent(int outfile, int pipefd[], char *cmd2, char **envp)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	//close(pipefd[0]);
	execute_command(cmd2, envp, pipefd);
}

int main (int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: [executable] file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	infile = open_file(argv[1], O_RDONLY, 0);
	outfile = open_file(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	create_pipe(pipefd);
	pid = fork_process();
	if (pid == 0)
	{
		setup_child(infile, pipefd, argv[2], envp);
	}
	setup_parent(outfile, pipefd, argv[3], envp);
	//close(pipefd[0]);
	//close(pipefd[1]);
	close(infile);
	close(outfile);
	return (0);
}