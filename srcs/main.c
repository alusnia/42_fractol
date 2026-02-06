/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:33:40 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/19 20:25:45 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	modify_n_iter(t_data *data, int keycode)
{
	char	*str;
	int		n;

	ft_printf("Recent number of calculations: %d\n", data->fractal->n_iter);
	if (keycode == 61)
	{
		ft_printf("By how many you want to increase this value?\n");
		str = get_next_line(0);
	}
	else
	{
		ft_printf("By how many you want to decrease this value?\n");
		str = get_next_line(0);
	}
	n = ft_atoi(str);
	free(str);
	if (keycode == 61 && (unsigned int)(data->fractal->n_iter + n) <= INT_MAX)
		data->fractal->n_iter += n;
	else if (keycode == 45 && data->fractal->n_iter - n >= 10)
		data->fractal->n_iter -= n;
	else
		ft_printf("Wrong value\n");
	ft_printf("Recent number of calculations: %d\n", data->fractal->n_iter);
	fill_image(data, data->fractal->f);
}

void	select_fractal(t_data *data)
{
	if (!data->fractal->type)
	{
		ft_printf("Enter which fractal set you want to display: \n");
		ft_printf("{\"Mandelbrot\", \"Julia\", \"Burning ship\"}\n");
		data->fractal->type = get_next_line(0);
	}
	if (!ft_strncmp("Mandelbrot", data->fractal->type, 10))
		get_mandelbrot_param(data);
	else if (!ft_strncmp("Julia", data->fractal->type, 5))
		get_julia_param(data);
	else if (!ft_strncmp("Burning ship", data->fractal->type, 12))
		get_bonus_param(data);
	else
	{
		free(data->fractal->type);
		data->fractal->type = NULL;
	}
}

int	main(void)
{
	t_data	*data;

	data = start_program();
	data->fractal->type = NULL;
	make_color_array(data);
	while (1)
	{
		select_fractal(data);
		ft_printf("Wrong argument, try again.\n");
	}
	return (0);
}
