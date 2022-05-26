
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:27:48 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/25 10:52:46 by ydumaine         ###   ########.fr       */
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
	char 	*name;
	char	type;
}	t_file;

typedef struct s_input
{
	pid_t			child;
	pid_t			child2;
	t_fd			*fd;
	int				tube[2];
	char			**env;
	int				redir_input;
	int				redir_output;
	int				redir_double_input;
	int				redir_double_output;
	char			*cmd_fct;
	char			**cmds;
	int				pipe;
}	t_input;

typedef struct s_data
{
	char			**env;
	int				nb_pipe;
	char			*temp;
	char			*prompt;
	int				done;
	HIST_ENTRY		**list;
	t_input			*inputs;
}	t_data;

/* PARSING */

/* EXECUTION */
void	ft_jm_part(t_data *data, char **env);

void	ft_pipe(t_data *data, char **env);
void	ft_check_cmds(char *fct, char *args);
char	*ft_check_access(char **env, char *cmd);

void	ft_errputstr(char *str, int stop, int code, t_data *data);
void	ft_yprint_input(t_data *data);
int		ft_yparsing(t_data *data);
char	**ft_split_and_omit(char const *s, char c, int keep_quotes);
int		ft_omit_quote_apostrophe(char c, unsigned int omit, unsigned int *i, int keep_quotes);
char	*ft_strjoin_andadd_rt(char const *s1, char const *s2);
#endif
