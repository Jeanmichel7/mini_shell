/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:10:51 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/26 21:04:42 by ydumaine         ###   ########.fr       */
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

int	ft_if_quotes_not_closes(t_data *data)
{
	char	*ptr;
	char	*temp;
	int		i;
	int		omit;

	i = -1;
	ptr = NULL;
	omit = 0;
	while (data->temp[++i])
		omit = ft_omit_quote_apostrophe(data->temp[i], omit, NULL, 1);
	if (omit != 0)
	{
		temp = data->temp;
		data->temp = ft_strjoin_andadd_rt(data->temp, NULL);
		free(temp);
		if (data->temp == NULL)
			return (ERROR_MEMORY);
		while (omit != 0)
		{
			omit = ft_retrieve_string(omit, data, temp, ptr);
			if (omit < -500)
				return (258);
		}
	}
	return (0);
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
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (258);
	}
	if (nb == ERROR_MEMORY)
	{
		write(2, "minishell: Error! memory not allocated", 38);
		return (5);
	}
	if (nb == ERROR_REDIRECTION)
		return (258);
	return (nb);
}

void	*ft_create_inputs(t_data *data)
{
	t_input	*ptr;
	int		i;

	i = 0;
	ptr = ft_calloc((data->nb_pipe + 1), sizeof(t_input));
	if (ptr == NULL)
		return (NULL);
	while (i < (data->nb_pipe + 1))
	{
		ptr[i].file = ft_calloc(1, sizeof(t_file));
		if (ptr->file == NULL)
			return (NULL);
		ptr[i].file->type = 0;
		ptr[i].child = -1;
		i++;
	}
	data->inputs = ptr;
	return (NULL);
}
