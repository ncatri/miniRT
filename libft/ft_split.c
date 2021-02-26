/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 07:09:32 by ncatrien          #+#    #+#             */
/*   Updated: 2020/11/26 04:47:55 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		words_count(char const *s, char c)
{
	int count;
	int	word;

	count = 0;
	while (*s)
	{
		if (*s != c)
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

static	int		word_len(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static	char	*copy_sub(char *str, int len)
{
	char *ptr;

	if (!(ptr = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ptr[len] = '\0';
	while (len--)
		ptr[len] = str[len];
	return (ptr);
}

void			free_split(char ***split_ptr, int i)
{
	int j;

	j = -1;
	while (++j < i)
		free((*split_ptr)[j]);
}

char			**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		num_words;

	if (!s)
		return (NULL);
	num_words = words_count(s, c);
	if (!(split = (char**)malloc(sizeof(char*) * (num_words + 1))))
		return (NULL);
	i = -1;
	while (++i < num_words)
	{
		while (*s == c)
			s++;
		split[i] = copy_sub((char*)s, word_len((char*)s, c));
		if (!split[i])
		{
			free_split(&split, i);
			free(split);
			return (NULL);
		}
		s += word_len((char*)s, c);
	}
	split[i] = NULL;
	return (split);
}
