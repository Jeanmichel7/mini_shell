/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:27:48 by jrasser           #+#    #+#             */
/*   Updated: 2022/07/04 20:02:51 by ydumaine         ###   ########.fr       */
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

int	g_error_code;

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
	pid_t			child;
}	t_input;

typedef struct s_data
{
	char			**env;
	int				nb_pipe;
	char			*temp;
	char			*prompt;
	int				color_prompt;
	int				chang_color_prompt;
	int				done;
	HIST_ENTRY		**list;
	t_input			*inputs;
	int				fd_in_saved;
	int				fd_out_saved;
	struct termios	termios_save;
}	t_data;

/* PARSING */
/* ERR */
int		ft_check_fds(t_data *data, int i);
void	ft_errputstr(char *str, int stop, int code, t_data *data);
int		ft_yprint_input(t_data *data);
int		ft_yparsing(t_data *data);
char	**ft_split_and_omit(char const *s, char c, int keep_quotes);
int		ft_omit_quote_apostrophe(char c, unsigned int omit, unsigned int *i, \
int keep_quotes);
char	*ft_strjoin_andadd_rt(char *s1, char const *s2);
int		ft_parse_redirection(t_data *data);
char	**ft_split_redirection(char const *s);
char	**ft_replace_elements(char **tab, char **elements, int *pos);
int		ft_freetab(char **tab);
int		ft_print_tab(char **tab);
int		ft_which_redirection_take_on_board(char *s);
int		ft_omit_quote_apostrophe(char c, unsigned int omit, unsigned int *i, \
int keep_quotes);
int		ft_ycheck_pipe(char *temp);
int		ft_if_quotes_not_closes(t_data *data);
char	**ft_envcpy(char **env);
void	*ft_create_inputs(t_data *data);
int		ft_yerror(int nb, t_data *data);
int		ft_check_and_replace_var(char **str, char **env);
int		ft_replace_var(char **str, char **env, int *i, int *j);
int		ft_checkvar(char *str, char *var, int *k);
int		ft_strcpy_var(char **str, char *value, int length_name, int start);
int		ft_retrieve_string(int omit, t_data *data, char *temp, char *ptr);
int		ft_print_error(int rd);
int		ft_type_redirection(char **str);
int		ft_search_pattern(char *str, char *pattern);
int		ft_update_file(char *str, t_file **files, int total, int rd);
char	**ft_delete_rd(char **tab);
char	**ft_delete_filename_in_cmd(char **tab, int pos);
char	**ft_delete_files_name(char **tab, int pos, int rd);
int		ft_extract_line(char *ptr, char **str, char *temp, char *pattern);
int		ft_pre_parsing(t_data *data);
int		ft_init_term(t_data *data);
int		ft_fill_heredoc(char *pattern, t_data *data);
int		ft_convert_redi(t_data *data);
int		ft_check_cmd_waiting(t_data *data, int i);
int		ft_sub_retrieve_string(int omit, char *ptr);
void	ft_check_rd(int rd, t_input *input);
/* EXECUTION */
void	ft_exec_parse(t_data *data);
void	ft_pipe(t_data *data);
int		ft_check_cmds(t_data *data, int i);
void	ft_check_redir(t_data *data, int i);
int		ft_exec_builtin(t_data *data, int i);
int		ft_check_fds(t_data *data, int i);
char	*ft_check_access(t_data *data, int i);
void	ft_close_redir(t_data *data, int i);
void	ft_dup_heredoc(t_data *data, int i, int j, int fd_heredoc);
int		ft_heredoc(t_data *data, int i, int j, int *type);
int		ft_sub_if_quotes_not_closes(int old_error, int omit);
int		ft_sub_if_not_cmd_after_last_pipe(char *ptr, int old_error);
int		ft_check_num(char *str);
int		ft_checkchar(int keep_quotes, char a, char b);

char	*ft_color_prompt(t_data *data);

/* BUILTINS */
int		ft_is_builtin(t_data *data, int i);
int		ft_no_need_child(t_data *data, int i);

/* ENV */
void	ft_env(t_data *data, int i);
void	ft_export(t_data *data, int i);
void	ft_display_export(t_data *data, int *j);
void	ft_unset(t_data *data, int i);
char	*ft_env_split_name(char *str_value, char *str);
void	ft_export_error(t_data *data, int i);

void	ft_echo(t_data *data, int i);
void	ft_cd(t_data *data, int i);
void	ft_pwd(t_data *data, int i);
void	ft_exit(t_data *data, int i);

/* FREE */
void	ft_free_inputs(t_data *data);
void	ft_free_section(t_data *data, int i);
void	ft_free(t_data *data);
void	ft_free_tab(char **tab);
void	ft_free_content_tab(char **tab);
void	ft_free_error(t_data *data, int i);

#endif
