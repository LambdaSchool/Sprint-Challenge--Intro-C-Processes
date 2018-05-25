#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
/**
 * Main
 */
int main(int argc, char **argv)
{
  // Parse command line
  
	char *dir_arg;
	if (argc == 1) {
		dir_arg = '.';	
	}
	else if (argc == 2) {
		dir_arg = argv[1];
	}
	else {
		fprintf(stderr, 'Please try again');
		exit(1);
	}
	
  // Open directory
  
	struct dirent *ent;
	printf("Directory:%s\n", dir_arg);
	DIR *directory = opendir(dir_arg);
	
	if(directory == NULL) {
		printf("error occured in opening the dir.");
		exit(1);
	}
	
  // Repeatly read and print entries
  
	while ((ent = readdir(directory)) != NULL) {
		printf("%s\n", ent -> d_name);
	}
 
  // Close directory
  
    closedir(directory); 

  return 0;
}