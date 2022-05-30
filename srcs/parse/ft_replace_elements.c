/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:58:50 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/30 17:08:56 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_replace_elements(char **tab, char **elements, int *pos)
{
	int	i; 
	int	j;
	int length; 	
	char **new_tab;
	
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
	i = -1;
	while (++i < *pos)
		new_tab[i] = tab[i];
	j = -1;
	while (elements[++j])
		new_tab[i + j] = elements[j];
	while (tab[i])
	{
		new_tab[i + j] = tab[i + 1];
		i++;
	}
	free(tab[*pos]);
	free(elements);
	*pos = *pos + j;
	return (new_tab);
}
