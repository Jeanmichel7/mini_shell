/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:47:30 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/01 13:36:04 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
t_li	*ft_lsti_new_t_li(int content)
{
	t_li	*ptr;

	ptr = malloc(sizeof(t_li));
	if (ptr == NULL)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

t_li	*ft_lstlast_t_li(t_li *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_t_li(t_li **lst, t_li *new)
{
	t_li	*ptr;

	if (*lst == NULL)
		*lst = new;
	else if (new != NULL)
	{
		ptr = ft_lstlast_t_li(*lst);
		ptr->next = new;
	}
}
*/

int	ft_which_redirection_take_on_board(char *s)
{
	unsigned int i; 
	unsigned int omit; 

	i = 0; 
	omit = 0;
	omit = ft_omit_quote_apostrophe(s[i], omit, NULL, 0);
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
		{
			if (omit != 0)
			{
				if (s[i] == '>')
					s[i] = -1;
				if (s[i] == '<')
					s[i] = -2;
			}
		}
		i++;
		omit = ft_omit_quote_apostrophe(s[i], omit, NULL, 0);
	}
	return (0);
}
/*
int	ft_which_redirection_take_on_board(const char *s, t_li **list)
{
	unsigned int i; 
	unsigned int omit; 
	t_li		 *ptr;

	i = 0; 
	omit = 0;
	omit = ft_omit_quote_apostrophe(s[i], omit, NULL, 0);
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
		{
			if (omit != 0)
			{
				ptr = ft_lsti_new_t_li(1);
				if (ptr == NULL)
					return (ERROR_MEMORY);
				ft_lstadd_back_t_li(list, ptr);
			}
			else 
			{
				ptr = ft_lsti_new_t_li(1);
				if (ptr == NULL)
					return (ERROR_MEMORY);
				ft_lstadd_back_t_li(list, ptr);
			}
		}
		i++;
		omit = ft_omit_quote_apostrophe(s[i], omit, NULL, 0);
	}
	return (0);
}
*/
