/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_andadd_rt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:00:13 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/31 12:40:05 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_andadd_rt(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	s1_len;

	s1_len = ft_strlen(s1);
	str = malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 2));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	if (s2 != NULL)
	{
		while (s2[i - s1_len])
		{
			str[i] = s2[i - s1_len];
			i++;
		}
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}
