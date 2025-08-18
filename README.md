# Hoeksema Hash Browns: building a hash map from scratch

- [Hash Map](#hash-map)
- [Stress Test](#stress-test)
- [Installation](#installation)
- [Usage](#usage)

# Hash Map
The following data structures are available by using the hash.h file:
- hash_table

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

# Usage
```c
#include  "hash.h"

hash_table_t table = hash_create(16);
hash_insert(table, "favorite_drink", "Waterloo");
char* value = (char*)hash_get(table, "favorite_drink");
hash_destroy(table);
```
