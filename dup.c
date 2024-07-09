/*A program demonstrating the implementation of system calls for manipulating the file descriptors*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char *file_path = "example.txt";
    int original_fd, dup_fd;

    // Opening a file in read-only mode
    original_fd = open(file_path, O_RDONLY);
    if (original_fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("File opened successfully.\n");

    // Duplicating the file descriptor
    dup_fd = dup(original_fd);
    if (dup_fd == -1) {
        perror("Error duplicating file descriptor");
        exit(EXIT_FAILURE);
    }

    printf("File descriptor duplicated successfully.\n");

    // Reading and printing the contents of the file using original file descriptor
    printf("Original file descriptor content:\n");
    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(original_fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("Error reading file using original file descriptor");
        exit(EXIT_FAILURE);
    }

    // Reading and printing the contents of the file using duplicated file descriptor
    printf("\nDuplicated file descriptor content:\n");
    lseek(dup_fd, 0, SEEK_SET); //resets the file pointer of the duplicated file descriptor to the beginning of the file.
    while ((bytes_read = read(dup_fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("Error reading file using duplicated file descriptor");
        exit(EXIT_FAILURE);
    }

    // Closing the file descriptors
    if (close(original_fd) == -1) {
        perror("Error closing original file descriptor");
        exit(EXIT_FAILURE);
    }

    if (close(dup_fd) == -1) {
        perror("Error closing duplicated file descriptor");
        exit(EXIT_FAILURE);
    }

    printf("\nFile descriptors closed successfully.\n");

    return 0;
}
/*
Open a file and obtain its file descriptor.
Duplicate the file descriptor using dup.
Read and print the file contents using both the original and duplicated file descriptors.
Reset the file pointer using lseek.
Close the file descriptors properly to release system resources.




*/