#include "libunit.h"

void	run_test(t_unit *unit)
{
	int32_t	return_value;

	if (check_flag(unit->parameters.flags, OUTPUT))
		return_value = unit->test.out();
	else
		return_value = unit->test.simple();
	sleep(1);
	exit(return_value);
}

int32_t	setup_test_env(t_unit *unit, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		fprintf(stdout, YEL"fork error, cannot run test\n"RESET);
		return (-1);
	}
	else if (pid == 0)
	{
		if (check_flag(unit->parameters.flags, OUTPUT))
		{
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		run_test(unit);
	}
	chrono_start();
	return (0);
}

void	run_suite(t_unit *unit)
{
	int32_t		pipe_fd[2];
	uint32_t	count;

	count = 0;
	while (unit != NULL)
	{
		if (check_flag(unit->parameters.flags, OUTPUT) && (pipe(pipe_fd) == -1))
			fprintf(stdout, YEL"pipe error, cannot run test\n"RESET);
		else
		{
			if (setup_test_env(unit, pipe_fd) == 0)
				print_result(unit, count);
			if (check_flag(unit->parameters.flags, OUTPUT))
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
		}
		unit = unit->next;
		count++;
	}
}

void	run_all(void)
{
	t_suite	**suite_list;
	t_suite	*current;

	suite_list = get_suite_list();
	current = *suite_list;
	while (current != NULL)
	{
		print_header(current->ft_name);
		run_suite(current->unit);
		current = current->next;
	}
}