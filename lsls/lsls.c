#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  DIR *directory;
  struct dirent *entry;
  struct stat st;
  int *filepath;
  int pathlen1;
  int pathlen2;
  int fullpathlen;
  
  for (int i = 1; i < argc; i++) {
  directory = opendir(argv[i]);
  if (directory == NULL) {
    printf("Cannot open directory '%s'\n", argv[i]);
    return 1;
  }
  while ((entry = readdir(directory)) != NULL) {
  // pathlen = (strlen(argv[i])+(strlen(entry->d_name));
  pathlen1 = strlen(argv[i]);
  pathlen2 = strlen(entry->d_name);
  fullpathlen = pathlen1 + pathlen2;
  filepath = malloc(fullpathlen * sizeof(char) + 2);
  sprintf(filepath, "%s/%s", argv[i], entry->d_name);
  printf("%s \n", entry->d_name);
  stat(filepath, &st);
  printf("%10lld \n", (long long int) st.st_size);
  free(filepath);
  }
  // int rc = fork();
  // if(rc < 0) {
  //   fprintf(stderr, "Fork failed \n");
  //   exit(1);
  // } else if(rc == 0) {
  //   while ((entry = readdir(directory)) != NULL) {
  //     printf("%s \n", entry->d_name);  
  //   }
  // } else {
  //   int wc = waitpid(rc, NULL, 0);
  //   closedir(directory);
  // }
  }
  return 0;
}