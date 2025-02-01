/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:34:11 by rjesus-d          #+#    #+#             */
/*   Updated: 2024/11/11 15:24:12 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

/*
#include <stdio.h>

int   main(void)
{
        char    *string_1 = "Back to back";
        char    *string_2 = "";
        char    *substring_1;
        char    *substring_2;
        size_t  len_1 = 4;
        size_t  len_2 = 2;
        unsigned int    start_1 = 8;
        unsigned int    start_2 = 2;

        printf("String 1: \"%s\"\tMax length: %zu\n", string_1, len_1);
        substring_1 = ft_substr(string_1, start_1, len_1);
        printf("Substring 1: \"%s\"\n\n", substring_1);

        printf("String 2: \"%s\"\tMax length: %zu\n", string_2, len_2);
        substring_2 = ft_substr(string_2, start_2, len_2);
        printf("Substring 2: \"%s\"\n", substring_2);
        return (0);
}*/
