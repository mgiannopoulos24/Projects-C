# Graph Algorithms Implementation
This project provides implementations of several graph algorithms in C, using a graph representation defined in graph.h. The algorithms implemented include Prim's algorithm, Boruvka's algorithm, Kruskal's algorithm, Dijkstra's algorithm, and Dial's algorithm. These algorithms are fundamental in graph theory and are used for various graph-related problems such as finding minimum spanning trees, shortest paths, and more.

## Files
- `graph.h`: Header file defining the graph structure and basic operations.
- `prim.c`: Implementation of Prim's algorithm for finding Minimum Spanning Tree (MST).
- `boruvka.c`: Implementation of Boruvka's algorithm for finding MST.
- `kruskal.c`: Implementation of Kruskal's algorithm for finding MST.
- `dijkstra.c`: Implementation of Dijkstra's algorithm for finding shortest paths from a source vertex.
- `dial.c`: Implementation of Dial's algorithm for finding shortest paths in networks with small integer weights.
- `union_find.h`, `union_find.c`: Header and implementation files for the Union-Find data structure used in Kruskal's and Boruvka's algorithms.
## Usage
Compilation
Compile the project using `make`:

```bash
User@Github:~$ make dijkstra
User@Github:~$ make prim
User@Github:~$ make kruskal
User@Github:~$ make dial
User@Github:~$ make boruvka
```

## Running Algorithms
Each algorithm executable takes its input and demonstrates its functionality. For example:

```bash
./build/prim
./build/boruvka
./build/kruskal
./build/dijkstra
./build/dial
```
## Input Format
The algorithms expect input in a specific format depending on the algorithm (e.g., number of vertices, edges with weights). Modify the input directly in the source code as needed.

## Output
The output of each algorithm typically includes the results of their respective computations, such as the Minimum Spanning Tree (MST) for Prim's, Boruvka's, and Kruskal's algorithms, or shortest paths for Dijkstra's and Dial's algorithms.

## Example

1. Djikstra:
```bash
User@Github:~$ ./build/dijkstra 
Graph:
Graph with 5 vertices:
Vertex 1 -> (2, 4) (3, 2)
Vertex 2 -> (1, 4) (3, 5) (4, 10)
Vertex 3 -> (1, 2) (2, 5) (4, 3)
Vertex 4 -> (2, 10) (3, 3) (5, 7)
Vertex 5 -> (4, 7)
Shortest distances from vertex 1:
Vertex 1: 0
Vertex 2: 4
Vertex 3: 2
Vertex 4: 5
Vertex 5: 12
```
2. Prim:
```bash
User@Github:~$ ./build/prim 
Graph:
Graph with 5 vertices:
Vertex 1 -> (2, 4) (3, 2)
Vertex 2 -> (1, 4) (3, 5) (4, 10)
Vertex 3 -> (1, 2) (2, 5) (4, 3)
Vertex 4 -> (2, 10) (3, 3) (5, 7)
Vertex 5 -> (4, 7)
Minimum Spanning Tree (MST) from vertex 1:
Edge 1 - 2: 4
Edge 1 - 3: 2
Edge 3 - 4: 3
Edge 4 - 5: 7
```
3. Kruskal:
```bash
User@Github:~$ ./build/kruskal 
Graph:
Graph with 5 vertices:
Vertex 1 -> (2, 4) (3, 2)
Vertex 2 -> (1, 4) (3, 5) (4, 10)
Vertex 3 -> (1, 2) (2, 5) (4, 3)
Vertex 4 -> (2, 10) (3, 3) (5, 7)
Vertex 5 -> (4, 7)
Minimum Spanning Tree (MST):
Edge 1 - 2: 4
Edge 1 - 3: 2
Edge 3 - 4: 3
Edge 4 - 5: 7
```
4. Dial:
```bash
User@Github:~$ ./build/dial 
Graph:
Graph with 5 vertices:
Vertex 1 -> (2, 1) (3, 4)
Vertex 2 -> (1, 1) (3, 2) (4, 5)
Vertex 3 -> (1, 4) (2, 2) (4, 1) (5, 3)
Vertex 4 -> (2, 5) (3, 1) (5, 7)
Vertex 5 -> (3, 3) (4, 7)
Shortest distances from vertex 1:
Vertex 1: 0
Vertex 2: 1
Vertex 3: 3
Vertex 4: 4
Vertex 5: 6
```
5. Boruvka:
```bash
User@Github:~$ ./build/boruvka
Graph:
Graph with 5 vertices:
Vertex 1 -> (2, 1) (3, 4)
Vertex 2 -> (1, 1) (3, 2) (4, 5)
Vertex 3 -> (1, 4) (2, 2) (4, 1) (5, 3)
Vertex 4 -> (2, 5) (3, 1) (5, 7)
Vertex 5 -> (3, 3) (4, 7)
Minimum Spanning Tree (MST):
Edge 3 - 2: 2
Edge 4 - 3: 1
Edge 0 - 4: 0
Edge 3 - 5: 3
```