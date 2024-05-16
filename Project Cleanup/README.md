# Recursive Directory Deletion Program

This C program provides functionality to recursively delete files and directories within a specified root directory path. It is designed to work across different operating systems, including Windows, macOS, and Unix-like systems.

## Features 

- **Cross-platform:** The program handles differences between Windows and Unix-like systems transparently, ensuring consistent behavior across different platforms.
- **Recursive deletion:** It traverses through directories recursively, deleting all files and subdirectories within the specified root directory path.
- **Error handling:** Error messages are provided in case of failure during file or directory deletion, aiding in debugging and troubleshooting.

### How to compile:

`gcc -o cleanup cleanup.c`

### How to run:

`./cleanup.exe` or `./cleanup`

## Disclaimer
**Use this program responsibly**. Double-check the root directory path before running the program to avoid unintended data loss.