/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 08:07:56 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 10:41:32 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	mult_color(t_color color, t_coordinates mult)
{
	t_color	result;
	int		red;
	int		green;
	int		blue;

	red = fmin(color.r * mult.x, 255);
	green = fmin(color.g * mult.y, 255);
	blue = fmin(color.b * mult.z, 255);
	result = set_color(red, green, blue);
	return (result);
}

t_color	add_colors(t_color color1, t_color color2)
{
	t_color	res;

	res.r = fmin(color1.r + color2.r, 255);
	res.g = fmin(color1.g + color2.g, 255);
	res.b = fmin(color1.b + color2.b, 255);
	res = set_color(res.r, res.g, res.b);
	return (res);
}

t_color	set_color(int r, int g, int b)
{
	t_color	color;

	color.t = 0;
	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;
	color.value = create_trgb(color);
	return (color);
}

int	create_trgb(t_color color)
{
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}
