/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:59:12 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/03 23:59:13 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static void	clean( char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
			i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

static int	length(char const *s, int i, char c)
{
	int	len_word;

	len_word = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len_word++;
	}
	return (len_word);
}

static char	**mini_split(char **arr, const char *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		if (s[i] != c)
		{
			arr[j] = malloc((length(s, i, c) + 1) * sizeof(char));
			if (!arr[j])
				return (NULL);
			while (s[i] != c && s[i])
				arr[j][k++] = s[i++];
			arr[j][k] = 0;
			j++;
		}
		else
			i++;
	}
	arr[j] = NULL;
	return (arr);
	clean(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc((count(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!mini_split(arr, s, c))
	{
		clean(arr);
	}
	return (arr);
}
