/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:58:50 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/30 13:26:56 by ydumaine         ###   ########.fr       */
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
	printf("\n valeur de lentgth : %d", length);
	new_tab = ft_calloc(length + 1, sizeof(char *));
	if (new_tab == NULL)
		return (NULL);
	i = -1;
	while (++i < *pos)
	{
		new_tab[i] = tab[i];
		ft_printf("\n boucle 1 : valeur de new_tab[%d] : %s", i, new_tab[i]);
	}
	j = -1;
	while (elements[++j])
	{
		new_tab[i + j] = elements[j];
		ft_printf("\n boucle 2 : valeur de new_tab[%d + %d] : %s", i, j, new_tab[i + j]); 
	}
	while (tab[i])
	{
		new_tab[i + j] = tab[i + 1];
		ft_printf("\n boucle 3 :valeur de new_tab[%d + %d] : %s", i, j, new_tab[i + j]); 
		i++;
	}
	ft_print_tab(new_tab);
	ft_freetab(tab);
	free(elements);
	*pos = *pos + j;
	return (new_tab);
}
