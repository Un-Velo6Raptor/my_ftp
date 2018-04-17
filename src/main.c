/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "my_ftp.h"

int main(int argc, char **argv)
{
	int ret = 0;

	ret = check_arg(argc, argv);
	return ret;
}