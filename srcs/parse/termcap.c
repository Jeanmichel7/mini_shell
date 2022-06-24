/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:06:34 by ydumaine          #+#    #+#             */
/*   Updated: 2022/06/24 18:55:13 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
char	*ft_getenv(char *name, t_data *data)
{
	int		j;
	char	**temp;
    char    *ptr;

	j = 0;
	while (data->env && data->env[j])
	{
		temp = ft_split(data->env[j], '=');
		if (ft_strlen(name) == ft_strlen(temp[0])
			&& ft_strncmp(name, temp[0], ft_strlen(name)) == 0)
		{
            ptr = malloc(sizeof(char) * (ft_strlen(temp[1]) + 1));
            ft_memcpy(ptr, temp[1], ft_strlen(temp[1]) + 1);
			ft_free_tab(temp);
			return (ptr);
		}
		ft_free_tab(temp);
		j++;
	}
	return (0);
}

int ft_init_term()
{
    int ret;
    char *term_type;
    term_type = ft_getenv("TERM", data);

    if (term_type == NULL)
    {
        fprintf(stderr, "TERM must be set (see 'env').\n");
        return -1;
    }

    ret = tgetent(NULL, term_type);

    if (ret == -1)
    {
        fprintf(stderr, "Could not access to the termcap database..\n");
        return -1;
    }
    else if (ret == 0)
    {
        fprintf(stderr, "Terminal type '%s' is not defined in termcap 
		database (or have too few informations).\n", term_type);
        return -1;
    }

    return 0;
}
*/

/*
void	ft_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
*/

void	ft_handle_signal(int sig)
{
	HIST_ENTRY	**list;
	int 		i; 
	int			j;

	j = 0;
	list = history_list();
	if (sig == SIGINT)
	{
		if (list)
		{
			i = 0;
			while (list[i])
				i++;
			i--;
			while (list[i]->line[j] && (list[i]->line[j] == ' ' || list[i]->line[j] == 34 || list[i]->line[j] == 39))
				j++;
			if (list && ft_strncmp(&(list[i]->line[j]),"cat", 3) == 0) 
				return ; 
		}
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error_code = 1; 
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int	ft_init_term(t_data *data)
{
	int				rc;
	struct termios	termios;

	signal(SIGINT, &ft_handle_signal);
	signal(SIGQUIT, &ft_handle_signal);
	rc = tcgetattr(0, &data->termios_save);
	termios = data->termios_save;
	termios.c_lflag &= ~ECHOCTL;
	termios.c_cc[VMIN] = 100;
	termios.c_cc[VTIME] = 100;
	rc = tcsetattr(0, 0, &termios);
	return (rc);
}
