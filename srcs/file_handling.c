/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:06 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/02/06 13:41:25 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("Error: Failed to open file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	create_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("Error: Failed to create or open file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
