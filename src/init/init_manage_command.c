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
#include <arpa/inet.h>
#include <netdb.h>
#include "my_ftp.h"

static int epur_and_launch_command(int fd_server, t_client *client, char *home,
	char *cmd)
{
	int tmp = 0;

	for (int idx = 0; cmd[idx] != '\0'; ++idx) {
		while ((cmd[idx] == ' ' || cmd[idx] == '\t') &&
			cmd[idx + 1] != '\0' &&
			(cmd[idx + 1] == ' ' || cmd[idx + 1] == '\t')) {
			cmd[idx] = ' ';
			cmd[idx + 1] = ' ';
			idx++;
		}
		if (cmd[idx] != ' ' || (tmp > 0 && idx < strlen(cmd) - 1)) {
			cmd[tmp] = cmd[idx];
			tmp++;
		}
	}
	cmd[tmp] = '\0';
	if (strlen(cmd) >= 2 && !strcmp(&cmd[strlen(cmd) - 2], "\r\n"))
		cmd[strlen(cmd) - 2] = '\0';
	return manage_command(fd_server, client, home, cmd);
}

static int command_send_to_manage(t_client *client, int fd_server, char *home)
{
	char command[MAX_LENGTH_COMMAND + 1];
	int len = 0;

	len = read(client->fd, command, MAX_LENGTH_COMMAND);
	if (len <= 0)
		exit(1);
	command[len] = '\0';
	return epur_and_launch_command(fd_server, client, home, command);
}

static int loop_read(int fd_server, t_client *client, char *home)
{
	int ret = 0;
	struct timeval select_wait;
	fd_set readfs;

	select_wait.tv_usec = 1000;
	while (!ret) {
		FD_ZERO(&readfs);
		FD_SET(client->fd, &readfs);
		if (select(client->fd + 1, &readfs, NULL, NULL, &select_wait) ==
			-1) {
			ret = 84;
		} else if (FD_ISSET(client->fd, &readfs))
			ret = command_send_to_manage(client, fd_server, home);
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