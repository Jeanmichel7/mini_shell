/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:50:22 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/01 20:38:06 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcpy_var(char **str, char *value, int length_name, int start)
{
	char	*ptr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ptr = ft_calloc((ft_strlen(*str) - length_name)
			+ ft_strlen(value) + 1, sizeof(char));
	if (ptr == NULL)
		return (1);
	while (++i < start)
		ptr[i] = (*str)[i];
	while (value[++j])
		ptr[i + j] = value[j];
	while ((*str)[i + length_name])
	{
		ptr[j + i] = (*str)[i + length_name];
		i++;
	}
	ptr[j + i] = 0;
	free(*str);
	*str = ptr;
	return (0);
}

int	ft_checkvar(char *str, char *var, int *k)
{
	int	j;

	j = 0;
	while (var[j])
	{
		if (var[j] == '=')
		{
			*k = j + 1;
			return (1);
		}
		if (var[j] != str[j])
			break ;
		j++;
	}
	return (0);
}

int	ft_replace_var(char **str, char **env, int *i, int *j)
{
	(*i)++;
	while (*env != NULL)
	{
		if (ft_checkvar(&(*str)[*i], *env, j) == 1)
		{
			if (ft_strcpy_var(str, &(*env)[*j], *j, *i - 1) == 1)
				return (1);
			else
				return (0);
		}
		env = env + 1;
	}
	return (0);
}

int	ft_check_and_replace_var(char **str, char **env)
{
	int	i;
	int	j;
	int	omit;

	i = 0;
	j = 0;
	omit = 0;
	while ((*str)[i] != 0)
	{
		omit = ft_omit_quote_apostrophe((*str)[i], omit, NULL, 0);
		if ((*str)[i] == '$' && omit != 2)
			ft_replace_var(str, env, &i, &j);
		i++;
	}
	return (0);
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
		ptr->file = ft_calloc(1, sizeof(t_file));
		if (ptr->file == NULL)
			return (NULL);
		ptr->file->type = 0;
		ptr->child = -1;
		i++;
	}
	data->inputs = ptr;
	return (NULL);
}
