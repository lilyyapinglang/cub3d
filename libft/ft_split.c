/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmottini <tmottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:22:40 by tmottini          #+#    #+#             */
/*   Updated: 2025/06/18 11:50:38 by tmottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (NULL);
}

static int	ft_count_items(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_putitem(char *item, char const *s, int i, int word)
{
	int	j;

	j = 0;
	while (word > 0)
	{
		item[j] = s[i - word];
		j++;
		word--;
	}
	item[j] = '\0';
	return (item);
}

static char	**ft_split_items(char const *s, char c, char **s2, int num_items)
{
	int	i;
	int	item;
	int	word;

	i = 0;
	item = 0;
	word = 0;
	while (item < num_items)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word++;
		}
		s2[item] = (char *)malloc(sizeof(char) * (word + 1));
		if (!s2[item])
			return (free_array(s2, item));
		ft_putitem(s2[item], s, i, word);
		word = 0;
		item++;
	}
	s2[item] = NULL;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num_items;

	if (!s)
		return (NULL);
	num_items = ft_count_items(s, c);
	s2 = (char **)malloc(sizeof(char *) * (num_items + 1));
	if (!s2)
		return (NULL);
	return (ft_split_items(s, c, s2, num_items));
}
