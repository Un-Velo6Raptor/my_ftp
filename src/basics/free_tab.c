/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdlib.h>
#include "my_ftp.h"

void free_tab(char **tab)
{
	for (int idx = 0; tab && tab[idx]; ++idx) {
		free(tab[idx]);
	}
	if (tab)
		free(tab);
}