/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:27:48 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/21 15:33:10 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <errno.h>

typedef struct s_fd
{
	char	*file;
	char	type;
}	t_fd; 


typedef struct s_input
{
	pid_t	child;
	t_fd	*tab_fd;
	int		tube[2];
	
	int		redir_input;
	int		redir_output;
	int		redir_double_input;
	int		redir_double_output;
	char	*cmd_fct;
	char	**cmds;
	int		pipe;
	struct s_input *next;
	struct s_input *prev; 	

}	t_input;

typedef struct s_str_input
{
	int		nb_pipe;
	t_input	*input;
}	t_str_input;

typedef struct s_data
{
	char	**env;
	char			*temp;
	char			*prompt;
	int				done;
	HIST_ENTRY 		**list;
	t_str_input		inputs;
}	t_data;

/* PARSING */

/* EXECUTION */
void	ft_jm_part(t_data *data, char **env);

void	ft_pipe(t_data *data, char **env);
void	ft_check_cmds(char *fct1, char *args1, char *fct2, char *args2);
char	*ft_check_access(char **env, char *cmd);

void	ft_errputstr(char *str, int stop, int code, t_data *data);
void	ft_yprint_input(t_input *input);
int		ft_yparsing(t_data *data);
#endif
