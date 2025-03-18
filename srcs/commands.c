/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:56:47 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/24 10:56:52 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*search_path(char **dirs, char *cmd)
{
	char	*half_path;
	char	*path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		half_path = ft_strjoin(dirs[i], "/");
		if (!half_path)
			return (NULL);
		path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	*find_dir(char *cmd, char**envp)
{
	char	**full_path;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	full_path = ft_split(envp[i] + 5, ':');
	if (!full_path)
		return (NULL);
	path = search_path(full_path, cmd);
	ft_free(full_path);
	return (path);
}

void	execute_command(char *cmd, char **envp)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split)
	{
		perror("Error: Failed splitting the command into arguments");
		exit(EXIT_FAILURE);
	}
	path = find_dir(cmd_split[0], envp);
	if (!path)
	{
		ft_free(cmd_split);
		perror("Error: Invalid path");
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd_split, envp) == -1)
	{
		ft_free(cmd_split);
		free(path);
		perror("Error: execve failed");
		exit(EXIT_FAILURE);
	}
}
