/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:50:22 by ydumaine          #+#    #+#             */
/*   Updated: 2022/07/04 20:35:01 by ydumaine         ###   ########.fr       */
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
	if (value != NULL)
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
		if (var[j] == '=' && (str[j] == ' ' || str[j] == '\0'
				|| str[j] == 34 || str[j] == 39 || str[j] == '\n'))
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

int	ft_add_g_error_code(char **str, int *i, int *j)
{
	char	*ptr;

	ptr = ft_itoa(g_error_code);
	if (ptr == NULL || ft_strcpy_var(str, ptr, *j + 2, *i - 1) == 1)
	{
		if (ptr != NULL)
			free(ptr);
		return (1);
	}
	free(ptr);
	return (0);
}

int	ft_replace_var(char **str, char **env, int *i, int *j)
{
	(*i)++;
	if ((*str)[*i] == '?')
		return (ft_add_g_error_code(str, i, j));
	while (*env != NULL)
	{
		if (ft_checkvar(&(*str)[*i], *env, j) == 1)
			return (ft_strcpy_var(str, &(*env)[*j], *j, *i - 1));
		env = env + 1;
	}
	while ((*str)[*i + *j] != ' ' && (*str)[*i + *j] != '\0')
		(*j)++;
	return (ft_strcpy_var(str, NULL, *j + 1, *i - 1));
}

int	ft_check_and_replace_var(char **str, char **env)
{
	int	i;
	int	j;
	int	omit;

	i = 0;
	j = 0;
	omit = 0;
	if ((*str) == NULL)
		return (0);
	while ((*str)[i] != 0)
	{
		omit = ft_omit_quote_apostrophe((*str)[i], omit, NULL, 0);
		if ((*str)[i] == '$' && omit != 2 &&
			(*str)[i + 1] != ' ' && (*str)[i + 1] != '\0' &&
				(*str)[i + 1] != 34)
			if (ft_replace_var(str, env, &i, &j) == 1)
				return (ERROR_MEMORY);
		i++;
	}
	return (0);
}

/*
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
		if (ptr[i].file == NULL)
			return (NULL);
		ptr[i].file->type = 0;
		ptr[i].child = -1;
		i++;
	}
	data->inputs = ptr;
	return (NULL);
}
*/