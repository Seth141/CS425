# Results for Assignment 01

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Memory (KB) | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| 01 | 9.56s | &mdash; | 1041336 | Initial version - no changes |
| 02 | 2.20s | 4.35x | 1041336 | Used the -03 optimization flag for speedup |
| 03 | 2.18s | 4.39x| 1041320 | Used the -03 and -funroll-all-loops flags |
| 04 | 1.91s | 5.01x| 1041324 | Used the -0fast flag |

## Profiling Analysis

### Initial Review

It is interesting to see how the optimization flags 
can really speed up a program while only increasing 
memory usage slightly. I read that the -O3 flag can 
lose precision if used, so I am thinking it is wise 
to use the -0fast flag since it gives the best time 
and most likely does not lose precision from what I 
read.