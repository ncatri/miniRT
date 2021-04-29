#include "libft.h"

int	initialize_buf_c(t_buf *b, char *c)
{
	b->tmp = malloc(BUF_LINE_LIM * sizeof(char));
	b->pos = 0;
	b->size = BUF_LINE_LIM;
	*c = 'a';
	return (1);
}

int	free_and_zero(t_file **f)
{
	free(*f);
	*f = 0;
	return (0);
}
