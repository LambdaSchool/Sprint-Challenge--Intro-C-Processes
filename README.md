# Sprint-Challenge: Intro to C and Processes

Complete both tasks below.

_The code for the second task needs a Unix-like environment to work! That includes
Linux, macos, Cygwin, WSL, BSD, etc._

If you want to test if your environment is set up for it, compile and run the
[testdir.c](examples/testdir.c) program in the `examples/` directory. (You can
type `make` in the `examples/` directory.) It should print `Testing: PASS`.

## Task 1

### Short Answer Questions

Add your answers inline, below, with your pull request.

1. List all of the main states a process may be in at any point in time on a standard Unix system. Briefly explain what each of these states means.
  Start
    Initial state of a process upon creation.
  Ready
    Process is started and awaiting to be assigned a processor. Upon computer startup the computer goes through and opens all the scheduled start up programs but while they can all be started by an initial process; they cannot be run until the OS assigns a processor to complete the scheduled process.
  Running
    Once a processor is assigned to the process, the process starts executing its instructions.
  Waiting
    Waiting is when a process goes into a waiting or standby state. This could be for a number of reasons; the program could be awaiting user input to continue executing its instructions. It could also be waiting for a resource to become available. (internet, data, file, another process to complete.)
  Terminating
    OS terminates the process once it completes its instructions, once in terminating or Exit state the process waits to be removed from memory, as it no longer needs to be taking up computer resources.


2. What is a zombie process? How does one get created? How does one get destroyed?
  A zombie process is a child process in exit status that is never read by the parent process. If a parent process doesn't contain a wait command to wait for the child process to terminate before terminating there is no parent process to reap the child. The child process will then just take up space on the process table, each zombie process has its own PID, and since Linux/Unix have a finite amount of PID's for assignment, with too many zombie processes no new processes can be opened.
  To prevent zombie processes using the wait() system call in the parent process to wait for the child to terminate. The parent will then collect/reap the exit status of the child process and schedule it to be removed from the process table. 
  To destroy a zombie process (since they are "dead" they cannot be killed by normal calls), you can sending a SIGCHLD signal to the parent; which will force the parent to perform wait() system call an subsequently reap it's zombie children. If that call does not work there is a problem with the parent process and you would need to kill the parent process directly; once the parent has been killed init adopts all the zombie children. init periodically calls wait() which will clean up the zombie children.

3. What are some of the benefits of working in a compiled language versus a non-compiled language? More specifically, what benefits are there to be had from taking the extra time to compile our code?
  Compiled languages typically run faster and are more efficient then non-compiled languages, this is because once compiled a program can be run any number of times without have to re-compiling the language unless changes are made. A non-compiled languages relies on an interpreter to run the program, and each time it is exectued the program must be parsed, interpreted, and then executed.
  Since a program cannot be compiled until errors are resolved, this way you will never be able to run a compiled language program until errors are resolved allowing the compiler to compile.


## Task 2

Write a program in C, `lsls.c`, that prints out a directory listing for the
directory the user specifies on the command line. If the user does not specify a
directory, print out the contents of the current directory, which is called `.`.

### Example runs:

```
$ ./lsls
.
..
lsls.c
lsls

$ ./lsls /home/exampleuser
.
..
.config
.vim
.yarnrc
.bashrc
foo.c
.vscode
Downloads
.gitconfig
.bash_history
.viminfo
src
```

**Hint**: Start by just printing out the contents of the current directory `.`,
and then add the command line parsing later after you have it working.

### General approach

_You are expected to use Google to find examples of how to use these functions.
Also see [Details](#details), below._

1. Call `opendir()`.
2. Then repeatedly call `readdir()`--printing the filenames as you go--until it
   lets you know there are no more directory entries by returning `NULL`.
3. Then call `closedir()`.

You don't have to write the three functions, above. They're _system calls_ built
into the OS.

### Details

You will be using functionality included in `<dirent.h>`. This header file holds
the declarations for `DIR`, `struct dirent`, `opendir()`, `readdir()`, and
`closedir()`, below.

* `DIR *opendir(char *path)`: This function opens the directory named in `path`
  (e.g. `.`) and returns a pointer to a variable of type `DIR` that will be used
  later. If there is an error, `opendir()` returns `NULL`.
  
  _You should check for errors. If there is one, print an error message and exit
  (using the `exit()` function)._

* `struct dirent *readdir(DIR *d)`: Reads the next directory entry from the
  `DIR` returned by `opendir()`. Returns the result as a pointer to a `struct
  dirent` (see below). Returns `NULL` if there are no more directory entires.

* `closedir(DIR *d)`: Close a directory (opened previously with `opendir()`)
  when you're done with it.

The `struct dirent *` returned by `readdir()` has the following fields in it:

```c
struct dirent {
  ino_t  d_ino       // file serial number
  char   d_name[]    // file name, a string
};
```

(You don't need to declare this `struct dirent` type. It's already included in
`<dirent.h>`.)

For output, you should print the field `d_name` from your `struct dirent *`
variable, e.g.

```c
struct dirent *ent;

// ... some of your code ...

ent = readdir(d);

printf("%s\n", ent->d_name);
```

To parse the command line, you'll have to look at `argc` and `argv` specified in
your `int main(int argc, char **argv)` function. Example code to print all
command line arguments can be found in [commandline.c](examples/commandline.c).
Modify that example to look at the command line parameters, if any, and pass
those to `opendir()`.

### Stretch Goal: Print file size in bytes

Modify the program to print out the file size in bytes as well as the name.

Example output (suggestion: use `%10lld` to print the size in a field of width
10):

```
$ ./lsls
    224  .
    992  ..
   1722  lsls.c
   8952  lsls
```

You'll need to use the `stat()` call in `<sys/stat.h>`.

* `int stat(char *fullpath, struct stat *buf)`: For a given full path to a file
  (i.e. the path passed to `opendir()` following by a `/` followed by the name
  of the file in `d_name`), fill the fields of a `struct stat` that you've
  pointed to. Returns `-1` on error.

  ```c
  // Example stat() usage

  struct stat buf;

  stat("./lsls.c", &buf);

  printf("file size is %lld\n", buf.st_size);
  ```

### Stretch Goal: Mark Directories

Instead of a size in bytes for a directory (which is marginally useful), replace
the number with the string `<DIR>`.

Example output:

```
$ ./lsls
     <DIR>  .
     <DIR>  ..
      1717  lsls.c
      8952  lsls
```

The `st_mode` field in the `struct stat` buffer holds information about the file
permissions and type of file.

If you bitwise-AND the value with `S_IFDIR` and get a non-zero result, the file
is a directory.

(If you bitwise-AND the value with `S_IFREG` and get a non-zero result, the file
is a regular file, as opposed to a device node, symbolic link, hard link,
directory, named pipe, etc.)
