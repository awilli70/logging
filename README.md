# Logging Problem Demo

Files:

* heavy.c - creates a heavy simulated logging load.
```
USAGE:   ./heavy [-r repetitions] [-s write_size]

OPTIONS: -r: number of total writes performed (default 200)
         -s: size of writes, in KB (default 64)
NOTES:   repetitions and write_size must be greater than 0
```

* standard.c - to be created
* random.c - defines some general helper functions for random buffer allocation

Usage:

Compile with `make`, run with ./heavy or ./standard
