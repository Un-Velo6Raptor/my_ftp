/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <string.h>
#include "my_ftp.h"

int command_quit(int fd_server __attribute__((unused)), t_client *client __attribute__((unused)),
	char *home __attribute__((unused)), char *command __attribute__((unused)))
{
	return 1;
}