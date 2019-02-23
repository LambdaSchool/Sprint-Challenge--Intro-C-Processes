#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  // printf("there were %d arguments", argc);

  char **get_info(char *str) {
    struct dirent *ptr_dirent;

    printf("the directory is: %s\n", str);
    
    DIR *ptr_dir;
    ptr_dir = opendir(str);

    if(ptr_dir == NULL) {
      printf("Cannot open directory %s\n", str);
      // exit(1);
    }

    while ((ptr_dirent = readdir(ptr_dir)) != NULL) {
      printf("[%s]\n", ptr_dirent->d_name);
    }

    closedir(ptr_dir);
    // return 0;
  }

  if (argc < 1) {
    printf("There was an error");

  } else if (argc == 1) {
    char cwd[250];

    // get current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      // printf("Current working directory: %s\n", cwd);
      // print out current working directory
      get_info(cwd);

    }
  }
  // char commands[1024];
  // char *args[100];

  // char **parse_commands(char *str, int *argc, char **args) {
    
  //   char *token;
  //   *argc = 0;

  //   token = strtok(str, " \t\n\r");

  //   while (token != NULL && *argc < 100) {
  //     args[(*argc)++] = token;

  //     token = strtok(NULL, " \t\n\r");
  //   }

  //   args[*argc] = NULL;

  //   return args;
  // }

  // while(1) {
  //   printf("lssh$ ");

  //   fgets(commands, sizeof(commands), stdin);

  //   parse_commands(commands, &argc, args);

  //   if(argc == 0) {
  //     continue;
  //   } else {
  //     printf("%d", argc);
  //   }


  // }
  // Parse command line

  // Open directory

  // Repeatly read and print entries

  // Close directory

  return 0;
}