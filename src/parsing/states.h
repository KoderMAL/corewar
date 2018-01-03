#ifndef STATES_H
# define STATES_H

/*
** states_main.c
*/

void		state_start(t_env *env, char c);
void		state_comment(t_env *env, char c);
void		state_command_label_instruction(t_env *env, char c);

/*
** states_header.c
*/

int			match_name(t_env *env);
int			match_comment(t_env *env);
void		state_pre_str(t_env *env, char c);
void		state_str(t_env *env, char c);
void		state_eol(t_env *env, char c);

/*
** states_label.c
*/

int			check_label(t_env *env);

/*
** states_instruction.c
*/

const t_op	*match_instruction(t_env *env);
void		state_pre_arg(t_env *env, char c);
void	state_arg(t_env *env, char c);
void	state_post_arg(t_env *env, char c);

/*
** save_label.c
*/

void		save_label(t_env *env);

/*
** save_argument.c
*/

void		save_argument(t_env *env);

/*
** save_instruction.c
*/

void		save_instruction(t_env *env);

#endif