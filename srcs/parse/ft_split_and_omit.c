/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_and_omit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:00:34 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/29 16:23:11 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct relative_data
{
	unsigned int	count;
	unsigned int	i;
	unsigned int	omit;
	int				new_part;
}	t_r_data;

int	ft_check_part(t_r_data *r_data, int keep_quotes, char c, const char *s)
{
	while ((s[r_data->i] != c || r_data->omit != 0) && s[r_data->i])
	{
		if (keep_quotes == 0 && ((s[r_data->i] == 34 && r_data->omit == 1)
				|| (s[r_data->i] == 39 && r_data->omit == 2)
				|| (s[r_data->i] == 34 && r_data->omit == 0)
				|| (s[r_data->i] == 39 && r_data->omit == 0)))
		{
			r_data->omit = ft_omit_quote_apostrophe(s[r_data->i],
					r_data->omit, &(r_data->i), keep_quotes);
			continue ;
		}
		else if (keep_quotes == 1)
			r_data->omit = ft_omit_quote_apostrophe(s[r_data->i],
					r_data->omit, &(r_data->i), keep_quotes);
		(r_data->i)++;
		r_data->new_part = 1;
	}	
	return (0);
}

static unsigned int	ft_count_v2(const char *s, char c, int keep_quotes)
{
	t_r_data	r_data;

	r_data.new_part = 0;
	r_data.i = 0;
	r_data.count = 0;
	r_data.omit = 0;
	while (s[r_data.i])
	{
		while (s[r_data.i] == c && s[r_data.i])
			r_data.i++;
		r_data.new_part = 0;
		ft_check_part(&r_data, keep_quotes, c, s);
		if (s[r_data.i] && r_data.omit == 0)
			r_data.count++;
		else
			if (s[r_data.i - 1] != c && s[r_data.i] == 0 && r_data.omit == 0
				&& r_data.new_part == 1)
				r_data.count++;
	}
	return (r_data.count);
}

char	*ft_add_zero(int k, char *str)
{
	str[k] = '\0';
	return (str);
}

char	*ft_sub_split_v2(char const *s, char c,
unsigned int *j, int keep_quotes)
{
	char			*str;
	unsigned int	k;
	unsigned int	omit;

	omit = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	k = 0;
	while (s[*j] == c && s[*j])
		(*j)++;
	while ((s[*j] != c || omit != 0) && s[*j])
	{
		if (keep_quotes == 0 && ((s[*j] == 34 && omit == 1)
				|| (s[*j] == 39 && omit == 2) || (s[*j] == 34 && omit == 0)
				|| (s[*j] == 39 && omit == 0)))
		{
			omit = ft_omit_quote_apostrophe(s[*j], omit, j, keep_quotes);
			continue ;
		}
		else if (keep_quotes == 1)
			omit = ft_omit_quote_apostrophe(s[*j], omit, j, keep_quotes);
		str[k++] = s[(*j)++];
	}
	return (ft_add_zero(k, str));
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
