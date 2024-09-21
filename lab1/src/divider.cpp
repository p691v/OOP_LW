#include "../include/divider.h"

int divider(int a, int b){
    if (a < 1 || b < 1)
        return -1;
    return (a - 1) * b + (b - 1) * a;
}
