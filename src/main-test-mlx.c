/* ************************************************************************** */
/*   cyanotype.c — lava lamp cyanotype, cross-platform Mac/Linux             */
/*                                                                            */
/*   Mac:                                                                     */
/*   cc cyanotype.c minilibx_opengl_20191021-1/libmlx.a                      */
/*      -I minilibx_opengl_20191021-1                                         */
/*      -framework OpenGL -framework AppKit -lm -o cyanotype                 */
/*                                                                            */
/*   Linux:                                                                   */
/*   cc cyanotype.c minilibx-linux/libmlx.a                                  */
/*      -I minilibx-linux -lX11 -lXext -lm -o cyanotype                      */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

# ifdef __linux__
#  include "../minilibx-linux/mlx.h"
#  define KEY_ESC    65307
#  define EVT_CLOSE  17
#  define EVT_RESIZE 26
# else
#  include "../mlx/mlx.h"
#  define KEY_ESC    53
#  define EVT_CLOSE  17
#  define EVT_RESIZE 15
# endif

# define W       800
# define H       800
# define NBALLS  6

typedef struct s_ball
{
	double	x;
	double	y;
	double	r;
	double	phase_x;
	double	phase_y;
	double	freq_x;
	double	freq_y;
}	t_ball;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	double	t;
	t_ball	balls[NBALLS];
}	t_app;

// ── color palette ─────────────────────────────────────────────────────────────

static int	lerp_rgb(double t, int a, int b)
{
	int	r;
	int	g;
	int	bl;

	r  = ((a >> 16) & 0xFF)
		+ (int)((((b >> 16) & 0xFF) - ((a >> 16) & 0xFF)) * t);
	g  = ((a >>  8) & 0xFF)
		+ (int)((((b >>  8) & 0xFF) - ((a >>  8) & 0xFF)) * t);
	bl = ( a        & 0xFF)
		+ (int)(((  b       & 0xFF) - ( a        & 0xFF)) * t);
	return ((r << 16) | (g << 8) | bl);
}

static int	cyano_color(double v)
{
	static int	stops[6] = {
		0x060D1F,
		0x0A2A6E,
		0x1A4FA0,
		0x4A90C4,
		0x9DC8E8,
		0xE8F4FB,
	};
	double	seg;
	int		idx;
	double	lt;

	v = v < 0.0 ? 0.0 : (v > 1.0 ? 1.0 : v);
	seg = v * 5.0;
	idx = (int)seg;
	if (idx >= 5)
		return (stops[5]);
	lt = seg - idx;
	lt = lt * lt * (3.0 - 2.0 * lt);
	lt = lt * lt * (3.0 - 2.0 * lt);
	return (lerp_rgb(lt, stops[idx], stops[idx + 1]));
}

// ── metaball field ────────────────────────────────────────────────────────────

static double	field(t_app *a, double x, double y)
{
	double	sum;
	double	dx;
	double	dy;
	double	dist2;
	int		i;

	sum = 0.0;
	i = 0;
	while (i < NBALLS)
	{
		dx = x - a->balls[i].x;
		dy = y - a->balls[i].y;
		dist2 = dx * dx + dy * dy;
		if (dist2 < 1.0)
			dist2 = 1.0;
		sum += (a->balls[i].r * a->balls[i].r) / dist2;
		i++;
	}
	return (sum);
}

// ── grain ─────────────────────────────────────────────────────────────────────

static double	grain(int x, int y, double t)
{
	double	n;

	n = sin((double)x * 127.1 + (double)y * 311.7 + t * 0.1) * 43758.5453;
	n = n - (int)n;
	return (n * 0.03);
}

// ── update balls ─────────────────────────────────────────────────────────────

static void	update_balls(t_app *a)
{
	int	i;

	i = 0;
	while (i < NBALLS)
	{
		a->balls[i].x = W / 2.0
			+ sin(a->t * a->balls[i].freq_x + a->balls[i].phase_x)
			* W * 0.38;
		a->balls[i].y = H / 2.0
			+ cos(a->t * a->balls[i].freq_y + a->balls[i].phase_y)
			* H * 0.38;
		i++;
	}
}

// ── render ───────────────────────────────────────────────────────────────────

static void	render(t_app *a)
{
	int		x;
	int		y;
	double	v;
	double	mapped;
	char	*dst;

	update_balls(a);
	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			v = field(a, (double)x, (double)y);
			mapped = v / (v + 1.0);
			mapped = mapped * mapped * (3.0 - 2.0 * mapped);
			mapped += grain(x, y, a->t);
			if (mapped < 0.0) mapped = 0.0;
			if (mapped > 1.0) mapped = 1.0;
			dst = a->addr + (y * a->ll + x * (a->bpp / 8));
			*(unsigned int *)dst = cyano_color(mapped);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
}

// ── hooks ─────────────────────────────────────────────────────────────────────

static int	on_resize(void *p)
{
	t_app	*a;

	a = (t_app *)p;
	mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
	return (0);
}

static int	update(void *p)
{
	t_app	*a;

	a = (t_app *)p;
	a->t += 0.010;
	render(a);
	return (0);
}

static int	on_close(void *p)
{
	(void)p;
	exit(0);
}

static int	on_key(int k, void *p)
{
	(void)p;
	if (k == KEY_ESC)
		exit(0);
	return (0);
}

// ── init balls ───────────────────────────────────────────────────────────────

static void	init_balls(t_app *a)
{
	double	p[NBALLS][5] = {
		{0.0, 0.0, 0.29, 0.37, 110.0},
		{1.3, 2.4, 0.47, 0.23,  90.0},
		{3.7, 1.1, 0.61, 0.53,  95.0},
		{5.2, 3.9, 0.19, 0.67,  80.0},
		{2.1, 4.6, 0.53, 0.41,  85.0},
		{4.4, 0.7, 0.37, 0.29,  75.0},
	};
	int	i;

	i = 0;
	while (i < NBALLS)
	{
		a->balls[i].phase_x = p[i][0];
		a->balls[i].phase_y = p[i][1];
		a->balls[i].freq_x  = p[i][2];
		a->balls[i].freq_y  = p[i][3];
		a->balls[i].r       = p[i][4];
		a->balls[i].x       = W / 2.0;
		a->balls[i].y       = H / 2.0;
		i++;
	}
}

// ── main ─────────────────────────────────────────────────────────────────────

int	main(void)
{
	t_app	a;

	a.t = 0.0;
	init_balls(&a);
	a.mlx = mlx_init();
	if (!a.mlx)
		return (1);
	a.win = mlx_new_window(a.mlx, W, H, "cyanotype — ESC");
	if (!a.win)
		return (1);
	a.img = mlx_new_image(a.mlx, W, H);
	if (!a.img)
		return (1);
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.ll, &a.endian);
	mlx_hook(a.win, EVT_CLOSE, 0, on_close, NULL);
	mlx_hook(a.win, EVT_RESIZE, 0, on_resize, &a);
	mlx_key_hook(a.win, on_key, &a);
	mlx_loop_hook(a.mlx, update, &a);
	mlx_loop(a.mlx);
	return (0);
}