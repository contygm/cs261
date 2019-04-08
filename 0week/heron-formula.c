#include <math.h>
#include <stdio.h>

int semiPerimeter(int a, int b, int c) {
    int numerator = a + b + c;
    
    return numerator / 2;
}

int area() {
    int a = 3;
    int b = 4; 
    int c = 5;

    int s = semiPerimeter(a, b, c);

    int firstTerm = s - a;
    int secondTerm = s - b;
    int thirdTerm = s - c;

    int root = s * firstTerm * secondTerm * thirdTerm;

    return sqrt(root);
}