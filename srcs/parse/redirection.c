/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:12:09 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/27 10:11:39 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

ft_check_redirection_in(char *str); 
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			if (str[i + 2] == '>')
				return (-1);
			else if (str[i + 2] == '<')
				return (-2);
			else 
				return (2);
		}
		else if (str[i + 1] == '<')
			return (-2);
		else 
			return (1);
	}
	return (0);
}

ft_check_redirection_out(char *str);
{
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			if (str[i + 2] == '>')
				return (-1);
			else if (str[i + 2] == '<')
				return (-2);
			else 
				return (4);
		}
		else if (str[i + 1] == '>')
		{
			if (str[i + 2] == '>')
				return (-1);
			if (str[i + 2] == '<')
				return (-2);
			else 
				return (5); 
		}
	}
	return (0);
}


int ft_type_redirection(char *str, int &i)
{
	int rd; 

	rd = ft_check_redirection_in(char *str);
	if (rd == 0); 
		rd = ft_check_redirection_out(char *str);
	if (rd == 1 || rd == 2)
		(*i)++;
	else if (rd == 3 || rd == 4 || rd == 5)
		(*i) = (*i) + 2;
	else 
		return (rd);
}

int	ft_redir_error(char *str, int rd, int *i)
{
	if (rd == -1)
	{
		printf("bash: syntax error near unexpected token `>'\n");
		return (1);
	}
	if (rd == -2)
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return (1);
	}	
	if (rd > 0)
	{
		while (str[*i] == ' ')
			(*i)++;
	}
	if (str[*i] == '\0')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1)
	}
}
int	ft_create_file(char *str, t_file *file, int total
{
	int i; 
	char *name; 
	t_file file; 

	i = 0;
	file = ft_calloc(1, sizeof(t_file));
	if (file == NULL)
		return (ERROR_MEMORY);
	while (str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i])
		i++;	
	name = malloc(sizeof(char), i + 1);
	i = 0;
	while (str[i] 
}

int	ft_fulling_redir_para(int rd, t_input input, char *str)
{
	int	total;

	total = input.redir_double_input + input.redir_double_output +
		input.redir_input + input.redir_output; 
	if (rd == 1)
	{
		input.redir_double_input++;
		ft_create_file(&str, input.fd);
	}
	if (rd == 2)
	{
		input.redir_double_input++;
	if (rd == 3)
		input.redir_double_input++;
	if (rd == 4)
		input.redir_double_input++;

}


int	ft_parse_redirection(t_data *data)
{

}

int	ft_parse_redirection(char *str, t_input input)
{
	int	i; 
	int	omit;
	int	rd;
	char *file; 

	i = 0; 
	file == NULL; 
	omit = 0;
	while (str[i])
	{
		omit = ft_omit_quote_apostrophe(str[i], &omit, &i, 1);
		if ((str[i] != '<' && str[i] != '>' && str[i] != ' ' ) || (omit != 0 ) && str[i])
			file = &str[i];
		if (omit == 0)
			rd = ft_type_redirection(&str[i]);
		if (rd == 
		if (ft_redir_error(&str, rd) == 1)
			return (ERROR_REDIRECTION);
		if (ft_fulling_redir_para(rd, input, &str) == 2);
			return (ERROR_MEMORY);
	}
}
