/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_and_omit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:00:34 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/25 17:36:21 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "../includes/minishell.h"

static unsigned int	ft_count_v2(const char *s, char c, int keep_quotes)
{
	unsigned int	count;
	unsigned int	i;
	unsigned int	omit; 

	i = 0;
	count = 0;
	omit = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			omit = ft_omit_quote_apostrophe(s[i], omit, &i, keep_quotes);
			i++;
		}	
		if (s[i] && omit == 0)
			count++;
		else
			if (s[i - 1] != c && s[i] == 0)
				count++;
	}
	printf("\n valeur de count : %d", count);
	return (count);
}

char	*ft_sub_split_v2(char const *s, char c, unsigned int *j, int keep_quotes)
{
	char			*str;
	unsigned int	k;
	unsigned int	omit;

	omit = 0;
	printf("\n valeur de s dans split : %s", s);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	k = 0;
	while (s[*j] == c && s[*j])
		(*j)++;
	while ((s[*j] != c || omit != 0) && s[*j])
	{
		omit = ft_omit_quote_apostrophe(s[*j], omit, j, keep_quotes);
		str[k++] = s[(*j)++];
	}
	str[k] = '\0';
	return (str);
}

char	**ft_split_and_omit(char const *s, char c, int keep_quotes)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_v2(s, c, keep_quotes) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_count_v2(s, c, keep_quotes))
	{
		tab[i++] = ft_sub_split_v2(s, c, &j, keep_quotes);
	}	
	tab[i] = NULL;
	return (tab);
}
