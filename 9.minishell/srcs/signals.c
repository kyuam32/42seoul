#include "minishell.h"

void	set_terminal(struct termios *set_term)
{
	tcgetattr(0, set_term);
	set_term->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, set_term);
}

void	signal_handler(void)
{
	signal(SIGINT, (void *)signal_interrupt);
	signal(SIGQUIT, (void *)signal_quit);
}

void	eof_exit(void)
{
	printf("\033[%dA", 1);
	printf("\033[%dC", 14);
	printf("exit\n");
	exit(0);
}

void	signal_interrupt(int signo)
{
	if (g_state.is_child == FALSE)
	{
		if (g_state.process_flag == TRUE)
		{
			ft_putstr_fd("\n", STD_ERR);
			rl_replace_line("", 0);
		}
		else
		{
			ft_putstr_fd("\n", STD_ERR);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_state.signal_flag = signo;
	}
	else
		exit(signo);
}

void	signal_quit(int signo)
{
	if (g_state.is_child == FALSE)
	{
		g_state.signal_flag = signo;
		if (ft_strlen(rl_line_buffer) > 0)
		{
			rl_replace_line("", 0);
			if (is_there_child(&g_state.order_que) == \
						FALSE && g_state.process_flag == FALSE)
			{
				ft_putstr_fd("\n", STD_ERR);
				exit(signo);
			}
			else
				ft_putstr_fd("Quit: 3\n", STD_ERR);
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
			rl_replace_line("", 0);
		}
	}
	else
		exit(signo);
}
