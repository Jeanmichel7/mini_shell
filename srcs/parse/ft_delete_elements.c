/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:52:53 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/02 01:24:33 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **ft_delete_rd(char **tab)
{
	int	i;
	int length;
	int	j;
	char **ptr;

	i = 0;
	length = 0;
	while (tab[i])
	{
		if (tab[i][0] != '>' || tab[i][0] != '<')
			length++;
		i++;
	}
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
		{
			ptr[j] = tab[i];
			j++;
		}
		i++;
	}
	return (ptr);
}
