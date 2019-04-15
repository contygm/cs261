/* CS261- Assignment 1 - Q.2*/
/* Name:
 * Date:
 * Solution description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
    
    // classic swap
    int *temp = a;
    a = b;
    b = temp;

    /*Decrement the value of integer variable c*/
    c--;

    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand() % 10 + 1;
    int y = rand() % 10 + 1;
    int z = rand() % 10 + 1;

    /*Print the values of x, y and z*/
    printf("Value of x: %d\n", x);
    printf("Value of y: %d\n", y);
    printf("Value of z: %d\n", z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
    int result = foo(&x, &y, z);

    /*Print the values of x, y and z*/
    printf("foo: Value of x: %d\n", x);
    printf("foo: Value of y: %d\n", y);
    printf("foo: Value of z: %d\n", z);

    /*Print the value returned by foo*/
    printf("Value of foo result: %d\n", result);
    
    return 0;
}
    
    


