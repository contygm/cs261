/* CS261- Assignment 1 - Q.1*/
/* Name: Genevieve Conty
 * Date: 04/15/2019
 * Solution description: HW Solution - Q.1
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *allStudents = malloc(sizeof(struct student) * 10);

     /*Return the pointer*/
     return allStudents;
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
     IDs being between 1 and 10, scores between 0 and 100
     
     https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
     From Wikipedia for Fischer/Yates shuffle:
          To shuffle an array a of n elements (indices 0..n-1):
               for i from n−1 downto 1 do
               j ← random integer such that 0 ≤ j ≤ i
               exchange a[j] and a[i]
     */

     int allIds[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
     
     // shuffle allIds[] with Fischer/Yates shuffle
     for (int i = 9; i > 0; i--) {
          // get random int from 0 - i
          int j = rand() % (i + 1);
          
          // classic swap
          int temp = allIds[j];
          allIds[j] = allIds[i];
          allIds[i] = temp;
     }
     
     // assign students ID and score
     for(int i = 0; i < 10; i++) {
          students[i].id = allIds[i];
          students[i].score = rand() % 100 + 1;
     }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
     ID1 Score1
     ID2 score2
     ID3 score3
     ...
     ID10 score10 */
     
     // print headers
     printf("ID \t SCORE \n");
     printf("------------------------ \n");

     // print all ids and scores
     for(int i = 0; i < 10; i++) {
          printf("%d \t %d \n", students[i].id, students[i].score);
     }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/

     // declare needed variables
     int min = 100;
     int max, avg = 0;

     // go through all students
     for(int i = 0; i < 10; i++) {
          // minimum: check if score is new min
          if(students[i].score < min) {
               min = students[i].score;
          }
          
          // maximum: check if score is new max
          if (students[i].score > max) {
               max = students[i].score;
          }
     
          // avg: calculate total score of all students
          avg += students[i].score;
     }

     // divide total scores by # of students
     avg /= 10;

     // print min, max, avg
     printf("Minimum score: %d\n", min);
     printf("Maximum score: %d\n", max);
     printf("Average score: %d\n", avg);

}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     if (stud != NULL)
     {
          free(stud);
     }
}

int main(){
     struct student* stud = NULL;

     /*Call allocate*/
     stud = allocate();

     /*Call generate*/
     generate(stud);

     /*Call output*/
     output(stud);

     /*Call summary*/
     summary(stud);

     /*Call deallocate*/
     deallocate(stud);

     return 0;
}

