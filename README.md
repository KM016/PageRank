# Citation Ranking with a HITS-Style Algorithm

A C++ implementation of an iterative graph-ranking algorithm for a fixed network of seven academic papers.

> University of Bristol Coursework <br>
> Mark awarded: **90/100** <br>
> Date: 03/2024 

## Project overview

The papers and their citations are represented by a directed adjacency matrix $A$, where $A_{ij}=1$ means that paper $i$ cites paper $j$. The program assigns each paper two related scores:

- **Impact score:** higher when the paper is cited by papers with high knowledge scores.
- **Knowledge score:** higher when the paper cites papers with high impact scores.

Although the repository is named `PageRank`, the implemented method is closer to the HITS authority-hub algorithm than to Google's PageRank algorithm. Impact corresponds to an authority-style score and knowledge to a hub-style score.

## Input graph

The coursework uses a fixed example containing seven papers. Its adjacency matrix is

$$
A = \begin{pmatrix}
0&1&1&0&0&0&0\\
0&0&1&0&0&0&0\\
0&0&0&0&0&0&0\\
0&0&1&0&1&1&0\\
1&1&1&0&0&1&0\\
1&0&1&0&0&0&0\\
1&1&1&1&1&1&0
\end{pmatrix}.
$$

A row describes the papers cited by one paper; a column describes the papers that cite it. Self-citations are excluded because the diagonal entries are zero.

## Algorithm

Starting with both score vectors set to one, the program repeatedly applies

$$
\alpha = A^T\beta,
\qquad
\beta = A\alpha,
$$

where $\alpha$ contains the impact scores and $\beta$ contains the knowledge scores. Both vectors are normalised by their Euclidean norms after each update. Iteration stops when the convergence condition is met or after 100 iterations.

The complete procedure is:

1. initialise all impact and knowledge scores to `1`;
2. update each impact score from the knowledge scores of papers citing it;
3. update each knowledge score from the impact scores of papers it cites;
4. normalise both vectors using the Euclidean norm;
5. compare the new scores with the previous iteration; and
6. continue until the tolerance of $10^{-6}$ is reached or the iteration cap is hit.

## Program structure

The source defines two classes:

- `matrix` owns the flattened integer matrix, provides row and column dimensions, reads and writes individual elements, prints the matrix and releases the allocated memory.
- `algorithm` builds the citation example, performs the iterative score updates and prints the final result.

`main()` constructs a 7-by-7 matrix, uses its dimensions to initialise the algorithm and then calls `run()`.

For the hard-coded seven-paper example, the program identifies:

- **Paper 3** as having the highest impact score; and
- **Paper 7** as having the highest knowledge score.

The complete saved result is:

| Paper | Impact | Knowledge |
| ---: | ---: | ---: |
| 1 | 0.39853266 | 0.28485625 |
| 2 | 0.39853266 | 0.17429382 |
| 3 | 0.62825841 | 0.00000000 |
| 4 | 0.17734066 | 0.36891782 |
| 5 | 0.27968720 | 0.51245081 |
| 6 | 0.42185326 | 0.28485625 |
| 7 | 0.00000000 | 0.63924120 |

## Building and running

The project requires a C++11-compatible compiler.

```bash
g++ -std=c++11 -O2 PageRank.cpp -o pagerank
./pagerank
```

The program prints the number of iterations followed by the two scores for each paper.

## Repository contents

```text
.
├── PageRank.cpp    # Matrix representation and ranking algorithm
└── README.md
```

## Scope and limitations

This is a coursework implementation for one fixed 7-by-7 adjacency matrix, not a general graph-ranking library. The matrix and vector sizes are hard-coded, input is not read from a file, and the convergence logic is implemented manually. The program is best read as a compact demonstration of iterative matrix-based ranking and C++ memory management.
