/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:00:34 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/22 15:51:26 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static unsigned int	ft_count_rd(const char *s)
{
	unsigned int	count;
	unsigned int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '>' || s[i] == '<') && s[i])
			while ((s[i] == '>' || s[i] == '<') && s[i])
				i++;
		if ((s[i] != '>' || s[i] != '<') && s[i])
		{
			count++;
			while (s[i] != '>' && s[i] != '<' && s[i])
				i++;
		}
	}
	return (count);
}

char	*ft_sub_split_rd(char const *s, unsigned int *j)
{
	char			*str;
	unsigned int	k;

	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	k = 0;
	if ((s[*j] == '<' || s[*j] == '>') && s[*j])
	{
		while ((s[*j] == '>' || s[*j] == '<') && s[*j])
			(*j)++;
	}
	else if (s[*j])
	{
		while (s[*j] != '>' && s[*j] != '<' && s[*j])
			str[k++] = s[(*j)++];
	}
	str[k] = '\0';
	return (str);
}

char	**ft_split_redirection(char const *s)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_rd(s) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_count_rd(s))
	{
		tab[i++] = ft_sub_split_rd(s, &j);
	}	
	tab[i] = NULL;
	return (tab);
}
