#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int	flag(va_list arg, const char c);
int	digit(int nb);
size_t	ft_strlen(char *str);
int	string(char *str);
int	hex(unsigned int nb);

int	ft_printf(const char *s, ...)
{
	int	i;
	int	len;
	va_list	arg;

	i = 0;
	len = 0;
	va_start(arg, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			len += flag(arg, s[i]);
		}
		else
			len += write(1, &s[i], 1);
		i++;
	}
	return (len);
}

int	flag(va_list arg, const char c)
{
	int	len;

	len = 0;
	if (c == 'd')
		len = digit(va_arg(arg, int));
	if (c == 'x')
		len = hex(va_arg(arg, unsigned int));
	if (c == 's')
		len = string(va_arg(arg, char *));
	return (len);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	string(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	digit(int nb)
{
	int	len;
	int	i;

	len = 0;
	if (nb == -2147483648)
		return (string("-2147483648"));
	if (nb < 0)
	{
		len += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
		len += digit(nb / 10);
	i = nb % 10 + 48;
	len += write(1, &i, 1);
	return (len);
}

int	hex(unsigned int nb)
{
	int	i;
	int	len;

	len = 0;
	i = nb % 16;
	if (nb >= 16)
		len += hex(nb / 16);
	if (i < 10)
		i += 48;
	else
		i += 87;
	len += write(1, &i, 1);
	return (len);
}

/*int	main(int ac, char **av)
{
	if (ac == 4)
	{
		int i = atoi(av[1]);
		int j = atoi(av[2]);
		int k = printf("digit: %d, hex: %x, string: %s\n", i, j, av[3]);
		printf("%d\n", k);
		int t = ft_printf("digit: %d, hex: %x, string: %s\n", i, j, av[3]);
		printf("%d\n", t);
	}
}*/