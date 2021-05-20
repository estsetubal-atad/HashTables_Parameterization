# Hashtables parameterization

This program allows varying the `multipler` and hashtable `tableSize`, when using a *hash function* that looks like:

```cpp
int hashFunction(int key, int tableSize) {
    return k * <multiplier> % tableSize;
}
```

The program simulates the behavior of the *hash function* by evaluating the result using several thousand *random* keys.

Several statistics are presented for analysing occuring *collisions*.