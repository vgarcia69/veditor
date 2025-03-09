/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:54:52 by vgarcia           #+#    #+#             */
/*   Updated: 2025/02/21 12:51:44 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

int	count_word(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j] && s[j] != '\n')
	{
		if (s[j] == c)
			++j;
		else
		{
			if (!j || s[j - 1] == c)
				++i;
			++j;
		}
	}
	return (i);
}

static int	cut_word(char **s, char c)
{
	int	i;

	i = 0;
	while (**s && **s != c)
	{
		i++;
		(*s)++;
	}
	while (**s && **s == c)
		(*s)++;
	return (i);
}

static char	**fill_strs(char **strs, char const *str, char c)
{
	int		i;
	int		j;
	int		word_cut;
	char	*to_cut;

	to_cut = (char *)str;
	i = 0;
	while (*str != '\0')
	{
		word_cut = cut_word(&to_cut, c);
		strs[i] = malloc(sizeof(char) * (word_cut + 1));
		if (strs[i] == NULL)
		{
			free_tab(strs);
			return (NULL);
		}
		strs[i][word_cut] = '\0';
		j = 0;
		while (*str && *str != c)
			strs[i][j++] = *str++;
		while (*str != '\0' && *str == c)
			str++;
		i++;
	}
	return (strs);
}

char	**ft_split(char const *str, char c)
{
	char	**strs;
	int		words_count;

	if (!str)
		return (NULL);
	words_count = count_word(str, c);
	strs = malloc(sizeof(char *) * (words_count + 1));
	if (strs == NULL)
		return (NULL);
	strs[words_count] = NULL;
	strs = fill_strs(strs, str, c);
	return (strs);
}
