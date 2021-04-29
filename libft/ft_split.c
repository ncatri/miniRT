/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 07:09:32 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/15 14:07:02 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char c, char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

static	int	words_count(char *s, char *charset)
{
	int	count;
	int	word;

	count = 0;
	while (*s)
	{
		if (!is_separator(*s, charset))
			word = 1;
		else
		{
			if (word)
			{
				count++;
				word = 0;
			}
		}
		s++;
	}
	if (word)
		count++;
	return (count);
}

static	int	word_len(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !is_separator(str[i], charset))
		i++;
	return (i);
}

static	char	*copy_sub(char *str, int len)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr)
	{
		ptr[len] = '\0';
		while (len--)
			ptr[len] = str[len];
	}
	return (ptr);
}

char	**ft_split(char const *s, char *charset)
{
	char	**split;
	int		i;
	int		num_words;

	if (!s)
		return (NULL);
	num_words = words_count((char *)s, charset);
	split = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (split)
	{
		i = -1;
		while (++i < num_words)
		{
			while (is_separator(*s, charset))
				s++;
			split[i] = copy_sub((char *)s, word_len((char *)s, charset));
			if (!split[i])
				return (free_split(split));
			s += word_len((char *)s, charset);
		}
		split[i] = NULL;
	}
	return (split);
}
