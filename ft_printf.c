/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:52:18 by sombru            #+#    #+#             */
/*   Updated: 2026/03/21 17:51:53 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// malloc, free, write,
// va_start, va_arg, va_copy, va_end
inline static void	resolve_invalid_flags(t_format *f)
{
	if (f->zero && f->minus)
		f->zero = 0;
	if (f->minus && f->default_)
		f->default_ = 0;
	if (f->plus && f->space)
		f->space = 0;
}

inline static char	*get_format_string(const char *input)
{
	int	i;

	i = 0;
	while (!ft_strchr("cspdiuxX%", *input))
	{
		(input)++;
		i++;
	}
	return (ft_strndup(input - i, i + 1));
}

int	expand(const char *input, va_list arg)
{
	t_format	f;
	char		*format_string;

	if (*input == '%')
		return (write(1, "%", 1));
	format_string = get_format_string(input);
	f.default_ = 1;
	f.dot = 0;
	f.field_witdh = 0;
	f.hash = 0;
	f.minus = 0;
	f.plus = 0;
	f.precision = 0;
	f.space = 0;
	f.zero = 0;
	f.specifier = 'n';
	parse_flags(format_string, &f);
	resolve_invalid_flags(&f);
	parse_specifier(format_string, &f);
	free(format_string);
	return (convert(&f, arg));
}

int	ft_printf(const char *input, ...)
{
	int		count;
	va_list	arg;

	count = 0;
	va_start(arg, input);
	while (*input)
	{
		if (*input == '%')
		{
			count += expand(++input, arg);
			while (!ft_strchr("cspdiuxX%", *input))
				input++;
		}
		else
			count += write(STDOUT_FILENO, input, 1);
		input++;
	}
	va_end(arg);
	return (count);
}

// int main()
// {
// 	char str[] = "aa";
// 	printf("my return: %d\n", ft_printf(" % 4d ", -20));
// 	printf("ori return: %d\n", printf(" % 4d ", -20));

// 	printf("my return: %d\n", ft_printf(" %+4d ", -20));
// 	printf("ori return: %d\n", printf(" %+4d ", -20));

// 	printf("my return: %d\n", ft_printf(" %.2d ", -2));
// 	printf("ori return: %d\n", printf(" %.2d ", -2));

// 	printf("my return: %d\n", ft_printf(" %.3d ", -11));
// 	printf("ori return: %d\n", printf(" %.3d ", -11));

// 	printf("my return: %d\n", ft_printf(" %.1x ", 0));
// 	printf("ori return: %d\n", printf(" %.1x ", 0));
// 	(void)str;
// 	return 0;
// }
	// printf("my return: %d\n",ft_printf(" %+4d ", -20));
	// printf("ori return: %d\n", printf(" %+4d ", -20));
	// printf("my return: %d\n",ft_printf(" % 4d ", -20));
	// printf("ori return: %d\n", printf(" % 4d ", -20));