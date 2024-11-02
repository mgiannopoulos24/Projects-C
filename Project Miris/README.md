# Project Miris - Transactional Graph Management System

**Miris** is a command-line tool designed to manage and monitor small financial transactions between users. It uses a directed multi-graph to represent these transactions, where each node represents a user, and each edge represents a transaction with attributes like amount and date.

The application allows users to insert, delete, modify, and query the graph using different commands.

## Project Structure

```console
Project Miris/
│
├── src/                  # Source code directory
│   ├── main.c            # Main application shell
│   └── graph.c           # Graph structure and algorithms
│
├── include/              # Header files
│   └── graph.h           # Function prototypes and data structures
│
├── obj/                  # Compiled object files (generated during build)
│
├── build/                # Output directory for the final executable
│
├── tests/
│   ├── data8-3.txt
│   ├── data15-3.txt
│   ├── data100-4.txt
│   ├── data100-8.txt
│   └── data1000-25.txt   # Sample input files for initializing different graphs
│
└── Makefile              # Makefile for building the project
```

## Usage

To run the **Miris** application, provide an input file with initial transactions and specify an output file to store the current graph:
```console
./build/miris -i input.txt -o graph.txt
```

- `-i input.txt`: Input file containing initial transactions.
- `-o graph.txt`: Output file to store the current graph.


## Supported Commands

Once the application starts, you can interact with the graph using the following commands:

1. **Insert Node(s)** - `i Ni [Nj Nk ...]`

**Description:** Adds one or more nodes to the graph.

**Example:**
```console
miris> i 1 2 3
```

This inserts nodes `1`, `2`, and `3` into the graph.

2. **Insert Edge** - `n Ni Nj sum date`

**Description:** Adds an edge between nodes `Ni` and `Nj`, representing a transaction of `sum` on a specific `date`.

**Example:**
```console
miris> n 1 2 3000 2024-05-01
```

This inserts an edge from node `1` to node `2` with a transaction of `3000` units on `2024-05-01`.

3. **Delete Node(s)** - `d Ni [Nj Nk ...]`

**Description:** Deletes one or more nodes from the graph, along with their associated edges.

**Example:**
```console
miris> d 1 2
```

This deletes nodes `1` and `2` from the graph.

4. **Delete Edge** - `l Ni Nj`

**Description**: Deletes the edge from node `Ni` to node `Nj`.

**Example:**
```console
miris> l 1 2
```

This deletes the edge from node `1` to node `2`.

5. **Modify Edge** - `m Ni Nj old_sum new_sum old_date new_date`

**Description:** Modifies an existing edge between `Ni` and `Nj`, updating the transaction amount and date.

**Example:**
```console
miris> m 1 2 3000 3500 2024-05-01 2024-06-01
```

This modifies the edge from `1` to `2`, changing the amount from `3000` to `3500` and the date from `2024-05-01` to `2024-06-01`.

6. **Find Outgoing Transactions** - `f Ni`

**Description:** Displays all outgoing transactions from node `Ni`.

**Example:**
```console
miris> f 1
```

This shows all transactions that node `1` has sent to other nodes.

7. **Find Incoming Transactions** - `r Ni`

**Description:** Displays all incoming transactions to node `Ni`.

**Example:**
```console
miris> r 2
```

This shows all transactions received by node `2`.

8. **Detect Simple Cycles** - `c Ni`

**Description:** Checks if node `Ni` is part of any simple cycles in the graph.

**Example:**
```console
miris> c 1
```

This checks if node `1` is part of any cycles.

9. **Find Cycles with Minimum Sum** - `f Ni k`

**Description:** Checks if node `Ni` is part of any cycles where each edge in the cycle has at least `k` units.

**Example:**
```console
miris> f 1 1000
```

This checks if node `1` is part of any cycles where each transaction has at least `1000` units.

10. **Trace Flow** - `t Ni m`

**Description:** Traces the flow of transactions starting from node `Ni` with a maximum depth of `m` edges.

**Example:**
```console
miris> t 1 2
```

This traces the flow of transactions starting from node `1`, exploring up to `2` edges deep.

11. **Check Connectivity** - `o Ni Nj`

**Description:** Checks if there is a path from node `Ni` to node `Nj`.

**Example:**
```console
miris> o 1 3
```

This checks if node `1` is connected to node `3` through a path of edges.

12. **Exit the Application** - `e`

**Description:** Exits the application and frees all dynamically allocated memory.

**Example:**
```console
miris> e
```

This exits the application and prints the number of bytes released.

## Build and Run

1. **Build the application:**
```console
make
```
2. **Run the application:**
```console
./build/miris -i input.txt -o graph.txt
```

3. **Enter commands** (e.g.,`i`,`n`,`f`,`r`,`c`, etc.)

## Examples with Execution Times

1. Test file `data8-3.txt`.





## Cleaning Up

To remove all object files and the generated executable:
```console
make clean
```

## Graph Representation in Output File

After running commands, the state of the graph is written to the output file specified. Each node and its outgoing edges are listed, providing a snapshot of the current graph structure.

**Note:** This project is the first assignment for the Operating Systems 2024-25 (K22) course at DIT NKUA.