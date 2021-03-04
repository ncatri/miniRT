/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 08:37:13 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/04 07:44:40 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int		display_mouse_position_on_click(t_mlx mlx)
{
	mlx_mouse_hook(mlx.window_id, mouse_hook_display_position_and_button, &mlx);
	return (0);
}

int		mouse_hook_display_position_and_button(int button, int x, int y, t_mlx *mlx)
{
	printf("button: %d, x: %d, y: %d\n", button, x, y);
	(void)mlx;
	return (0);
}

int		mouse_hook_display_angle(t_mlx mlx)
{
	t_coordinates	p;

	p.x = 0;
	p.y = 0;
	mlx_mouse_hook(mlx.window_id, mouse_angle, &p);
	return (0);
}

int		mouse_angle(int button, int x, int y, t_coordinates *p)
{
	double	angle;

	if (button == 1)
	{
		angle = M_PI;
		printf("angle: %.6f\n", angle);
	}
	angle = x * y;
	p->x = x;
	p->y = y;
	return (0);
}

int		mode_quit_on_click_red_cross(t_mlx mlx)
{
	mlx_hook(mlx.window_id, 17, 0, close_red_cross, &mlx);
	return (0);
}

int		close_red_cross(int key, t_mlx *mlx)
{
	(void)key;
	(void)mlx;
	exit(0);
	return (0);
}
