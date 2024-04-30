/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhnal <muhnal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:26:01 by muhnal            #+#    #+#             */
/*   Updated: 2022/11/21 09:47:55 by muhnal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function counts the number of words
static int	count_words(char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			words++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (words);
}

// Function returns the length of chars before the next separator
static int	find_word_length(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

// Functions allocates and copies to a new variable the word
static char	*create_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = find_word_length(str, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

// Function splits a string of chars depending on char
char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**strings;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	strings = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!strings)
		return (NULL);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			strings[i] = create_word(str, c);
			i++;
		}
		while (*str && *str != c)
			str++;
	}
	strings[i] = 0;
	return (strings);
}
