/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include <stdlib.h>
#include "my_ftp.h"

static int count_words(char *str)
{
	int result = 0;

	for (int idx = 0; str[idx] != '\0'; ++idx) {
		if (str[idx] == ' ')
			result++;
	}
	if ((!result && strlen(str)) ||
		(strlen(str) > 0 && str[strlen(str) - 1] != ' '))
		result++;
	return result;
}

static int len_word(char *str)
{
	int idx = 0;

	for (; str[idx] != '\0' && str[idx] != ' '; ++idx);
	return idx;
}

static int copy_word(char *str, char *result)
{
	int idx = 0;
	int tmp = 0;

	for (; str[tmp] != '\0' && str[tmp] == ' '; ++tmp);
	for (; str[idx + tmp] != '\0' && str[idx + tmp] != ' '; ++idx) {
		result[idx] = str[idx + tmp];
	}
	result[idx] = '\0';
	return idx + tmp;
}

char **str_to_wordtab(char *str)
{
	int nb_words = count_words(str);
	char **tab = malloc(sizeof(char *) * (nb_words + 1));
	int idx = 0;
	int start = 0;

	if (!tab)
		return NULL;
	for (; idx < nb_words; ++idx) {
		tab[idx] = malloc(sizeof(char) * (len_word(str) + 1));
		if (!tab[idx])
			return NULL;
		start += copy_word(&str[start], tab[idx]);
		tab[idx + 1] = NULL;
	}
	tab[idx] = NULL;
	return tab;
}