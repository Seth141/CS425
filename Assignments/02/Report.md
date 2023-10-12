# Results for Assignment 02

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Memory (KB) | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| 01 | >1 hour | &mdash; | &mdash | Initial version - no changes |
| 02 | 1m8.486s | >60x | &mdash | implemented all threading logic, dynamic scheduling, and std::unique_lock for the mutexes.|
| 03 | 1m8.267s | 1.0032x| &mdash | mostly same code, but for the mutexes, I found that using the plain mutex.lock and mutex.unlock statements worked better for this data set. |

## Profiling Analysis

### Initial Review

This project's final data set really shows that using multi-threading, dynamic scheduling, and optimization flags can yield a real night and day difference! I let the initial, serial version of program run on BLUE for over an hour before hitting control-c. Seeing a 60x speedup was pretty eye-opening. 