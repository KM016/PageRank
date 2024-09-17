# PageRank

Date: 03/2024 <br>
University Project

# The Task

The objective of this project is to rank academic papers based on their bibliographies, i.e., how often they cite other papers and how often they are cited by others. This ranking is performed using two key scores:

- **Impact Score:** A measure of how many other papers cite a given paper.
- **Knowledge Score:** A measure of how many papers the given paper cites.

To achieve this, we use an iterative algorithm that computes both the impact and knowledge scores based on citation data, represented as a graph.

## Input

The input for this project is an adjacency matrix `A`, which represents citations between papers:

- `A[i, j] = 1` if paper `i` cites paper `j`.
- `A[i, j] = 0` if paper `i` does not cite paper `j`.
- Self-citations are not allowed (`A[i, i] = 0`).

For example, the following adjacency matrix represents a set of 7 papers:

$$
A = \begin{pmatrix}
0 & 1 & 1 & 0 & 0 & 0 & 0 \\
0 & 0 & 1 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 1 & 0 & 1 & 1 & 0 \\
1 & 1 & 1 & 0 & 0 & 1 & 0 \\
1 & 0 & 1 & 0 & 0 & 0 & 0 \\
1 & 1 & 1 & 1 & 1 & 1 & 0 \\
\end{pmatrix}
$$

## Output

The algorithm will output two ranking scores for each paper:

- **Impact Score:** Reflects how often the paper is cited.
- **Knowledge Score:** Reflects how often the paper cites others.


# The Algorithm

The algorithm used to compute the ranking scores is inspired by HITS (Hyperlink-Induced Topic Search), a well-known algorithm in information retrieval. The steps of the algorithm are as follows:

1. **Initialization:**  
   Both the impact and knowledge scores are initialized to 1 for all papers. These scores are stored in vectors \(\alpha\) (impact) and \(\beta\) (knowledge).

2. **Iterative Updates:** The algorithm iteratively updates the impact and knowledge scores as follows:

   - **Impact Score Update:**  
     The impact score of a paper is updated using the knowledge scores of the papers that cite it:
     $\alpha_i = \sum_{j=1}^n A_{j,i} \cdot \beta_j$

   - **Knowledge Score Update:**  
     The knowledge score of a paper is updated using the impact scores of the papers it cites:
     $\beta_i = \sum_{j=1}^n A_{i,j} \cdot \alpha_j$

3. **Normalization:** After each update, the impact and knowledge score vectors are normalized using the Euclidean norm to prevent unbounded growth:
   $\alpha \leftarrow \frac{\alpha}{\|\alpha\|}, \quad \beta \leftarrow \frac{\beta}{\|\beta\|}$

4. **Convergence Check:** The algorithm continues updating the scores until the maximum change between iterations is smaller than a small positive constant $\epsilon$ (e.g., \$\epsilon = 10^{-6}\$) or a maximum number of iterations $M$ (e.g., $M = 100$) is reached.
