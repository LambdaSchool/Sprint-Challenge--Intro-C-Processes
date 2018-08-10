#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  // Parse command line
  char *directory_name;
  if (argc == 1)
  {
    directory_name = ".";
  }
  else if (argc == 2)
  {
    directory_name = argv[1];
  }
  else
  {
    fprintf(stderr, "Too amny arguments! Usage: ./index2 [your directory name]\n");
    exit(1);
  }

  // Open directory
  struct dirent *ent;
  
  
  DIR *directory = opendir(directory_name);
  
  if (directory == NULL)
  {
    fprintf(stderr, "The directory open error");
    exit(2);
  }

  // Repeatly read and print entries
  while ((ent = readdir(directory)) != NULL)
  {
    char path[200];
    struct stat buf;
    
    snprintf(path, sizeof(path), "%s/%s", directory_name, ent->d_name);
    stat(path, &buf);

    if (S_ISREG(buf.st_mode))
    {
      printf("%20lld %s\n", buf.st_size, path);
    }
    else
    {
      printf("%20s %s\n", "<DIR>", path);
    }
    
    
    // // trying to under stand the "If you bitwise-AND the value with S_IFDIR and get a non-zero result, the file is a directory."
    // // this returns a a positive value on files
    // printf("using S_ISREG %d\n",(S_ISREG(buf.st_mode)));

    // // both of these always return a value
    // printf("S_IFREG %d\n",(S_IFREG));
    // printf("value of buf.st_mode %d\n",(buf.st_mode));
  }

  // Close directory
  closedir(directory);
  return 0;
}