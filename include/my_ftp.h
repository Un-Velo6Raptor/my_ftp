/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_MYFTP_2017_MY_FTP_H
# define PSU_MYFTP_2017_MY_FTP_H

# include <unistd.h>

#ifndef 	NB_CLIENT_MAX
# define  	NB_CLIENT_MAX	100
#endif

#ifndef 	MAX_LENGTH_COMMAND
# define  	MAX_LENGTH_COMMAND	4096
#endif

enum bool {
	FALSE = 0,
	TRUE = 1
};

typedef struct s_client_list {
	enum bool is_used;
	enum bool username;
	enum bool password;

	pid_t pid;
	int fd;
	char *ip;
	char *current_path;
} t_client;

// Prototypes
int check_arg(int, char **);
int init_and_launch_server(int port, char *path);
int loop_client_connection(int fd_server, char *path);
int print_msg_to_client(t_client *client, char *code);
void error_client(t_client *client, char *msg);
void init_list_client(t_client *list_empty);
int assign_block_client(t_client *list_client, int client_fd);
void close_all_client(t_client *list_client);
void reset_client(t_client *client);
int init_manage_command(int fd_server, t_client *client, char *path);

#endif //PSU_MYFTP_2017_MY_FTP_H
