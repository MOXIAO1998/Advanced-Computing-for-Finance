# Advanced-Computing-for-Finance
1. Explain the key differences between pointers and references in C++. When would you choose to use a pointer over a reference, and vice versa, in the context of implementing numerical algorithms?
    
```
A pointer stores an address, can be reassigned, can be nullptr, and supports pointer arithmetic. A reference is an alias to an existing object,
must be initialized, cannot be null in normal use, and cannot be reseated.

In numerical algorithms, pointers are more useful for raw arrays, dynamic memory, and low-level kernels. References are better when a function 
always needs a valid object and no pointer arithmetic is required. In this project, pointers were the better choice because matrices and vectors 
were stored as contiguous 1D arrays.
```
2. How does the row-major and column-major storage order of matrices affect memory access patterns and cache locality during matrix-vector and matrix-matrix multiplication? Provide specific examples from your implementations and benchmarking results.

```
Row-major stores rows contiguously, while column-major stores columns contiguously. 
This changes memory access patterns and cache behavior.

In matrix-vector multiplication, both versions performed similarly when indexing matched 
the storage layout. Under -O3 at n=512, row-major was about 0.3339 ms and column-major was 
about 0.3372 ms.

In matrix-matrix multiplication, the effect was much larger. The naive version 
accesses B[k][j] as a strided column in row-major storage, while the transposed-B 
version accesses (B^T)[j][k] contiguously. At n=256 under -O3, naive was 18.1444 
ms and transposed B was 8.9968 ms.
```

3. Describe how CPU caches work (L1, L2, L3) and explain the concepts of temporal and spatial locality. How did you try to exploit these concepts in your optimizations?

```
L1 cache is the smallest and fastest, L2 is larger and slower, and L3 is larger again 
and usually shared across cores.

Spatial locality means nearby memory is likely to be used soon. Temporal 
locality means recently used data is likely to be reused soon.

We exploited these ideas by matching indexing to storage order, using 
transposed B to make inner-loop access contiguous, and using blocking 
to improve cache reuse. The stride benchmark also showed locality clearly: 
under -O3, runtime stayed near 21–22 ms for strides 1–8, but increased sharply 
for 16–64.
```


4. What is memory alignment, and why is it important for performance? Did you observe a significant performance difference between aligned and unaligned memory in your experiments? Explain your findings.

```
Memory alignment means placing data at addresses that match a chosen boundary, such as 64 bytes. 
It can help cache-line usage and vectorized loads/stores.

In our experiments, alignment alone did not make a large difference. For example, at n=512 under -O3, 
aligned and unaligned matrix-vector runtimes were almost identical, and the same was true for naive 
matrix-matrix multiplication. This suggests that access pattern and cache locality mattered more than alignment alone.

```

5. Discuss the role of compiler optimizations (like inlining) in achieving high performance. How did the optimization level affect the performance of your baseline and optimized implementations? What are the potential drawbacks of aggressive optimization?

```
Compiler optimization had a much larger effect than manual inlining in this project. '
Moving from -O0 to -O3 gave large speedups. For example, row-major matrix-vector multiplication at 
n=512 improved from 0.9227 ms to 0.3339 ms, and naive matrix-matrix multiplication at n=256 improved 
from 58.5094 ms to 18.1444 ms.

Inlining can help very small helper functions, but our main cost came from the innermost arithmetic loops. 
A drawback of aggressive optimization is that debugging becomes harder.
```

6. Based on your profiling experience, what were the main performance bottlenecks in your initial implementations? How did your profiling results guide your optimization efforts?
```
Profiling showed that the main bottleneck was the matrix-matrix multiplication kernel itself. 
In the naive run, multiply_mm_naive(...) took about 99.7% of total runtime with about 376 ms 
self time. In the transposed-B run, multiply_mm_transposed_b(...) took essentially all runtime with about 205 ms self time.

This guided us toward cache-focused optimizations inside the kernel. The final blocked implementation 
reduced runtime at n=256 from 58.6028 ms to 26.7674 ms, a 2.19× speedup.
```


7. Reflect on the teamwork aspect of this assignment. How did dividing the initial implementation tasks and then collaborating on analysis and optimization work? What were the challenges and benefits of this approach?
```
Dividing the baseline implementations made the project more efficient, because 
different kernels could be built in parallel. The main benefit was speed and 
specialization. The main challenge was making sure everyone used consistent 
conventions for indexing, testing, and benchmarking.

Overall, the division of labor worked well: implementation was faster, and the 
later analysis and optimization were stronger because the team could compare 
multiple approaches together.
```