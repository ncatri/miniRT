/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 08:06:58 by ncatrien          #+#    #+#             */
/*   Updated: 2021/02/19 08:35:03 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	*connection_server(t_mlx *mlx)
{
	void	*connection;

	connection = mlx_init();
	if (connection)
		mlx->checks = NO_ERROR;
	else
		mlx->checks = ERROR;
	return (connection);
}

void	*connect_window(t_mlx *mlx, t_window window)
{
	void	*window_id;
	void	*connection_id;
	int		x;
	int		y;

	connection_id = mlx->connection_graphic_server;
	x = window.width;
	y = window.height;
	window_id = mlx_new_window(connection_id, x, y, window.title);
	if (window_id)
		mlx->checks = NO_ERROR;
	else
		mlx->checks = ERROR;
	return (window_id);
}

t_mlx	initialize_mlx(t_window window)
{
	t_mlx mlx;

	mlx.connection_graphic_server = connection_server(&mlx);
	mlx.window_id = connect_window(&mlx, window);
	return (mlx);
}

t_window	define_window(int width, int height, char *title)
{
	t_window window;

	window.width = width;
	window.height = height;
	window.title = ft_strdup(title);
	return (window);
}

void	open_mode(t_window window)
{
	t_mlx		mlx;

	mlx = initialize_mlx(window);
	if (mlx.checks)
	{
		mlx_key_hook(mlx.window_id, quit_on_esc, (void*)&mlx);
		mlx_loop(mlx.connection_graphic_server);
	}
	else
		ft_putstr_fd("Error while opening window\n", 1);
}
