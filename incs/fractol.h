/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:39:07 by alusnia           #+#    #+#             */
/*   Updated: 2026/02/06 15:04:34 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 600
# define HEIGHT 600
# include "libftplus.h"
# include "mlx_int.h"
# include "mlx.h"
# include <math.h>

//Structs-----------------------------------------------------------------------

typedef struct s_fractal
{
	char	*type;
	int		n_iter;
	double	(*f)();
	double	*frame;
	double	parameter_1;
	double	parameter_2;
}	t_fractal;

typedef struct s_data
{
	double			*frame;
	float			scale;
	double			frame_x_len;
	double			frame_y_len;
	double			old_x_len;
	double			old_y_len;
	char			psycho_color;
	int				endian;
	int				*colors;
	t_img			*image;
	t_xvar			*xvar;
	t_fractal		*fractal;
}	t_data;

//main--------------------------------------------------------------------------
void		modify_n_iter(t_data *data, int keycode);
void		select_fractal(t_data *data);
//manage_program----------------------------------------------------------------
int			kill_program(t_data *data);
int			manage_mpress(int mpress, int x, int y, t_data *data);
int			manage_kpress(int keycode, t_data *data);
t_data		*start_program(void);
t_win_list	*new_window(t_data *data);
//manage_graphic----------------------------------------------------------------
void		make_color_array(t_data *data);
void		ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void		switch_psycho(t_data *data);
int			assign_background(int value);
int			assign_color(t_data *data, int value);
//image-------------------------------------------------------------------------
int			export_coordinates(int mpress, int x, int y, t_data *data);
int			zoom_image(int zoom_value, int x, int y, t_data *data);
void		move_image(t_data *data, int event);
void		change_frame(int x, int y, t_data *data);
void		fill_image(t_data *data, double (*f)(t_data*, int, int));
//mandelbrot--------------------------------------------------------------------
void		start_mandelbrot(t_data *data);
void		get_mandelbrot_param(t_data *data);
void		calculate_esc(double c_real, double c_imag,
				double *z_real, double *z_imag);
double		man_alg(t_data *data, int x, int y);
//julia-------------------------------------------------------------------------
void		start_julia(t_data *data);
void		get_julia_param(t_data *data);
double		jul_alg(t_data *data, int x, int y);
//bonus
void		start_bonus(t_data *data);
void		get_bonus_param(t_data *data);
void		calculate_esc_bonus(double c_real, double c_imag,
				double *z_real, double *z_imag);
double		bon_alg(t_data *data, int x, int y);
#endif