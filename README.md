## SEMB-DFS

## Site para compilar os códigos: https://www.tutorialspoint.com/compile_c_online.php

## Gerador aleatório de relações : 
```c
#include <stdio.h>
#include <time.h>

int main()
{
    srand(time(NULL));   // Initialization, should only be called once.
    for (int i = 0; i < 1001; i++) {
        int randomOne = rand() % 1000;
        int randomTwo = rand() % 1000;
        printf("addEdge(%d, %d);\n", randomOne, randomTwo);    
    }

    return 0;
}
```
