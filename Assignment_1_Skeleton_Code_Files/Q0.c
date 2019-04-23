/* CS261- Assignment 1 - Q. 0*/
/* Name: Genevieve Conty
 * Date: 04/15/2019
 * Solution description: HW Solution - Q0
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){

    /*Print the value and address of the integer pointed to by iptr*/
    printf("from fooA: value of iptr: %d\n", *iptr);
    printf("from fooA: address of iptr: %p\n", &iptr);

    /*Increment the value of the integer pointed to by iptr by 5*/
    (*iptr) += 5;
    
    /*Print the address of iptr itself*/
    printf("from fooA: Address of iptr: %p\n", &iptr);

    /*Dummy variable, ignore the warning*/
    int c=5;  
}


void fooB(int* jptr){
  
    /*Print the value and address of the integer pointed to by jptr*/
    printf("from fooB: Value of jptr: %d\n", *jptr);
    printf("from fooB: Address of jptr: %p\n", &jptr);

    /*Decrement the address by 1 pointed to by jptr using jptr */
    (*jptr)--;
      
    /*Print the address of jptr itself*/
    printf("from fooB: Address of jptr: %p\n", &jptr);
}


int main(){
    
    /*Declare an integer x and initialize it randomly to a value in [0,10] */
    int x = rand() % 10 + 1;

    /*Print the value and address of x*/
    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", &x);

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*Print the value of x*/
    printf("fooA(): Value of x: %d\n", x);

    /*Call fooB() with the address of x*/
    fooB(&x);

    /*Print the value and address of x*/
    printf("fooB(): Value of x: %d\n", x);
    printf("fooB(): Address of x: %p\n", &x);

    // Are the value and address of x different than 
    // the value and address that were printed 
    // before the call to fooB(..)? Why or why not?
    // The value and address of x printed after fooB() 
    // are different from the value and address printed before. 
    // This is because of the dummy variable at the end of fooA()
    
    return 0;
}


