/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:02:05 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/13 11:51:37 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	start_mandelbrot(t_data *data)
{
	new_window(data);
	data->fractal->frame = malloc(2 * sizeof(double));
	if (!data->fractal->frame)
		kill_program(data);
	data->fractal->frame[0] = -2.0f;
	data->fractal->frame[1] = -1.5f;
	data->fractal->f = man_alg;
	fill_image(data, data->fractal->f);
	mlx_loop(data->xvar);
}

void	get_mandelbrot_param(t_data *data)
{
	char	*temp;

	data->fractal->n_iter = 0;
	while (data->fractal->n_iter <= 0)
	{
		ft_printf("Enter number of calculations requiered for each pixel ");
		ft_printf("More = More detailed and slower\n");
		temp = get_next_line(0);
		data->fractal->n_iter = ft_atoi(temp);
		if (data->fractal->n_iter <= 0)
			ft_printf("Wrong value. Value should be > 0\n");
		free(temp);
	}
	start_mandelbrot(data);
}

void	calculate_esc(double c_real, double c_imag,
		double *z_real, double *z_imag)
{
	double	temp_real;

	temp_real = (*z_real * *z_real) - (*z_imag * *z_imag) + c_real;
	*z_imag = (2 * *z_real * *z_imag) + c_imag;
	*z_real = temp_real;
}

double	man_alg(t_data *data, int x, int y)
{
	double	c_real;
	double	c_imag;
	double	z_real;
	double	z_imag;
	int		n;

	n = 0;
	c_real = ((double)x / WIDTH) * data->frame_x_len + data->frame[0];
	c_real = (c_real / (WIDTH / 3)) - 2.0f;
	c_imag = ((double)y / HEIGHT) * data->frame_y_len + data->frame[1];
	c_imag = -1 * ((c_imag / (HEIGHT / 3)) - 1.5f);
	z_real = 0;
	z_imag = 0;
	while (n++ < data->fractal->n_iter && z_real + z_imag < 2)
		calculate_esc(c_real, c_imag, &z_real, &z_imag);
	if (n == data->fractal->n_iter)
		return (0);
	z_real = (log(log(z_imag + z_real))) / log(2);
	z_real = n + 1 - z_real;
	return (z_real);
}
