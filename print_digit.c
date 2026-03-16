/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:24:11 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:05:59 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbrlen(unsigned int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		++i;
	}
	return (i);
}

char	*ft_itoa_printf(unsigned int n, int *out_nbr_len)
{
	char	*str;
	int		len;

	if (!n)
	{
		*out_nbr_len = 1;
		return (ft_strdup("0"));
	}
	len = ft_nbrlen(n);
	*out_nbr_len = len;
	str = malloc(sizeof(*str) * (len + 1));
	str[len] = '\0';
	while (len-- && n != 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

static char	resolve_digit_sign(t_format *f, int is_negative)
{
	if (is_negative)
		return ('-');
	if (f->plus)
		return ('+');
	if (f->space)
		return (' ');
	return ('\0');
}

// Enough for -2147483648\0
int	print_digit(t_format *f, int arg)
{
	char	*result;
	char	sign;
	int		count;
	int		len;
	int		is_negative;
	int		precision_zeros;
	int		total_len;
	long	nbr;

	count = 0;
	is_negative = 0;
	precision_zeros = 0;
	nbr = (long)arg;
	if (nbr < 0)
	{
		is_negative = 1;
		nbr = -nbr;
	}
	result = ft_itoa_printf((unsigned int)nbr, &len);
	sign = resolve_digit_sign(f, is_negative);
	if (f->dot && f->field_witdh > len)
		precision_zeros = f->field_witdh - len;
	total_len = len;
	total_len += precision_zeros;
	if (sign)
		total_len++;
	if (!f->dot && !f->minus && f->default_ && f->field_witdh)
	{
		if (f->zero && !f->dot && sign)
		{
			count += write(1, &sign, 1);
			sign = '\0';
		}
		count += apply_format(f, total_len);
	}
	if (sign)
		count += write(1, &sign, 1);
	while (precision_zeros-- > 0)
		count += write(1, "0", 1);
	count += write(1, result, ft_strlen(result));
	if (!f->dot && f->minus && f->field_witdh)
		count += apply_format(f, total_len);
	return (free(result), count);
}

// int main()
// {
// 	print_digit(NULL, 45);
// }