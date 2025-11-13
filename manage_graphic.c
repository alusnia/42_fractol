/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_graphic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:34:26 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/13 11:51:39 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel_ptr;

	pixel_ptr = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)pixel_ptr = color;
}

int	assign_color(t_data *data, int value)
{
	int	first_col;
	int	second_col;

	if (value < 1)
		return (0x00000000);
	first_col = ((value + data->psycho_color) % 49) / 7;
	first_col = data->colors[first_col];
	second_col = ((value + data->psycho_color + 1) % 49) / 7;
	second_col = data->colors[second_col];
	value %= data->fractal->n_iter / 4;
	value = ((first_col + value * second_col / 100) / 2);
	return (value);
}

int	assign_background(int value)
{
	int	color_1;
	int	color_2;

	color_1 = 0x0000008D;
	color_2 = 0x008585FF;
	color_1 += ((color_2 * (value - 1) * 6) / 100) - color_1;
	return (color_1);
}

void	make_color_array(t_data *data)
{
	data->colors = malloc(7 * sizeof(int));
	if (!data->colors)
		kill_program(data);
	data->colors[0] = 0x00FFFFFF;
	data->colors[1] = 0x000000FF;
	data->colors[2] = 0x00000FF0;
	data->colors[3] = 0x0000FF00;
	data->colors[4] = 0x000FF000;
	data->colors[5] = 0x00FF0000;
	data->colors[6] = 0x00F00000;
}

void	switch_psycho(t_data *data)
{
	if (data->psycho_color > 0)
	{
		data->psycho_color = 0;
		ft_printf("Psycho colors stat - inactive\n");
	}
	else
	{
		data->psycho_color = 1;
		ft_printf("Psycho colors stat - active\n");
	}
}
