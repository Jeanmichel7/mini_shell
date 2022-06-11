/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:27:48 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/11 16:06:47 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR_PIPE 1001
# define ERROR_MEMORY 1002
# define ERROR_REDIRECTION 1003

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
	IN = 1,
	OUT,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_file
{
	char	*name;
	t_type	type;
	int		fd;
}	t_file;

typedef struct s_input
{
	t_file			*file;
	int				tube[2];
	int				redir_input;
	int				redir_output;
	int				redir_double_input;
	int				redir_double_output;
	char			*cmd_fct;
	char			**cmds;
	int				pipe;
	pid_t			child;
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
	int				fd_in_saved;
	int				fd_out_saved;
}	t_data;

/* PARSING */
/* ERR */
int		ft_check_fds(t_data *data, int i);
void	ft_errputstr(char *str, int stop, int code, t_data *data);
int		ft_yprint_input(t_data *data);
int		ft_yparsing(t_data *data);
char	**ft_split_and_omit(char const *s, char c, int keep_quotes);
int		ft_omit_quote_apostrophe(char c, unsigned int omit, unsigned int *i, int keep_quotes);
char	*ft_strjoin_andadd_rt(char const *s1, char const *s2);
int 	ft_parse_redirection(t_data *data); 
char	**ft_split_redirection(char const *s);
char	**ft_replace_elements(char **tab, char **elements, int *pos);
int		ft_freetab(char **tab);
int		ft_print_tab(char **tab);
//int		ft_which_redirection_take_on_board(const char *s, t_li **list);
int		ft_which_redirection_take_on_board(char *s);
int		ft_omit_quote_apostrophe(char c, unsigned int omit, unsigned int *i, int keep_quotes);
int		ft_ycheck_pipe(char *temp);
char	*ft_if_quotes_not_closes(t_data *data);
char 	**ft_envcpy(char **env);
void	*ft_create_inputs(t_data *data);
int		ft_yerror(int nb, t_data *data);
int		ft_check_and_replace_var(char **str, char **env);
int		ft_replace_var(char **str, char **env, int *i, int *j);
int		ft_checkvar(char *str, char *var, int *k);
int		ft_strcpy_var(char **str, char *value, int length_name, int start);
int		ft_retrieve_string(int omit, t_data *data, char *temp, char *ptr);
int		ft_print_error(int rd);
int 	ft_type_redirection(char **str);
int		ft_search_pattern(char *str, char *pattern);
int		ft_update_file(char *str, t_file **files, int total, int rd);
char	**ft_delete_rd(char **tab);
char 	**ft_delete_filename_in_cmd(char **tab, int pos);
char	 **ft_delete_files_name(char **tab, int pos, int rd);
int		ft_extract_line(char *ptr, char **str, char *temp, char *pattern);

/* EXECUTION */
void	ft_exec_parse(t_data *data);
void	ft_pipe(t_data *data);
int		ft_check_cmds(char *fct, char *fct_name);
char	*ft_check_access(t_data *data, int i);
void	ft_close_redir(t_data *data, int i);

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

/* FREE */
void	ft_free_inputs(t_data *data);
void	ft_free_section(t_data *data, int i);
void	ft_free(t_data *data);
void	ft_free_tab(char **tab);
//void	*ft_freetab(char **tab);

#endif
