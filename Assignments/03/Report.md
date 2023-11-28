# Results for Assignment 03

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Changes |
| :-----: | ---- | ------- |
| 01 | 4.8 minutes | Initial version - no changes |
| 02 | 44.75 seconds | Implemented basic threading for each connection. |
| 03 | 1m8.267s | mostly same code, but for the mutexes, I found that using the plain mutex.lock and mutex.unlock statements worked better for this data set. |

## Profiling Analysis

### Initial Review

After running into the odd bad alloc error when using Chrome, switching to 
Incognito mode or another browser like Safari seemed to resolve this pesky error. 
Initially, the site took forever to load all of the images, but after implementing some 
pretty straightforwad threading in server.cpp, things started to speed up. This was due to 
adding a thread to every new connection made during the loading sequence. I am working on 
adding a ring buffer to speed things up even more, but I am not sure I will have enough time 
to complete this addition.