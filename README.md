Age aggregator
==============

Takes a file containing id/age tuples, and outputs distinct ages, with a count
of records belonging to that age.  For example, given the file:

```
123,12
321,44
312,13
546,44
```

output would be the following:

```
Age      Count
===      =====
12       1
13       1
44       2
```

genages.sh
----------
Quick script to generate the random records.  Try `genages.sh -h` for help.

ageagg.sh
---------
Dirty bash script to aggregate using the CLI pipeline.  Usage:
```
./ageagg.sh <filename>
```

