#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd;

    if (argc < 2) {
        printf("I need the file to open as an argument!\n");
        return 0;
    }

    fd = open(argv[1], O_RDONLY);

    if (fd < 0){
        perror("open");
        return fd;
    }

    close(fd);

    fd = open(argv[1], O_RDWR | O_SYNC);

    if (fd < 0){
        perror("open");
        return fd;
    }

    close(fd);

    fd = open(argv[1], O_WRONLY | O_NONBLOCK);

    if (fd < 0){
        perror("open");
        return fd;
    }

    close(fd);

    return 0;
}

/*
1. Argument Validation
The program first checks argc to ensure you provided a filename when running the command (e.g., ./my_program test.txt). If you didn't, it prints an error message and quits.

2. The Three "Open" Tests
The core of the program attempts to open the file you specified three different times, each with a different set of permissions and behaviors.

Attempt,Flags Used,What it does
#1,O_RDONLY,Read-Only: Checks if the file exists and if you have permission to read it.
#2,O_RDWR | O_SYNC,"Read/Write + Synchronous: Checks if you can both read and write. The O_SYNC flag ensures that any writing operations are written directly to the disk hardware immediately, rather than being cached by the OS."
#3,O_WRONLY | O_NONBLOCK,"Write-Only + Non-blocking: Checks if you can write to the file. The O_NONBLOCK flag is usually used for special files (like pipes or device files) so the program doesn't ""hang"" or wait if the file isn't ready."

3. Error Handling
After every open() call, the program checks if the File Descriptor (fd) is less than 0.

If fd is negative, it means the open attempt failed (e.g., the file doesn't exist or you don't have permission).

It uses perror("open"), which prints a human-readable explanation of why it failed (like "Permission denied" or "No such file or directory").

4. Cleanup
After every successful open, it immediately calls close(fd). This is good practice to free up the file descriptor before trying to open it again with different settings.

Summary of Key Functions
open(): Requests the operating system to give the program access to a file. It returns a "File Descriptor" (an integer) which acts as a handle for that file.

argv[1]: This is the string containing the filename you passed in the terminal.

O_RDONLY, O_WRONLY, O_RDWR: These are the "Big Three" access modes (Read, Write, or Both).

Note: If you run this on a standard text file that you own, it will likely succeed on all three steps and exit silently. It only "speaks up" if you forget the argument or if an error occurs.
*/