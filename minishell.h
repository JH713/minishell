/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:01:25 by jihyeole          #+#    #+#             */
/*   Updated: 2023/06/18 12:28:49 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirect
{
	int					type;
	char				*fd;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char				**command;
	t_redirect			*input;
	t_redirect			*output;
	t_redirect			*redirect;
}	t_command;

typedef struct s_info
{
	int			process_num;
	int			heredoc_num;
	char		**heredocs;
	t_command	*commands;
	t_env		*env;
}	t_info;

typedef struct s_process
{
	int		n;
	pid_t	pid;
	int		fd[2];
}	t_process;

char		*read_command(void);
void		add_list(char *str, t_list **cmds);
int			is_not_sep(char c);
int			ft_strcmp(char	*s1, char *s2);
int			check_end(char *command, int i, char c);
int			check_prev(char *command, int i, t_list *cmds);
void		error_m(int c);
void		error_m1(char *str);
int			check_sep_input(char *sep, int i);
int			check_sep_output(char *sep, int i);
int			check_sep(char *sep);
int			join_sep_to_fd(char *command, int start, int i, t_list **cmds);
int			find_sep(char *command, int start, int i, t_list **cmds);
int			get_word(char *command, int i, t_list **cmds, int *flag);
int			handle_consecutive_redirection_error(char *command, int i);
int			get_operator(char *command, int i, t_list **cmds, int *flag);
t_list		*split_command(char *command, int i, int flag);
int			check_error(t_list *list);
int			pipe_num(t_list	*list);
void		add_last(t_redirect **rd, t_redirect *new);
int			check_if_pair(char	*content, char quotes);
t_redirect	*malloc_redirect(int type, char *fd, char *file);
int			check_type(char	*content);
void		check_input(t_info *info, t_list *list, char **fd, int *type);
void		put_input(t_info *info, t_list *list, \
					t_command *command, char *file);
void		put_output(t_info *info, char *content, \
					t_command *command, char *file);
void		init_command(t_command *command, int num);
void		join_env_2(char **line, char *env_value, int start, int end);
int			check_prev_quotes(char *line, int i);
void		handle_variable_expansion(char **line, int flag, int *i, int *j);
void		handle_exit_status_variable(char **line, int *i, char **env_value);
int			get_environment_variable_value(char *line, \
					t_env *env_lst, char **env_value, int j);
int			expand_env_inner(char **line, t_env *env_lst, int *i, int flag);
void		check_quotes_env(char **line, t_env *env_lst, int *i);
void		expand_env_2(char **line, t_env *env_lst);
void		check_quotes_in_cmd(char *content, char **temp, int *i, int *j);
char		*check_cmd(char	*content);
void		count_if_quotes(char **temp, int *i);
int			count_words(char *temp, int i);
int			count_word_with_expand(char *content, t_env *env_lst);
int			check_word_num(t_list *list, t_env *env_lst);
size_t		get_word_len(char *str, size_t len, size_t temp);
char		**split_word(char *str, int num);
void		expand_and_fill_command(t_command *command, \
							char *content, t_env *env_lst, int *j);
t_list		*handle_input_redirection(t_info *info, t_list *list, \
							t_env *env_lst, t_command *command);
t_list		*handle_output_redirection(t_info *info, t_list *list, \
							t_env *env_lst, t_command *command);
t_list		*check_and_init(t_list *list, t_command *command, t_env *env_lst);
t_list		*put_command(t_info *info, t_command *command, \
							t_list *list, t_env *env_lst);
void		free_info(t_info *info);
void		free_command(char **command);
void		free_redirect(t_redirect *rd);
void		free_heredocs(t_info *info);
int			check_num(char *num);
t_env		*init(int argc, char *argv[], char **env, char **command);
void		get_env_lst(t_env **env_lst, char **env);
int			get_first_idx(char *str, char c);
char		**get_path(t_env *env_lst);
void		env_lst_add_back(t_env **lst, t_env *new);
t_env		*env_lst_new(char *env);
void		print_env(char **env);
void		minishell_error_not_exit(char *cmd, char *err_msg, int exit_num);
void		minishell_error(char *command, char *err_msg, int exit_num);
void		minishell_arg_error(char *cmd, char *arg, char *msg, int exit_num);
void		minishell_perror(char *msg, int exit_num);
void		print_error(char *msg, int status);
int			unlink_heredocs(t_info *comm_info);
int			create_heredoc_temp(t_info *info);
void		join_env(char **line, char *env_value, int start, int end);
void		expand_env(char **line, t_env *env_lst);
void		redirect_process(t_process *proc, t_info *info, int i);
int			fd_check(char *fd);
int			env_lst_size(t_env *lst);
char		*get_env_str(t_env *env_lst);
char		**env_lst_to_arr(t_env *env_lst);
void		env_lstdelone(t_env *lst);
t_env		*get_lst_by_key(t_env *env_lst, char *key);
int			env_lst_unset(t_env **env_lst, char **str);
int			create_pipe(t_process *process, t_info *info);
void		close_unused_pipes(int i, int process_num, t_process *process);
int			unlink_heredocs(t_info *comm_info);
void		wait_all_child(t_info *info, t_process *process);
int			fd_check(char *fd);
char		*execute_check(char *command, char **path);
void		execute_command(t_process *proc, int i, t_info *info, t_env **lst);
void		fork_and_execute(t_process *proc, t_info *info, t_env **env_lst);
int			exec_single_builtin(t_info *info, t_env **env_lst);
int			builtin_func(t_info *info, char **command, t_env **env_lst);
int			check_env_name(char *str);
void		minishell_argstr_error(char *cmd, char *arg, char *msg, int num);
void		sigint_handler(int sig);
void		init_in_while(char *command);
void		hd_sigint_handler(int sig);
char		*get_temp_name(void);
int			check_builtin(char **command);
int			fd_check_in_single_bulletin(char *fd);
void		cleanup_memory(t_info *info, t_process *process);
int			check_single_builtin(t_info *info);
void		process_single_builtin(t_info *info);
void		init_redirect_fd(int *redirect_fd);
int			put_redirect_fd(t_redirect *re, int *redirect_fd, t_info *info);
void		duplicate_fd(int *redirect_fd, int *dup_fd);
void		restore_original_fd(int *redirect_fd, int *dup_fd);
char		*check_cmd2(char *content, t_env *env_lst);
int			builtin_echo(char **command, char **env);
void		free_env_arr(char **env);
int			check_env_name(char *str);
int			builtin_export(char **command, t_env **env_lst, char **env);
void		free_sorted_lst(t_env *sorted_lst);
void		print_export_env(t_env *sorted_lst);
t_env		*get_sorted_lst(t_env *env_lst);
int			jh_strcmp(char	*s1, char *s2);
int			builtin_cd(char **command, t_env **env_lst, char **env);
void		print_error_not_exit(char *msg, int status);
long long	ft_atol(const char *str);
t_list		*handle_output_redirection2(t_info *info, t_list *list, \
			t_env *env_lst, t_command *command);
void		builtin_exit(t_info *info, char **command);
void		exit_with_minus(char **command, unsigned char *exit_num);
void		exit_with_plus(char **command, unsigned char *exit_num);
void		exit_without_sign(char **command, unsigned char *exit_num);
int			minishell_perror_not_exit(char *msg, int exit_num);
void		set_shlvl(t_env **env_lst);
void		set_oldpwd(t_env **env_lst);
void		save_file_name(t_redirect *input, t_redirect *redirect, \
			char *tempfile);
int			redirect_process2(t_process *proc, t_info *info, int i);
char		*check_cmd3(char *content, t_env *env_lst);
void		print_maenggu1(void);
void		print_maenggu2(void);

#endif