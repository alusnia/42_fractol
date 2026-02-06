/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:06:56 by alusnia           #+#    #+#             */
/*   Updated: 2026/02/06 15:48:40 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	start_julia(t_data *data)
{
	char	*temp;

	data->fractal->n_iter = 0;
	while (data->fractal->n_iter < 10)
	{
		ft_printf("Enter number of calculations requiered for each pixel ");
		ft_printf("More = More detailed and slower\n");
		temp = get_next_line(0);
		data->fractal->n_iter = ft_atoi(temp);
		if (data->fractal->n_iter < 10)
			ft_printf("Wrong value. Value should be >= 10\n");
		free(temp);
	}
	new_window(data);
	data->fractal->frame = malloc(2 * sizeof(double));
	if (!data->fractal->frame)
		kill_program(data);
	data->fractal->frame[0] = -1.5f;
	data->fractal->frame[1] = -1.5f;
	data->fractal->f = jul_alg;
	fill_image(data, data->fractal->f);
	mlx_loop(data->xvar);
}

void	get_julia_param(t_data *data)
{
	char	*input;
	double	temp;

	ft_printf("Enter value of \"c\" in this state \"x.x(...)x,y.y(...)y\"\n");
	ft_printf("Any no-digits entires will be considered as 0\n");
	ft_printf("Enter x first, x should be >= -2 and <= 1\n");
	input = get_next_line(0);
	temp = ft_atod(input);
	free(input);
	if (temp < -2 || temp > 1)
		return ;
	data->fractal->parameter_1 = temp;
	ft_printf("Now enter y, y should be >= -1.5 and <= 1.5\n");
	input = get_next_line(0);
	temp = ft_atod(input);
	free(input);
	if (temp < -1.5 || temp > 1.5)
		return ;
	data->fractal->parameter_2 = temp;
	start_julia(data);
}

double	jul_alg(t_data *data, int x, int y)
{
	double	c_real;
	double	c_imag;
	double	z_real;
	double	z_imag;
	int		n;

	n = 0;
	c_real = data->fractal->parameter_1;
	c_imag = data->fractal->parameter_2;
	z_real = ((double)x / WIDTH) * data->frame_x_len + data->frame[0];
	z_real = (z_real / (WIDTH / 3)) - 1.5f;
	z_imag = ((double)y / HEIGHT) * data->frame_y_len + data->frame[1];
	z_imag = -1 * ((z_imag / (HEIGHT / 3)) - 1.5f);
	while (n++ < data->fractal->n_iter && z_real + z_imag < 2)
		calculate_esc(c_real, c_imag, &z_real, &z_imag);
	if (n == data->fractal->n_iter)
		return (0);
	z_real = (log(log(z_imag + z_real))) / log(2);
	z_real = n + 1 - z_real;
	return (z_real);
}
