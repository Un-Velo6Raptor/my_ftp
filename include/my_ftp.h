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
# define  	NB_CLIENT_MAX		100
#endif

#ifndef 	MAX_LENGTH_COMMAND
# define  	MAX_LENGTH_COMMAND	4096
#endif

#ifndef		NB_COMMAND
# define 	NB_COMMAND		100 // Todo: Update to the real number
#endif

enum bool {
	FALSE = 0,
	TRUE = 1,
	UNKNOWN = 2
};

typedef struct s_data_socket {
	int port_server;
	int port_client;

	int fd_socket;

	char *ip_server;
	char *ip_client;
} t_data_socket;

typedef struct s_client_list {
	// Management client
	enum bool is_used;
	enum bool username;
	enum bool password;
	enum bool mode;

	// Data management
	struct s_data_socket data_mng;

	// Process management
	pid_t pid;
	int fd;
} t_client;

// Basics functions
int tablen(char **tab);
void free_tab(char **tab);
char **str_to_wordtab(char *str, char sep);
void disp_ip(char **ip);
void disp_tab(char **tab);

// Init and emulate server
int check_arg(int, char **);
int init_and_launch_server(int port, char *path);
int loop_client_connection(int fd_server, char *path);

// Manage Client
int print_msg_to_client(t_client *client, char *code);
int write_msg(int fd, char *msg);
void error_client(t_client *client, char *msg);
void init_list_client(t_client *list_empty);
int assign_block_client(t_client *list_client, int client_fd);
void close_all_client(t_client *list_client);
void reset_client(t_client *client);

// Manage Command
int init_manage_command(int fd_server, t_client *client, char *path);
int manage_command(int fd_server, t_client *client, char *home, char *command);
int command_user(int fd_server, t_client *client, char *home, char *command);
int command_pass(int fd_server, t_client *client, char *home, char *command);
int command_quit(int fd_server, t_client *client, char *home, char *command);
int command_noop(int fd_server, t_client *client, char *home, char *command);
int command_help(int fd_server, t_client *client, char *home, char *command);
int command_cwd(int fd_server, t_client *client, char *home, char *command);
int command_cdup(int fd_server, t_client *client, char *home, char *command);
int command_pwd(int fd_server, t_client *client, char *home, char *command);
int command_dele(int fd_server, t_client *client, char *home, char *command);
int command_pasv(int fd_server, t_client *client, char *home, char *command);
int command_port(int fd_server, t_client *client, char *home, char *command);
int command_list(int fd_server, t_client *client, char *home, char *command);

// TODO: Potentiellemnt à supprimer
int find_my_ip(int fd, struct sockaddr_in *tmp);

#endif //PSU_MYFTP_2017_MY_FTP_H
