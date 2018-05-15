
uchar4 __OVERLOAD__ mix(uchar4 c1, uchar4 c2, float gradiant);
void					put_px(int2 px, uchar4 color, __global uchar4 *buf, int2 img_size);
uchar4					choose_color(float gradiant, int iter, int iter_max, float shift, char palette);
float2					c_mult(float2 z1, float2 z2);
float2					c_pow(float2 z, int pow);
uchar4					sky(float gradiant, float shift);
uchar4					neon(float gradiant, float shift);
uchar4					black_white(float gradiant, float shift);

__constant uchar4 color_sky[5] = {(uchar4)(0xFF, 0xFF, 0xFF, 0x00), (uchar4)(0xFF, 0x77, 0x22, 0x00),
				(uchar4)(0xAA, 0x33, 0x00, 0x00), (uchar4)(0x44, 0x22, 0x44, 0x00), (uchar4)(0x00, 0xAA, 0xFF, 0x00)};
__constant uchar4 color_neon[5] = {(uchar4)(0xFF, 0xFF, 0xFF, 0x00), (uchar4)(0xAA, 0xAA, 0xFF, 0x00),
				(uchar4)(0x33, 0xDD, 0x33, 0x00), (uchar4)(0xFF, 0x22, 0x44, 0x00), (uchar4)(0xFF, 0x00, 0xFF, 0x00)};

uchar4 __OVERLOAD__ mix(uchar4 c1, uchar4 c2, float gradiant)
{
	float4	tmp;
	float4	tmp1;
	float4	tmp2;

	tmp1 = (float4)(c1.x, c1.y, c1.z, c1.w);
	tmp2 = (float4)(c2.x, c2.y, c2.z, c2.w);
	tmp = mix(tmp1, tmp2, gradiant);
	return ((uchar4)(tmp.x, tmp.y, tmp.z, tmp.w));
}

float2					c_mult(float2 z1, float2 z2)
{
	return (z1.xx * z2.xy + z1.yy * z2.yx * (float2)(-1, 1));
}

float2					c_pow(float2 z, int pow)
{
	float2	ret;

	ret = z;
	while (--pow)
		ret = c_mult(ret, z);
	return (ret);
}

uchar4					sky(float gradiant, float shift)
{
	gradiant += shift * 5;
	return(mix(color_sky[(int)gradiant % 5], color_sky[((int)gradiant + 1) % 5], fmod(gradiant, 1)));
}

uchar4					neon(float gradiant, float shift)
{
	gradiant += shift * 5;
	return(mix(color_neon[(int)gradiant % 5], color_neon[((int)gradiant + 1) % 5], fmod(gradiant, 1)));
}

uchar4					black_white(float gradiant, float shift)
{
	return(mix((uchar4)(0xFF, 0xFF, 0xFF, 0x00), (uchar4)(0x11, 0x11, 0x11, 0x00), (sin(fabs(gradiant * 8 + shift * 4 * M_PI_F)) + 1) / 2));
}

uchar4					choose_color(float gradiant, int iter, int iter_max, float shift, char palette)
{
	if (iter < iter_max)
	{
		if (palette == 0)
			return (sky(gradiant, shift));
		else if (palette == 1)
			return (black_white(gradiant, shift));
		else
			return (neon(gradiant, shift));
	}
	else
		return ((uchar4)(0x00, 0x00, 0x00, 0x00));
}

