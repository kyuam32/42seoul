/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:23:31 by namkyu            #+#    #+#             */
/*   Updated: 2021/05/05 17:15:52 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "../1.libft/libft.h"

# define NONE 0

typedef enum			e_instruction
{
	sa = 0,
	sb = 1,
	ss = 2,
	pa = 3,
	pb = 4,
	ra = 5,
	rb = 6,
	rr = 7,
	rra = 8,
	rrb = 9,
	rrr = 10
}						t_instruct;

typedef struct			s_element
{
	int					num;
	struct s_element	*up;
	struct s_element	*dw;
}						t_element;

typedef struct			s_stack
{
	t_element			*top;
	t_element			*bot;
	int					size;
}						t_stack;

typedef struct			s_optimizer
{
	t_stack				*inst;
	t_stack				*result;
	t_stack				*target;
}						t_optimizer;

typedef struct			s_system
{
	t_stack				a;
	t_stack				b;
	t_stack				answer;
	t_stack				*sorted;
	t_optimizer			*opt;
	int					*arr;
	int					err;
	int					n;
	int					chunk;
	int					sorted_n;
	int					optimal_cal;
}						t_system;

/*
**						stack utils ----------------------------------------
*/
t_stack					*copy_stack(t_system *sys, t_stack *ori);
int						stack_pop_del(t_stack *stack);
void					stack_join(t_stack *upper_del, t_stack *lower);
void					free_stack(t_stack *target);
int						stack_rev_element(t_stack *stk);
/*
**						stack control --------------------------------------
*/
int						stack_element(t_system *sys, t_stack *stk, int n);
int						stack_push_element(t_stack *from, t_stack *to);
int						stack_swap_element(t_stack *stk);
int						stack_rot_element(t_stack *stk);
/*
**						instruction stack ----------------------------------
*/
int						stack_instruction(t_stack *a, \
											t_stack *b, t_instruct inst);
int						stack_instruction_rev(t_stack *a, \
												t_stack *b, t_instruct inst);
void					stack_instruction_convert(int i);
void					stack_instruction_print(t_stack *stack);
int						is_forbid_pattern(t_stack *list);
/*
**						parse ----------------------------------------------
*/
int						argument_is_valid(t_system *sys, int ac, char **av);

int						argument_is_duple(t_system *sys, int num);
/*
**						optimize -------------------------------------------
*/
t_optimizer				*optimize_init(t_system *sys, t_stack *target);
void					optimize_inst_renew(t_system *sys, t_optimizer *curr);
void					free_optimizer(t_optimizer *target);
/*
**						divide & conquer -----------------------------------
*/
void					divide(t_system *sys);
void					conquer(t_system *sys);
/*
**						sort -----------------------------------------------
*/
void					sort_stack(t_system *sys, t_element *pivot);
void					merge_setup(t_system *sys);
void					bfs_search(t_system *sys, int moved, t_stack *target);
void					triplet(t_system *sys);

/*
**						utils ----------------------------------------------
*/
int						is_target(t_stack *target);
void					print_error(void);
void					make_answer(t_system *sys, t_instruct inst);

#endif
