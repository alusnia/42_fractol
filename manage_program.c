/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 08:37:09 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/14 06:45:30 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	kill_program(t_data *data)
{
	if (data && data->image)
		mlx_destroy_image(data->xvar, data->image);
	if (data && data->xvar && data->xvar->win_list)
		mlx_destroy_window(data->xvar, data->xvar->win_list);
	if (data && data->xvar)
	{
		mlx_destroy_display(data->xvar);
		free(data->xvar);
	}
	if (data && data->frame)
		free(data->frame);
	if (data && data->fractal && data->fractal->type)
		free(data->fractal->type);
	if (data && data->fractal && data->fractal->frame)
		free(data->fractal->frame);
	if (data && data->fractal)
		free(data->fractal);
	if (data && data->colors)
		free(data->colors);
	if (data)
		free(data);
	exit(0);
}

int	manage_mpress(int mpress, int x, int y, t_data *data)
{
	if (mpress == 4 || mpress == 5)
	{
		if (data->psycho_color != 0 && data->psycho_color != 16)
			data->psycho_color++;
		else if (data->psycho_color != 0)
			data->psycho_color = 1;
		return (zoom_image(mpress, x, y, data));
	}
	else if (mpress == 1)
		return (export_coordinates(mpress, x, y, data));
	return (0);
}

int	manage_kpress(int keycode, t_data *data)
{
	if (keycode >= 65361 && keycode <= 65364)
	{
		if (data->psycho_color != 0 && data->psycho_color != 16)
			data->psycho_color++;
		else if (data->psycho_color != 0)
			data->psycho_color = 1;
		move_image(data, keycode);
	}
	else if (keycode == 45 || keycode == 61)
		modify_n_iter(data, keycode);
	else if (keycode == 65307)
	{
		kill_program(data);
	}
	else if (keycode == 103)
	{
		switch_psycho(data);
	}
	return (0);
}

t_data	*start_program(void)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	if (!data)
		kill_program(data);
	data->frame = malloc(2 * sizeof(double));
	data->scale = 1;
	data->frame_x_len = (double)WIDTH;
	data->frame_y_len = (double)HEIGHT;
	data->old_x_len = (double)WIDTH;
	data->old_y_len = (double)HEIGHT;
	data->xvar = mlx_init();
	data->image = mlx_new_image(data->xvar, WIDTH, HEIGHT);
	data->fractal = malloc(sizeof(t_fractal));
	if (!data->frame || !data->xvar || !data->image || !data->fractal)
		kill_program(data);
	if (!mlx_get_data_addr(data->image, &data->image->bpp,
			&data->image->size_line, &data->endian))
		kill_program(data);
	data->frame[0] = 0;
	data->frame[1] = 0;
	data->psycho_color = 0;
	return (data);
}

t_win_list	*new_window(t_data *data)
{
	char	*title;

	title = ft_strjoin("Fract-ol: ", data->fractal->type);
	title[ft_strlen(title) - 1] = '\0';
	data->xvar->win_list = mlx_new_window(data->xvar, WIDTH, HEIGHT, title);
	free(title);
	if (!data->xvar->win_list)
		kill_program(data);
	mlx_hook(data->xvar->win_list, DestroyNotify, StructureNotifyMask,
		kill_program, data);
	mlx_hook(data->xvar->win_list, KeyPress, KeyPressMask, manage_kpress, data);
	mlx_hook(data->xvar->win_list, 4, ButtonPress, manage_mpress, data);
	return (0);
}
