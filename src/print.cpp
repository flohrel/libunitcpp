#include "libunit.h"

void	print_signal(int32_t status)
{
	fprintf(stdout, RED);
	if (WTERMSIG(status) == SIGALRM)
		fprintf(stdout, "%20s", "Timeout");
	else if (WTERMSIG(status) == SIGSEGV)
		fprintf(stdout, "%20s", "Segfault");
	else if (WTERMSIG(status) == SIGBUS)
		fprintf(stdout, "%20s", "Bus error");
	else if (WTERMSIG(status) == SIGABRT)
		fprintf(stdout, "%20s", "Abort");
	else if (WTERMSIG(status) == SIGFPE)
		fprintf(stdout, "%20s", "Floating-point exception");
	else if (WTERMSIG(status) == SIGPIPE)
		fprintf(stdout, "%20s", "Broken pipe");
	else if (WTERMSIG(status) == SIGILL)
		fprintf(stdout, "%20s", "Illegal instruction");
}

void	print_result(t_unit *unit, int32_t count)
{
	int32_t	status;

	wait(&status);
	chrono_end();
	fprintf(stdout, "%02d) %-20s", count, unit->name);
	if (WIFEXITED(status) == true)
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
		{
			fprintf(stdout, GRN"%20s", "[OK]");
			if (check_flag(unit->parameters.flags, CHRONO))
				fprintf(stdout, RESET" in %.3fms", get_execution_time());
		}
		else
			fprintf(stdout, RED"%20s", "[KO]");
	}
	else if (WIFSIGNALED(status))
		print_signal(status);
	else
		fprintf(stdout, RED"%-20s", "Unknown error");
	fprintf(stdout, RESET"\n");
}

void	print_header(const char *str)
{
	uint32_t	i;
	size_t		len;

	i = 0;
	len = ft_strlen(str) + 20;
	fprintf(stdout, MAG"\t");
	while (i++ < len)
		fprintf(stdout, "#");
	fprintf(stdout, "\n");
	fprintf(stdout, "\t#####     "CYN"%s"MAG"     #####\n\t", str);
	while (--i)
		fprintf(stdout, "#");
	fprintf(stdout, "\n");
	fprintf(stdout, RESET);
}