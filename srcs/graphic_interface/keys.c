/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 08:38:01 by ncatrien          #+#    #+#             */
/*   Updated: 2021/02/19 10:49:10 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int		keys_find_id(int key, void *param)
{
	ft_putnbr_fd(key, 1);
	ft_putchar_fd('\n', 1);
	(void)param;
	return (0);
}

void	mode_display_keysid(t_mlx mlx)
{
	mlx_key_hook(mlx.window_id, keys_find_id, (void*)0);
}

void	mode_quit_on_esc(t_mlx mlx)
{
	mlx_key_hook(mlx.window_id, quit_on_esc, &mlx);
}

int		quit_on_esc(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		mlx_destroy_window(mlx->connection_graphic_server, mlx->window_id);
		exit(0);
	}
	return (0);
}

int		close_window(int key, t_mlx *mlx)
{
	mlx_destroy_window(mlx->connection_graphic_server, mlx->window_id);
	exit(0);
	(void)key;
	return (0);
}
