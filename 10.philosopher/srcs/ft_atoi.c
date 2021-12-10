#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if ((unsigned char)c == '\t')
		return (1);
	else if ((unsigned char)c == '\n')
		return (1);
	else if ((unsigned char)c == '\v')
		return (1);
	else if ((unsigned char)c == '\f')
		return (1);
	else if ((unsigned char)c == '\r')
		return (1);
	else if ((unsigned char)c == ' ')
		return (1);
	return (0);
}

int	range_check(unsigned long long num, int sign, int type)
{
	if (type == 4)
	{
		if (sign > 0 && num > 0xffffffff)
			return (0);
		else if (sign < 0 && num > 0xffffffff)
			return (0);
	}
	else if (type == 8)
	{
		if (sign > 0 && num > 0xffffffffffffffff)
			return (0);
		else if (sign < 0 && num > 0xffffffffffffffff)
			return (0);
	}
	return (1);
}

void	ft_atoi2_getnum(const char *str, unsigned long long *num, int *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		*num = ((*num * 10) + (str[i] - '0'));
		i++;
	}
}

int	ft_atoi2(const char *str, void *ret, int sizeoftype)
{
	unsigned long long	num;
	int					sign;
	int					range;

	sign = 1;
	num = 0;
	ft_atoi2_getnum(str, &num, &sign);
	range = range_check(num, sign, sizeoftype);
	if (ret)
	{
		if (sizeoftype == 4 && range)
			*((int *)ret) = (int)(num * sign);
		if (sizeoftype == 8 && range)
			*((long long *)ret) = (long long)(num * sign);
	}
	return (range);
}
