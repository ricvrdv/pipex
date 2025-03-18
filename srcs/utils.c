/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:57:16 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/24 10:57:19 by rjesus-d         ###   ########.fr       */
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

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	check_envp(char *envp[])
{
	int	i;

	i = 0;
	if (!envp[i])
	{
		perror("Error: No environment variables");
		exit(EXIT_FAILURE);
	}
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
	{
		perror("Error: No PATH variable");
		exit(EXIT_FAILURE);
	}
}
