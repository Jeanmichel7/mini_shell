/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:52:53 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/22 15:56:01 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_delete_rd(char **tab)
{
	int		i;
	int		j;
	char	**ptr;

	i = -1;
	j = 0;
	if (tab == NULL)
		return (NULL);
	while (tab[++i])
		if (tab[i][0] != '>' || tab[i][0] != '<')
			j++;
	ptr = ft_calloc(j + 1, sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (tab[++i])
	{	
		if (tab[i][0] == '>' || tab[i][0] == '<')
			free(tab[i]);
		else
			ptr[j++] = tab[i];
	}
	free(tab);
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
	free(tab);
	return (ptr);
}
