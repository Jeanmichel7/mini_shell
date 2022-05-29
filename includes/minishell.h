/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:27:48 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/29 22:07:59 by jrasser          ###   ########.fr       */
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

typedef enum e_type
{
	HEREDOC = 1,
	IN,
	OUT,
	APPEND
}	t_type;

typedef struct s_file
{
	char	*name;
	t_type	type;
	int		fd;
}	t_file;

typedef struct s_input
{
	pid_t			child;
	t_file			*file;
	int				tube[2];
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
	int				nb_pipe;
	char			*temp;
	char			*prompt;
	int				done;
	char			**env;
	HIST_ENTRY		**list;
	t_input			*inputs;
	int				fd_in_saved;
	int				fd_out_saved;
}	t_data;

/* PARSING */


/* EXECUTION */
void	ft_exec_parse(t_data *data);
void	ft_pipe(t_data *data);
int		ft_check_cmds(char *fct, char *fct_name);
char	*ft_check_access(t_data *data, int i);
void	ft_close_redir(t_data *data, int i);
void	ft_free_sec(t_data *data, int i);

/* BUILTINS */
int		ft_is_builtin(t_data *data, int i);
int		ft_is_new_local_var(t_data *data, int i);
void	ft_add_new_local_var(t_data *data, int i);
void	ft_echo(t_data *data, int i);
void	ft_cd(t_data *data, int i);
void	ft_pwd(t_data *data, int i);
void	ft_export(t_data *data, int i);
void	ft_unset(t_data *data, int i);
void	ft_env(t_data *data, int i);
void	ft_exit(t_data *data, int i);


/* ERR */
int		ft_check_fds(t_data *data, int i);
void	ft_errputstr(char *str, int stop, int code, t_data *data);

/* FREE */
void	ft_free_readline(t_data *data);
void	ft_free(t_data *data);
void	ft_free_tab(char **tab);
void	*ft_freetab(char **tab);


#endif