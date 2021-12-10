#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_line_que		line;
	struct termios	set_term;

	(void)argc;
	(void)argv;
	g_state.local_envp = arr_dup(env);
	set_terminal(&set_term);
	while (42)
	{
		signal_handler();
		exec_prompt(&line);
	}
}

void	exec_prompt(t_line_que *line)
{
	char	*buf;

	buf = readline("W.A.P.$HELL>> ");
	if (buf == 0)
		eof_exit();
	else if (ft_strlen(buf) > 0)
		add_history(buf);
	rl_redisplay();
	if (exception_handler(buf) == 0)
	{
		tokenizer_line(line, buf);
		if (exception_redir_with_no_path(line) == 0)
			process_execution(line, &g_state.local_envp);
		release_all_nodes(line);
	}
	free(buf);
}
