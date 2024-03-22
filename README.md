# Assignment 2: Multithreaded Matrix Multiplication

**READ ALL DIRECTIONS AND HINTS BEFORE STARTING!**

_(Note that this problem corresponds to Project 2 on page 170 of the textbook 7th ed. with some minor changes)._

**Important:** you must use the `pthread` library in c in this assignment.

  
Given two matrices, `A` and `B`, where matrix `A` contains `m` rows and `k` columns and matrix `B` contains `k` rows and `n` columns, we can compute the product of `A` and `B` as matrix `C`, where `C` contains `m` rows and `n` columns. The entry in matrix `C` for row `i`, column `j` is the sum of the products of the elements for row `i` in matrix `A` and column `j` in matrix `B`:

$$C_{i,j} = \sum_{n=1}^k A_{i,n} \cdot B_{n,j}$$

For this assignment, you will create a multi-threaded matrix multiplier. You will create _worker threads_ to handle each cell (i.e., every cell's value in the resulting matrix `C` is computed by a separate thread). You should create `m x n` worker threads (since that's how many cells there are in the resulting matrix!).

**Input:** You will read the matrix data from a file. The file name should be supplied as a terminal argument (e.g., ./matrix.o matrix1.in). Our input files use the following specification:

```
m k n  
p1  
p2  
p3...  
q1  
q2  
q3...
``` 

The first line has values `m`, `k`, and `n`. Here is the meaning of these values:

*   Matrix `A`: `m` rows x `k` columns
*   Matrix `B`: `k` rows x `n` columns

`p1, p2, p3...` correspond to **_double-precision values_** in row-major order for Matrix `A`. `q1, q2, q3...` correspond to **_double-precision values_** in row-major order for Matrix `B`.

## Example 

Suppose our file contains

```
3 2 3  
1  
4  
2  
5  
3  
6  
8  
7  
6  
5  
4  
3
```

This corresponds to two matrices, $`m_1 = \begin{bmatrix}
1, 4\\
2, 5\\
3,6
\end{bmatrix}`$, $`m_2 =\begin{bmatrix} 8, 7, 6\\5,4,3\end{bmatrix}`$, which has a resulting product of 

```math
C = 
\begin{bmatrix}
1\cdot 8 + 4\cdot 5 , 1 \cdot 7 + 4 \cdot 4 , 1\cdot 6 + 4\cdot 3\\
2\cdot 8 + 5 \cdot 5 , 2\cdot 7 + 5\cdot 4 , 2\cdot 6 + 5\cdot 3\\
3\cdot 8 + 6\cdot 5 , 3\cdot 7 + 6\cdot 4 , 3\cdot 6+6\cdot3
\end{bmatrix} = \begin{bmatrix}
28, 23, 18\\
41,34,27\\
54,45,36
\end{bmatrix}
```

## Output:

You should output the resulting matrix to standard out in the same format as a normal matrix (i.e., in row-major order with a newline separating rows):
```
28 23 18  
41 34 27  
54 45 36
```
It is perfectly fine if the numbers have decimals after them e.g., `28.00000`. Since we are reading and parsing doubles, it makes sense for the output to also have decimals (though, if you want to truncate the trailing zeroes for integer values, that's also fine!).

## Submission:
When your submission is ready, commit and sync all changes and create a tag in that version named **submission**.

Your project will be graded based on the _submission_ tagged version.

## Notes:

**1\. If your solution is not multi-threaded, you will receive a zero.**

**2\. Uncompilable code will receive a zero.**

**3\. When submitting your assignment, please don't put your name in the code or in the file name(s). Instead, put your student ID.**

4\. Your code should have no memory leaks of any kind.

5\. Don't over-complicate the solution. My solution is ~200 lines of code across multiple files with comments and error-checking (which you need to do).

6\. Use proper style, comments, and error-checking! Again, this is a 400/600-level course, and your code should reflect this.

## Hints:

1\. Test your program with other matrices! I will be using my own private test cases to see if your submission works. You can assume that all test cases will be valid (i.e., you don't have to check if there's a string instead of a number... etc.). In addition, contrary to what I had here previously, all matrices will be multipliable, so you don't need to check otherwise.

2\. Here's [a link](https://matrix.reshish.com/multiplication.php) to a matrix multiplication calculator to verify your program output.
