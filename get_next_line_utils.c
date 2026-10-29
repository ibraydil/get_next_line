
size_t ft_strlen(char *str)
{
  size_t len;
  len = 0;
  
  if (str == NULL)
    return 0;
  while (*str)
    {
      len++;
      str++;
    }
  return(len);
}
