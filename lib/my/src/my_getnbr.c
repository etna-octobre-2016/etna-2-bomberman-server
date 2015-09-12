#include "./headers/my.h"

int	my_getnbr(char *str)
{
  int	int_out;
  int	sign;

  int_out = 0;
  sign = 1;
  if (*str == '-')
    {
      sign = -1;
      str++;
    }
  while  (my_strlen(str) > 0 && (*str >= 48 || *str <= 57))
    {
      int_out = int_out * 10 + ((int) * str) - 48;
      str++;
    }
  return (int_out * sign);
}
