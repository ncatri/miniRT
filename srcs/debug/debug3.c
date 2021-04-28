#include "miniRT.h"

void	print_matrix44d(double matrix[4][4])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		printf("| ");
		while (++j < 4)
			printf("%4.2f ", matrix[i][j]);
		printf("|\n");
	}
}

int	display_mouse_position_on_click(t_mlx mlx)
{
	mlx_mouse_hook(mlx.window_id, mouse_hook_display_position_and_button, &mlx);
	return (0);
}

int	mouse_hook_display_position_and_button(int button, int x, int y, t_mlx *mlx)
{
	printf("button: %d, x: %d, y: %d\n", button, x, y);
	(void)mlx;
	return (0);
}
