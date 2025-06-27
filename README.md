# Shortest Path Algorithms in C (Dijkstra & Bellman-Ford)
This project implements two classic shortest path algorithms in C:

- **Dijkstra's Algorithm**
- **Bellman-Ford Algorithm**

Both algorithms work on directed graphs and take input from a file in adjacency list format.

---

##  Input File: `graf.txt`

Example content:
4
A-B-3
A-C-1
B-D-7
C-D-2

- The first line indicates the number of nodes.
- Each subsequent line defines an edge in the format: `Source-Destination-Weight`

---

##  Features

- Adjacency list representation of graph
- File-based graph initialization
- Detects negative-weight cycles (Bellman-Ford)
- Clear output of distances and paths
- Clean memory management

---

##  How to Compile and Run

```bash
gcc algoritmalar.c -o algoritmalar
./algoritmalar
