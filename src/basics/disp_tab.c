/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include "my_ftp.h"

void disp_tab(char **tab)
{
	for (int idx = 0; tab && tab[idx]; ++idx) {
		printf("[%d]: %s\n", idx, tab[idx]);
	}
}

void disp_ip(char **ip)
{
	for (int idx = 0; ip && ip[idx]; ++idx) {
		printf("%s", ip[idx]);
		if (ip[idx + 1])
			printf(".");
	}
	printf("\n");
}