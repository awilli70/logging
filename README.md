# Logging Problem Demo

Files:

* heavy.c - creates a heavy simulated logging load.

```bash
USAGE:   ./heavy [-r repetitions] [-s write_size]

OPTIONS: -r: number of total writes performed (default 200)
         -s: size of writes, in KB (default 64)
NOTES:   repetitions and write_size must be greater than 0
```

* standard - victim workload, plays Conway's Game of Life and outputs each
step to disk for a specified duration. Will output total iterations after 
completion

```bash
USAGE: ./small <duration>
```

* random.c - defines some general helper functions for random buffer allocation
* cleanup - removes files created by heavy.c

Usage:

Compile large workload with `make`, run with ./heavy

Compile small workload with `chmod u+x small`, run with ./small

Cleanup: `chmod u+x cleanup`, run with ./cleanup
