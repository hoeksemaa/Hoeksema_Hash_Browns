# Hoeksema Hash Browns: building a hash map from scratch

- [Hash Map](#hash-map)
- [Stress Test](#stress-test)
- [Installation](#installation)

# Hash Map
The following data structures are available by using the hash.h file:
- hash_table
- hash_node

The following functions are available by using the hash.h file:
- hash_create()
- hash_destroy()
- hash_insert()
- hash_get()
- hash_delete()
- hash_size()

This hash map uses chaining to resolve the collision problem. This is less performant but simpler to implement.

# Stress Test
The stress test inserts random numerical key/value pairs and measures the time it takes to insert a given number of keys. The size of the hash table is slightly less than the keys inserted because the random generation may output the same key twice.  

As table size grows, insertion speed is roughly constant while resizes double in time cost each time. As table capacity is also doubling each resize, this time cost is expected.

# Installation
Compile:
```make```

Remove executables:
```make clean```

Execute unit tests:
```./test```

Execute stress test:
```./stress_test```
