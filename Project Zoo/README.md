# Zoo Management System
The Zoo Management System is a command-line application written in C that helps manage animals, enclosures, zookeepers, and visitors in a zoo setting. This system provides functionalities to add animals to enclosures, create new enclosures, assign zookeepers to enclosures, add visitors to the zoo, and view detailed information about the zoo's status.

## Features
- Add Animal: Allows users to add new animals to the zoo and assign them to specific enclosures.
- Create Enclosure: Enables the creation of new enclosures with different habitat types.
- Add Zookeeper: Facilitates the addition of new zookeepers with their respective expertise.
- Add Visitor: Adds visitors to the zoo, recording their name and age.
- Assign Zookeeper to Enclosure: Assigns zookeepers to manage specific enclosures.
- View Zoo Information: Displays detailed information about all enclosures, including their animals and assigned zookeepers.

## Compilation

To compile the program run `make` or `make all` and to remove it use `make clean`.

## Usage
Upon running the program (`./zoo_management`), you will be presented with a menu where you can choose from various options to manage the zoo. Follow the prompts to add animals, create enclosures, add zookeepers, assign zookeepers to enclosures, add visitors, and view zoo information.

## Menu Options
1. Create an enclosure
2. Add an animal
3. Add a zookeeper
4. Add a visitor
5. Assign a zookeeper to an enclosure
6. View zoo information
7. Exit

## Example 

1. Create an enclosure:
```bash
===== Zoo Management System Menu =====
1. Create an enclosure
2. Add an animal
3. Add a zookeeper
4. Add a visitor
5. Assign a zookeeper to an enclosure
6. View zoo information
7. Exit
Enter your choice: 1
Enter enclosure name: Lions
Enter habitat: Savannah
Enclosure created successfully.
```
2. Add an animal:
```bash
===== Zoo Management System Menu =====
1. Create an enclosure
2. Add an animal
3. Add a zookeeper
4. Add a visitor
5. Assign a zookeeper to an enclosure
6. View zoo information
7. Exit
Enter your choice: 2
Enter animal name: Lion
Enter animal age: 5
Enter animal type: Carnivore
Available Enclosures:
1. Lions
Assign Lion to which enclosure (by number): 1
Added Lion to enclosure Lions.
Animal added to enclosure 'Lions' successfully.
```
3. Add a zookeeper:
```bash
===== Zoo Management System Menu =====
1. Create an enclosure
2. Add an animal
3. Add a zookeeper
4. Add a visitor
5. Assign a zookeeper to an enclosure
6. View zoo information
7. Exit
Enter your choice: 3
Enter zookeeper name: Nick
Enter zookeeper expertise: Carnivores
Zookeeper added successfully.
```
4. Add a visitor:
```bash
===== Zoo Management System Menu =====
1. Create an enclosure
2. Add an animal
3. Add a zookeeper
4. Add a visitor
5. Assign a zookeeper to an enclosure
6. View zoo information
7. Exit
Enter your choice: 4
Enter visitor name: Mike
Enter visitor age: 35
Visitor added successfully.
```
5. Assign a zookeeper to an enclosure:
```bash
===== Zoo Management System Menu =====
1. Create an enclosure
2. Add an animal
3. Add a zookeeper
4. Add a visitor
5. Assign a zookeeper to an enclosure
6. View zoo information
7. Exit
Enter your choice: 5
Zookeepers available:
1. Nick
Select a zookeeper (by number): 1
Available enclosures:
1. Lions
Assign zookeeper Nick to which enclosure (by number): 1
Assigned zookeeper Nick to enclosure Lions.
Zookeeper assigned successfully.
```
6. View zoo information:
```bash
===== Zoo Management System Menu =====
1. Create an enclosure
2. Add an animal
3. Add a zookeeper
4. Add a visitor
5. Assign a zookeeper to an enclosure
6. View zoo information
7. Exit
Enter your choice: 6

===== Zoo Information =====
Enclosures:
Enclosure Name: Lions
Habitat: Savannah
Number of Animals: 2
Assigned Zookeeper: Nick

Visitors:
Visitor Name: Mike
Visitor Age: 35
```
7. Exit:
```bash
===== Zoo Management System Menu =====
1. Create an enclosure
2. Add an animal
3. Add a zookeeper
4. Add a visitor
5. Assign a zookeeper to an enclosure
6. View zoo information
7. Exit
Enter your choice: 7
Exiting program. Goodbye!
```