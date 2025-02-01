/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:37:37 by rjesus-d          #+#    #+#             */
/*   Updated: 2024/11/11 15:25:08 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoint;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	sjoint = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!sjoint)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		sjoint[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		sjoint[i + j] = s2[j];
		j++;
	}
	sjoint[i + j] = '\0';
	return (sjoint);
}

/*
#include <stdio.h>

int   main(void)
{
        char    *s1 = "ABCD";
        char    *s2 = "EFGH";
        char    *sjoint;

        printf("s1: \"%s\"\ts2: \"%s\"\n", s1, s2);
        sjoint = ft_strjoin(s1, s2);
        printf("s1 + s2: \"%s\"\n", sjoint);
        return (0);
}*/
