#include "includes/miniRT.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: 2 arguments needed.\n", 1);
		return (0);
	}
	char *line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_putstr_fd(line, 1);
		ft_putchar_fd('\n', 1);
		free(line);
	}
	ft_putstr_fd(line, 1);
}
