/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_ftp.h"

void error_client(t_client *client, char *msg)
{
	fprintf(stderr, "%s: %s\n", client->data_mng.ip_client, msg);
	client->is_used = FALSE;
	client->username = FALSE;
	client->password = FALSE;
	close(client->fd);
	exit(0);
}