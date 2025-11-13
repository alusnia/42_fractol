/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:22:25 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/13 11:51:38 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	export_coordinates(int mpress, int x, int y, t_data *data)
{
	double	a;
	double	b;

	if (ft_strncmp(data->fractal->type, "Mandelbrot", 10) == 0)
	{
		a = ((double)x / WIDTH) * data->frame_x_len + data->frame[0];
		a = (a / (WIDTH / 3)) - 2.0f;
		b = ((double)y / HEIGHT) * data->frame_y_len + data->frame[1];
		b = -1 * ((b / (HEIGHT / 3)) - 1.5f);
		if (mpress == 1)
		{
			ft_printf("Selected point coordinates are:\n");
			ft_printf("X = %lf\nY = %lf\n", a, b);
		}
	}
	return (0);
}

int	zoom_image(int zoom_value, int x, int y, t_data *data)
{
	if (zoom_value == 4 && data->scale <= __FLT_MAX__
		&& data->frame_x_len / 1.1 != 0)
	{
		data->scale *= 1.1;
		data->frame_x_len /= 1.1;
		data->frame_y_len /= 1.1;
		change_frame(x, y, data);
	}
	else if (zoom_value == 5 && data->scale > 1)
	{
		data->scale /= 1.1;
		data->frame_x_len *= 1.1;
		data->frame_y_len *= 1.1;
		change_frame(x, y, data);
	}
	fill_image(data, data->fractal->f);
	return (0);
}

void	move_image(t_data *data, int event)
{
	if (event == 65361
		&& data->frame[0] - (10.0 / data->scale) >= -30.0f)
		data->frame[0] -= 10.0 / data->scale;
	else if (event == 65364 && data->frame[1]
		+ data->frame_y_len + (10.0 / data->scale) <= (double)(HEIGHT + 30))
		data->frame[1] += 10.0 / data->scale;
	else if (event == 65363 && data->frame[0]
		+ data->frame_x_len + (10.0 / data->scale) <= (double)(WIDTH + 30))
		data->frame[0] += 10.0 / data->scale;
	else if (event == 65362
		&& data->frame[1] - (10.0 / data->scale) >= -30.0f)
		data->frame[1] -= 10.0 / data->scale;
	fill_image(data, data->fractal->f);
}

void	change_frame(int x, int y, t_data *data)
{
	double	diff;
	double	power;

	diff = data->old_x_len - data->frame_x_len;
	power = (double)x / (double)WIDTH;
	data->frame[0] += diff * power;
	diff = data->old_y_len - data->frame_y_len;
	power = (double)y / (double)HEIGHT;
	data->frame[1] += diff * power;
	data->old_x_len = data->frame_x_len;
	data->old_y_len = data->frame_y_len;
	fill_image(data, data->fractal->f);
}

void	fill_image(t_data *data, double (*f)(t_data *, int, int))
{
	int		x;
	int		y;
	int		color;
	double	value;

	x = 0;
	y = 0;
	while (y < data->image->height)
	{
		while (x < data->image->width)
		{
			value = f(data, x, y);
			if (value < 15)
				color = assign_background((int)value);
			else
				color = assign_color(data, (int)value);
			ft_mlx_pixel_put(data->image, x, y, color);
			x++;
		}
		y++;
		x = 0;
	}
	mlx_put_image_to_window(data->xvar, data->xvar->win_list,
		data->image, 0, 0);
}
