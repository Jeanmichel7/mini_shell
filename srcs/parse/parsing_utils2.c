/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:10:51 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/01 17:30:01 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (1);
}

char	**ft_envcpy(char **env)
{
	int		i;
	char	**ptr;
	char	*str;

	i = 0;
	while (env[i] != NULL)
		i++;
	ptr = ft_calloc((i + 1), sizeof(char **));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		str = ft_calloc((ft_strlen(env[i]) + 1), sizeof(char));
		if (str == NULL)
		{
			ft_freetab(ptr);
			return (NULL);
		}
		ft_strlcpy(str, env[i], (ft_strlen(env[i]) + 1));
		ptr[i] = str;
		i++;
	}
	return (ptr);
}

char	*ft_if_quotes_not_closes(t_data *data)
{
	char	*ptr;
	char	*temp;
	int		i;
	int		omit;

	i = -1;
	omit = 0;
	ptr = NULL;
	while (data->temp[++i])
		omit = ft_omit_quote_apostrophe(data->temp[i], omit, NULL, 1);
	if (omit != 0)
	{
		temp = data->temp;
		data->temp = ft_strjoin_andadd_rt(data->temp, NULL);
		free(temp);
		if (data->temp == NULL)
			return (NULL);
		while (omit != 0)
		{
			omit = ft_retrieve_string(omit, data, temp, ptr);
			if (omit == ERROR_MEMORY)
				return (NULL);
		}
		i = 0;
	}
	return (data->temp);
}
/*
int	ft_free(t_data data)
{
	int		i;
	int 	u; 
	int 	total; 
	t_input	*ptr;

	i = 0;
	while (i <= data->nb_pipe)
	{
		u = 0;
		ptr = data->inputs[i];
		total = ptr->redir_double_output + ptr->redir_output + ptr->redir_input 
			+ ptr->redir_double_input ;
		files[0];
		
		
}
*/
int	ft_yerror(int nb, t_data *data)
{
	data = (t_data *)data;
	if (nb == ERROR_PIPE)
	{
		fprintf(stderr, "bash: syntax error near unexpected token `|'\n");
		return (258);
	}
	if (nb == ERROR_MEMORY)
	{
		fprintf(stderr, "Error! memory not allocated");
		return (5);
	}
	if (nb == ERROR_REDIRECTION)
		return (258);
	return (1);
}