__kernel void			draw_fract(
						   __global uchar4	*buf,
						   uint		pixel_sz,
						   uint		line,
						   int2		img_size,
						   int		iter_max,
						   float	zoom,
						   float2	pos,
						   float2	z1,
						   int		pow,
						   int		fract,
						   uchar	parm,
						   char		coloring,
						   float	color_rot,
						   char		palette
						  )
{
	int		id;
	int2	px_pos;
	float2	c;
	float2	z;
	int		iter;
	int		i;
	float	len;

	id = get_global_id(0);
	if ((ulong)id >= (ulong)(img_size.x * img_size.y))
		return ;
	px_pos = (int2)(id % img_size.x, id / img_size.x);
	c = (float2)((float)(px_pos.x - img_size.x / 2) * (float)4 / (float)min(img_size.x, img_size.y) / zoom + (float)pos.x,
				(float)(px_pos.y - img_size.y / 2) * (float)4 / (float)min(img_size.x, img_size.y) / zoom + (float)pos.y);
	z = z1;
	iter = 0;
	if (fract == 0)
	{
		while (length(z) <= 2 && ++iter < iter_max)
		{
			z = (float2)((parm & (0x1 << 0) ? fabs(z.x) : z.x) * (parm & (0x1 << 1) ? -1 : 1),
						(parm & (0x1 << 2) ? fabs(z.y) : z.y) * (parm & (0x1 << 3) ? -1 : 1));
			z = c_pow(z, pow);
			z = (float2)((parm & (0x1 << 4) ? fabs(z.x) : z.x) * (parm & (0x1 << 5) ? -1 : 1),
						(parm & (0x1 << 6) ? fabs(z.y) : z.y) * (parm & (0x1 << 7) ? -1 : 1));
			z += c;
		}
		if (coloring == 1 && (i = iter) < iter_max)
			while (length(z) < 1 << 10 && i < iter_max + 50)
			{
				z = (float2)((parm & (0x1 << 0) ? fabs(z.x) : z.x) * (parm & (0x1 << 1) ? -1 : 1),
							(parm & (0x1 << 2) ? fabs(z.y) : z.y) * (parm & (0x1 << 3) ? -1 : 1));
				z = c_pow(z, pow);
				z = (float2)((parm & (0x1 << 4) ? fabs(z.x) : z.x) * (parm & (0x1 << 5) ? -1 : 1),
							(parm & (0x1 << 6) ? fabs(z.y) : z.y) * (parm & (0x1 << 7) ? -1 : 1));
				z += c;
				i++;
			}
		len = length(z);
	}
	else
	{
		while (length(c) <= 2 && ++iter < iter_max)
		{
			c = (float2)((parm & (0x1 << 0) ? fabs(c.x) : c.x) * (parm & (0x1 << 1) ? -1 : 1),
						(parm & (0x1 << 2) ? fabs(c.y) : c.y) * (parm & (0x1 << 3) ? -1 : 1));
			c = c_pow(c, pow);
			c = (float2)((parm & (0x1 << 4) ? fabs(c.x) : c.x) * (parm & (0x1 << 5) ? -1 : 1),
						(parm & (0x1 << 6) ? fabs(c.y) : c.y) * (parm & (0x1 << 7) ? -1 : 1));
			c += z;
		}
		if (coloring == 1 && (i = iter) < iter_max)
			while (length(c) < 1 << 10 && i < iter_max + 50)
			{
				c = (float2)((parm & (0x1 << 0) ? fabs(c.x) : c.x) * (parm & (0x1 << 1) ? -1 : 1),
							(parm & (0x1 << 2) ? fabs(c.y) : c.y) * (parm & (0x1 << 3) ? -1 : 1));
				c = c_pow(c, pow);
				c = (float2)((parm & (0x1 << 4) ? fabs(c.x) : c.x) * (parm & (0x1 << 5) ? -1 : 1),
							(parm & (0x1 << 6) ? fabs(c.y) : c.y) * (parm & (0x1 << 7) ? -1 : 1));
				c += z;
				i++;
			}
		len = length(c);
	}
	if (coloring == 1)
		buf[id] = choose_color((i - log(log(len) / log((float)pow)) / log((float)pow)) / 7 + 10, iter, iter_max, color_rot, palette);
	else
		buf[id] = choose_color((float)iter / 7 + 10, iter, iter_max, color_rot, palette);
}

__kernel void	clear_buf(__global uchar4 *buf,
							uchar4 val)
{	int		id;

	id = get_global_id(0);
	buf[id] = (uchar4)(val.r, val.g, val.b, 0x00);
}
