/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:52:53 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/03 14:27:38 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_delete_rd(char **tab)
{
	int		i;
	int		length;
	int		j;
	char	**ptr;

	i = -1;
	length = 0;
	while (tab[++i])
		if (tab[i][0] != '>' || tab[i][0] != '<')
			length++;
	ptr = ft_calloc(length + 1, sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tab[i])
	{	
		if (tab[i][0] == '>' || tab[i][0] == '<')
			free(tab[i]);
		else
			ptr[j++] = tab[i];
		i++;
	}
	return (ptr);
}

char	**ft_delete_files_name(char **tab, int pos, int rd)
{
	int		i;
	char	**ptr;
	int		j;

	i = 0;
	j = 0;
	while (tab[i])
		i++;
	ptr = malloc(sizeof(char *) * i);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (tab[j])
	{
		if (j == pos)
			j++;
		else
			ptr[i++] = tab[j++];
	}
	if (rd == 4)
		free(tab[pos]);
	ptr[i] = 0;
	return (ptr);
}
