# Hospital Management System

The Hospital Management System is a command-line application written in C. It allows hospital staff to manage patient records, doctor details, and appointments efficiently. This system helps streamline operations by providing functionalities to add patients, add doctors, schedule appointments, and display lists of patients, doctors, and appointments.

## Features

- Add Patient: Allows adding new patients with unique IDs, names, ages, genders, and phone numbers.
- Display Patients: Displays a list of all registered patients with their details.
- Add Doctor: Enables adding new doctors with unique IDs, names, and departments.
- Display Doctors: Shows a list of all registered doctors along with their departments.
- Schedule Appointment: Facilitates scheduling appointments between patients and doctors by entering IDs, dates, and times.
- Display Appointments: Lists all scheduled appointments with details including patient names, doctor names, dates, and times.
- Input Handling: Supports input of names and departments with spaces using `fgets` for robust input handling.

## Usage

1. Compilation: To compile the program use `make` or `make all` and to remove it use `make clean`.
2. Execution: `./hospital`
3. Navigation: Use the menu displayed to navigate through different options:
- Enter the corresponding number to perform actions such as adding patients/doctors, scheduling appointments, displaying lists, or exiting the system.
4. Input Format:
- Patient and doctor IDs should be alphanumeric (e.g., P001, D001).
- Names can include spaces.
- Age is expected as an integer.
- Gender should be entered as 'M' or 'F'.
- Date format: DD/MM/YYYY.
- Time format: HH
5. Limitations:
- Maximum capacity:
    - Patients: 50
    - Doctors: 50
    - Appointments: 100
- The system does not handle advanced validation or storage (e.g., database integration).

## Example

```bash
--- Hospital Management System ---
1. Add Patient
2. Display Patients
3. Add Doctor
4. Display Doctors
5. Schedule Appointment
6. Display Appointments
0. Exit
Enter your choice: 1

Enter patient ID: P001
Enter patient name: John Doe
Enter patient age: 35
Enter patient gender (M/F): M
Enter patient phone number: 1234567890

Enter your choice: 3

Enter doctor ID: D001
Enter doctor name: Dr. Smith
Enter doctor department: Cardiology

Enter your choice: 5

Enter appointment ID: A001
Enter patient ID: P001
Enter doctor ID: D001
Enter date (DD/MM/YYYY): 20/06/2024
Enter time (HH:MM): 10:30

Enter your choice: 2

--- List of Patients ---
ID: P001, Name: John Doe, Age: 35, Gender: M, Phone: 1234567890

Enter your choice: 4

--- List of Doctors ---
ID: D001, Name: Dr. Smith, Department: Cardiology

Enter your choice: 6

--- List of Appointments ---
ID: A001, Patient: John Doe (P001), Doctor: Dr. Smith (D001), Date: 20/06/2024, Time: 10:30

Enter your choice: 0
Exiting...
```