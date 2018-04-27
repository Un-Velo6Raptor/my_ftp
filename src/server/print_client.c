/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "my_ftp.h"

static const char *msg_client[17] = {
	"200 Command okay.\r\n",
	"214 Help message.\r\n",
	"220 Service ready for new user.\r\n",
	"226 Closing data connection.\r\n",
	"230 User logged in, proceed.\r\n",
	"250 Requested file action okay, completed.\r\n",
	"331 User name okay, need password.\r\n",
	"332 Need account for login.\r\n",
	"221 Service closing control connection.\r\n",
	"425 Use PORT or PASV first.\r\n",
	"426 Connection closed; transfer aborted.\r\n",
	"500 Unknown command.\r\n",
	"530 Not logged in.\r\n",
	"550 Failed to change directory.\r\n",
	"552 Requested file action aborted. Exceeded storage allocation (for current directory or dataset).\r\n",
	"xxx Error (RFC compliant)\r\n",
	NULL
};

int write_msg(int fd, char *msg)
{
	int ret = 0;
	fd_set readfs;
	struct timeval select_wait;

	select_wait.tv_usec = 1000;
	if (!msg)
		return 84;
	FD_ZERO(&readfs);
	FD_SET(fd, &readfs);
	if (FD_ISSET(fd, &readfs))
		ret = write(fd, msg, strlen(msg));
	return ret;
}

int print_msg_to_client(t_client *client, char *code)
{
	int ret = 0;
	int len_code = strlen(code);

	for (int idx = 0; msg_client[idx] != NULL; ++idx) {
		if (!strncmp(code, msg_client[idx], len_code)) {
			ret = write_msg(client->fd, msg_client[idx]);
			break;
		}
	}
	if (ret != -1)
		ret = 0;
	return ret;
}