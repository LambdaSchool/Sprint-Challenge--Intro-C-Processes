#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
/**
 * Main
 */
int main(int argc, char **argv)
{
  int i;
  printf("There are %d command line argument(s):\n", argc);
  // Parse command line
    for (i = 0; i < argc; i++) {
         printf("   %s\n", argv[i]);
        printf("argc %d", argc);
    }
  DIR *d;
  struct dirent *ent;
  d = opendir(".");
  if(d == NULL) 
  {
    printf("Error: Unable to open directory.\n");
    exit(1);
  }
  while( (ent = readdir(d)) != NULL) 
  {
      printf("%s\n", ent->d_name);
  }
  closedir(d);   
  return 0;
}