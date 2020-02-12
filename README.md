### Project Description
-  In C, implement a variant of the memcpy function named “bitcpy.”  The function should behave the same as the memcpy function, except the third parameter specifies the number of bits (not bytes) to copy, and this number need not fit evenly into some number of bytes (indicate with comments in your code how you handle the case when this happens).

### Memcpy Limitations
- 1) Doesn't check for overflow or \0
- 2) Undeterministic behavior if source and destination addresses overlap

### Final Solution Notes
- Handles remaining bits of the final byte by padding with zeros
- Compile with: gcc -o main main.c -lm
