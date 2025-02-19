/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipexsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:42:23 by aleortiz          #+#    #+#             */
/*   Updated: 2025/02/19 16:08:44 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char *s);
static int	slash_split(char *s, int *cti, char **splstr, int ctj);

char	**ft_split_pipex(char *s)
{
	char	**splstr;
	int		cti;
	int		ctj;
	int		quotes;
	int		diff;

	splstr = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!splstr)
		return (NULL);
	cti = 0;
	ctj = 0;
	diff = 0;
	quotes = 0;
	while (s[cti])
		ctj = slash_split(s, &cti, splstr, ctj);
	splstr[ctj] = NULL;
	return (splstr);
}
static int	count_words(char *s)
{
	int	ctu;
	int	words;
	int	quote;

	ctu = 0;
	words = 0;
	quote = 0;
	while (s[ctu])
	{
		while (s[ctu]  && (s[ctu] == ' ' || s[ctu] == '\t'))
			ctu++;
		if (s[ctu])
			words++;
		while (s[ctu] && ((s[ctu] != ' ' && s[ctu] != '\t') || quote))
		{
			if (s[ctu] == 39 || s[ctu] == 34)
				quote = !quote;
			ctu++;
		}
	}
	return (words);
}
static int	slash_split(char *s, int *cti, char **splstr, int ctj)
{
	int	diff;
	int	quotes;

	diff = 0;
	quotes = 0;
	while (s[*cti] && (s[*cti] == ' ' || s[*cti] == '\t'))
	(*cti)++;
	diff = *cti;
	while (s[*cti] && ((s[*cti] != ' ' && s[*cti] != '\t') || quotes))
	{
		if (s[*cti] == 39 || s[*cti] == 34)
			quotes = !quotes;
		(*cti)++;
	}
	if (*cti > diff)
		splstr[ctj++] = ft_substr(s, diff, *cti - diff);
	return (ctj);
}