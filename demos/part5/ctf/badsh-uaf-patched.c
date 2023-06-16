#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	char name[32];
	int auth;
} user_t;

void main(void) {
	setbuf(stdout, NULL);
	
	char line[128];

	user_t *user;
	char *data;
	void *barn[8];

	int barn_count = 0;
	int is_logged_in = 0;
	int has_data = 0;

	printf("Welcome to my crappy program. Type \"help\" for available commands.\n");

	while(1) {
		printf("--> ");

		if(fgets(line, sizeof(line), stdin) == NULL)
			break;
		
		// The help command
		if(strncmp(line, "help", 4) == 0) {
			printf("Available commands:\n"
				"\tlogin <name>\t- create a user object\n"
			    "\twhoami\t\t- display current user object\n"
		 		"\twrite <data>\t- create a data object (max 36-bytes)\n"
				"\tprint\t\t- print current data object\n"
				"\tlogout\t\t- free 36-byte user object\n"
				"\tclear\t\t- free data object\n"
				"\tadd <digit>\t- create N 36-byte objects in the barn (max capacity 8)\n"
				"\tremove <digit>\t- free N (up to 8 existing) 36-byte objects from the barn\n"
				"\texit\t\t- Exits the program\n"
				"\twin\t\t- Open a shell if authorized.\n");
		}

		// The login command
		else if(strncmp(line, "login ", 6) == 0) {
			user = malloc(sizeof(user_t));
			user->auth = 0;

			if(strlen(line + 6) < 31)
				strcpy(user->name, line + 6);
			
			is_logged_in = 1;
			printf("Logged in.\n");
		}

		// The whoami command
		else if(strncmp(line, "whoami", 6) == 0) {
			if(is_logged_in)
				printf("Logged in as %sHas authorization? %s\n", 
						user->name, (user->auth) ? "Yes" : "No");
			else printf("Not logged in.\n");
		}

		// The write command
		else if(strncmp(line, "write", 5) == 0) {
			data = strndup(line + 6, 36);
			printf("Wrote data: %s\n", data);
		}

		// The print command
		else if(strncmp(line, "print", 5) == 0) {
			if(has_data) printf("Data: %s", data);
			else printf("No data.\n");
		}

		// The logout command
		else if(strncmp(line, "logout", 6) == 0) {
			free(user);
			is_logged_in = 0;
			printf("Logged out.\n");
		}

		// The clear command
		else if(strncmp(line, "clear", 5) == 0) {
			free(data);
			has_data = 0;
			printf("Cleared data.\n");
		}
		
		// The add command
		else if(strncmp(line, "add ", 4) == 0) {
			int added;

			if (!isdigit(line[4])) {
				printf("Argument is not a digit.\n\n");
				continue;
			} 
			
			int num = (int) line[4] - 48;

			for (added = 0; barn_count < 8 && added < num; added++)
				barn[barn_count++] = malloc(36);

			printf("Added %i objects to barn. Barn is now at %i objects.\n", added, barn_count);
		}

		// The remove command
		else if(strncmp(line, "remove ", 7) == 0) {
			int removed;

			if (!isdigit(line[7])) {
				printf("Argument is not a digit.\n\n");
				continue;
			}
			
			int num = (int) line[7] - 48;

			for (removed = 0; barn_count > 0 && removed < num; removed++)
				free(barn[--barn_count]);
			
			printf("Removed %i objects from barn. Barn is now at %i objects.\n", removed, barn_count);
		}

		// The win command - now without any use-after-free's >:3
		else if(strncmp(line, "win", 3) == 0) {
			if (!is_logged_in) {
				printf("Not logged in.\n\n");
				continue;
			}

			if(user->auth) {
				printf("You win.\n");
				system("/bin/sh");
			}
			else printf("You are not authorized.\n");
		}

		// The exit command
		else if(strncmp(line, "exit", 4) == 0)
			return;

		// User typed something weird
		else printf("Invalid command: %s", line);

		printf("\n");
	}
}
