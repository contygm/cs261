/* CS261- Assignment 1 - Q.2*/
/* Name: Genevieve Conty
 * Date: 04/15/2019
 * Solution description: HW Solution - Q.2
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
    printf("from foo: Value of x: %d\n", x);
    printf("from foo: Value of y: %d\n", y);
    printf("from foo: Value of z: %d\n", z);

    /*Print the value returned by foo*/
    printf("Value of foo result: %d\n", result);

    // A. Is the return value different than the value of 
    // integer z? Why or why not?
    // Yes. foo() decrements a copy of z so the return 
    // value and z are different
    //
    // B. Are the values of integers x and y different before 
    // and after calling thefunction foo(..)? Why or why not?
    // No, foo() doens't manupulate those values
    //

    return 0;
}
    
    


