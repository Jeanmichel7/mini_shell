/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:58:50 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/11 14:54:30 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_copy_elements(char **tab, char **new_tab, char **elements, int *pos)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < *pos)
		new_tab[i] = tab[i];
	while (elements[++j])
		new_tab[i + j] = elements[j];
	while (tab[i])
	{
		new_tab[i + j] = tab[i + 1];
		i++;
	}
	return (j);
}

char	**ft_replace_elements(char **tab, char **elements, int *pos)
{
	int		i;
	int		j;
	int		length;
	char	**new_tab;

	if (tab == NULL)
		return (NULL);
	length = 0;
	i = -1;
	while (tab[++i])
		length++;
	i = -1;
	length--;
	while (elements[++i])
		length++;
	new_tab = ft_calloc(length + 1, sizeof(char *));
	if (new_tab == NULL)
		return (NULL);
	j = ft_copy_elements(tab, new_tab, elements, pos);
	free(tab[*pos]);
	//ft_free_tab(tab);
	free(elements);
	*pos = *pos + j;
	return (new_tab);
}
