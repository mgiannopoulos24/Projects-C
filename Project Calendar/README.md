# Calendar Application
This is a command-line calendar application written in C. It allows users to display calendars for a specific month or the entire year in a customizable grid format.

## Features
- Display a calendar for a specific month.
- Display a calendar for an entire year in a 2-row, 6-column grid format.
- Support for leap years.
- Simple and intuitive command-line interface.

## Compilation
Compile the project using the provided Makefile:
```console
make
```

## Usage
Run the compiled executable `calendar` to interact with the calendar application:
```console
./build/calendar
```

The application will prompt you to enter either a year and month (YYYY MM) or just a year (YYYY). Based on your input, it will display the corresponding calendar.

Example usage:

```console
Enter year and month (YYYY MM) or year only (YYYY): 2024
Enter year and month (YYYY MM) or year only (YYYY): 2024 3
```

## Clean Up
To clean up the compiled files and object files, run:
```console
make clean
```