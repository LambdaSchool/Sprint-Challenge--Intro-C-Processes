#include <stdio.h>
#include <dirent.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  // Parse command line
  int i;

  printf("There are %d command line argument(s):\n", argc);

  for (i = 0; i < argc; i++) {
      printf("   %s\n", argv[i]);
  }
  // Open directory
  DIR *d = opendir(".");
  printf("Testing: %s\n", d == NULL? "FAIL": "PASS");

  // Repeatly read and print entries

  // Close directory
  closedir(dir);

  return 0;
}