/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdlib.h>
#include "my_ftp.h"

int tablen(char **tab)
{
	int idx = 0;

	for (; tab && tab[idx]; ++idx);
	return idx;
}