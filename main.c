/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:33:40 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/13 11:51:39 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
