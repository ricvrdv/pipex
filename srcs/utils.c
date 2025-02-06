/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:22:42 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/06 14:20:09 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free(char *str[])
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

char	*find_dir(char *cmd, char**envp)
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

void	execute_command(char *cmd, char **envp, int pipefd[])
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split)
	{
		perror("Error: Failed splitting the command into arguments.");
		exit(EXIT_FAILURE);
	}
	path = find_dir(cmd_split[0], envp);
	if (!path)
	{
		ft_free(cmd_split);
		perror("Error: Invalid path");
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
