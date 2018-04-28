/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include <stdlib.h>
#include "my_ftp.h"

static int count_words(char *str, char sep)
{
	int result = 0;

	if (!str)
		return 0;
	for (int idx = 0; str[idx] != '\0'; ++idx) {
		if (str[idx] == sep)
			result++;
	}
	if ((!result && strlen(str)) ||
		(strlen(str) > 0 && str[strlen(str) - 1] != sep))
		result++;
	return result;
}

static int len_word(char *str, char sep)
{
	int idx = 0;

	for (; str[idx] != '\0' && (str[idx] != sep || !idx); ++idx);
	return idx;
}

static int copy_word(char *str, char *result, char sep)
{
	int idx = 0;
	int tmp = 0;

	if (!str || !result)
		return 0;
	for (; str[tmp] != '\0' && str[tmp] == sep; ++tmp);
	for (; str[idx + tmp] != '\0' && str[idx + tmp] != sep; ++idx) {
		result[idx] = str[idx + tmp];
	}
	result[idx] = '\0';
	return idx + tmp;
}

char **str_to_wordtab(char *str, char sep)
{
	int nb_words = count_words(str, sep);
	char **tab = NULL;
	int idx = 0;
	int start = 0;

	if (!str)
		return NULL;
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return NULL;
	for (; idx < nb_words; ++idx) {
		tab[idx] = malloc(sizeof(char) * (len_word(&str[start], sep) + 1));
		if (!tab[idx])
			return NULL;
		start += copy_word(&str[start], tab[idx], sep);
		tab[idx + 1] = NULL;
	}
	tab[idx] = NULL;
	return tab;
}
