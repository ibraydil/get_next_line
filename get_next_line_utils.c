/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dibrayev <dibrayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 17:14:07 by dibrayev          #+#    #+#             */
/*   Updated: 2026/10/30 19:45:45 by dibrayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

size_t ft_strlen(const char *str)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*final_s;
	size_t len1;
	size_t len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	final_s = malloc(sizeof(char) * (len1 + len2) + 1);
	if (final_s == NULL)
		return (NULL);
	while (i < len1)
	{
    	final_s[i] = s1[i];
    	i++;
	}
	while (j < len2)
	{
    	final_s[i + j] = s2[j];
    	j++;
	}
	final_s[i + j] = '\0';
	return (final_s);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*ss;

	i = 0;
	cc = (char)c;
	ss = (char *)s;
	if (ss == NULL)
		return NULL;
	while (ss[i])
	{
		if (ss[i] == cc)
			return (&ss[i]);
		i++;
	}
	if (cc == '\0')
		return (&ss[i]);
	return (NULL);
}
