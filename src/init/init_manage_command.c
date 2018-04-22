/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my_ftp.h"

static int epur_and_launch_command(int fd_server, t_client *client, char *home,
	char *command)
{
	if (!strcmp(command, "\r\n"))
		return 0;
	int tmp = 0;
	for (int idx = 0; command[idx] != '\0' ; ++idx) {
		while ((command[idx] == ' ' || command[idx] == '\t') &&
			command[idx + 1] != '\0' && (command[idx + 1] == ' ' ||
			command[idx + 1] == '\t')) {
			command[idx] = ' ';
			command[idx + 1] = ' ';
			idx++;
		}
		if (command[idx] != ' ' ||
			(tmp > 0 && idx < strlen(command) - 1)) {
			command[tmp] = command[idx];
			tmp++;
		}
	}
	command[tmp] = '\0';
	return manage_command(fd_server, client, home, command);
}

static int loop_read(int fd_server, t_client *client, char *home)
{
	char command[MAX_LENGTH_COMMAND + 1];
	int ret = 0;
	int len = 0;
	struct timeval select_wait;
	fd_set readfs;

	select_wait.tv_usec = 1000;
	while (!ret) {
		FD_ZERO(&readfs);
		FD_SET(client->fd, &readfs);
		if (select(client->fd + 1, &readfs, NULL, NULL, &select_wait) ==
			-1) {
			ret = 84;
		} else if (FD_ISSET(client->fd, &readfs)) {
			len = read(client->fd, command, MAX_LENGTH_COMMAND);
			if (len <= 0)
				exit(1);
			command[len] = '\0';
			ret = epur_and_launch_command(fd_server, client, home, command);
		}
	}
	return ret;
}

int init_manage_command(int fd_server, t_client *client, char *path)
{
	int ret = 0;
	char *home = NULL;

	if (chdir(path) == -1)
		return 84;
	home = getcwd(NULL, 0);
	if (!home)
		return 84;
	home = realloc(home, strlen(home) + 2);
	if (!home)
		return (84);
	strcat(home, "/");
	ret = loop_read(fd_server, client, home);
	free(home);
	return ret;
}