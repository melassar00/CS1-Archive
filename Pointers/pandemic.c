/*  Muhamad Elassar
    CS1 Assignment 1: Pandemic
    9/23/2019                   
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENTMAX 100000

typedef struct Student {
  int symptomCnt; //symptom count for each student
  char name[101]; //student name
  char ** symptoms; //list of symptoms for each student
} Student;

int handleUpdate(Student *, char *, char *);
int initializeStudent(Student * student, int studentCount, char firstWord[], char secondWord[]);
void handleQuery(Student *, char *, char *);
int addSymptom(Student *, char *);

int main(){
  Student * students = calloc(STUDENTMAX, sizeof (Student *));
  // check if allocation fails
  if(students == NULL){
    return -1;
  }

  int n = 0; //number of lines
  char op; //u or q
  char firstWord[101]; //first entry
  char secondWord[101]; //second entry

  scanf("%d", &n);

  for(int i = 0; i < n; i++) {
    scanf(" %c %s %s", &op, firstWord, secondWord); //need leading space to accomodate previous entry's new line
      
    // UPDATE
    if(op == 'u') {
     // check if fails but still calls handleUpdate
      if(handleUpdate(students, firstWord, secondWord) == -1){
        return -1;
      }
    }
      // QUERY
    else if(op == 'q') {
      handleQuery(students, firstWord, secondWord);
    }
  }

  return 0;
}

int handleUpdate(Student * students, char * fword, char * sword) {
  int i;
  // loop through students list
  for (i = 0; i < STUDENTMAX; i++) {
    // if the symptom count is zero then it needs to be initialized
    if (students[i].symptomCnt == 0) {   
      break;
    }
    // if first word matches with the name then add the symptom to the students symptom list
    if (0 == strcmp(fword, students[i].name)) {
      // check if fails
      if(addSymptom(&students[i], sword) == -1){
        return -1;
      }
      return 0;//return because we don't need to initialize
    }
  }

  initializeStudent(students, i, fword, sword); //initialize student since its the student's first update
  return 0;
}

void handleQuery(Student * students, char * fword, char * sword){
  int flagIfFound = 0, numOfStudents = 0; //flag to tell if any entires were found
  // if first word matches "student"
  if(strcmp(fword, "student") == 0){
    int i, j;
    // loop through students list
    for (i = 0; i < STUDENTMAX; i++) {
      if (students[i].symptomCnt == 0) break; // if the students symptom count is zero then break

      // if the second word matches the students name
      if (0 == strcmp(sword, students[i].name)) {
        flagIfFound = 1; //set the flag to indicate something was found
        printf("%d\n", students[i].symptomCnt); // print the symptom count
        for (j = 0; j < students[i].symptomCnt; j++) {
          printf("%s\n", students[i].symptoms[j]); // print each symptom
        }
        break;
      }
    }
  } 

  // if the first word matches "symptom"
  else if (strcmp(fword, "symptom") == 0){
    int i, j;
    // first loop through students list to get the number of students
    for(i=0; i < STUDENTMAX; i++){
      if(students[i].symptomCnt == 0) break; //if symptom count is zero then break

      // loop through symptoms
      for(j=0; j < students[i].symptomCnt; j++){
        // if second word matches the students symptom then increment numOfStudents
        if(0 == strcmp(sword, students[i].symptoms[j])){
          flagIfFound = 1; //something was found so set flag
          numOfStudents++;
        }
      }
    }

    // if the number of students is over 0, then loop again to print students
    if(numOfStudents > 0){
      printf("%d\n", numOfStudents);
      for(i=0; i < STUDENTMAX; i++){
        if(students[i].symptomCnt == 0) break; //if symptom count is zero then break

        // loop through symptoms
        for(j=0; j < students[i].symptomCnt; j++){
          // if second word matches the students symptom then print the name of the student
          if(0 == strcmp(sword, students[i].symptoms[j])){
            printf("%s\n", students[i].name);
          }
        }
      }
    }

  }

  // if nothing was found then print 0
  if(flagIfFound == 0){
    printf("0\n");
  }

}


int initializeStudent(Student * students, int studentCount, char firstWord[], char secondWord[]){

  Student *student = (Student*) malloc(sizeof(Student));
  // check if allocation fails
  if(student == NULL){
    return -1;
  }

  student->symptomCnt = 1; //start with one symptom by default

  student->symptoms = malloc(sizeof(char *) * student->symptomCnt); //allocate enough memory for each symptom
  // check if allocation fails
  if(student->symptoms == NULL){
    return -1;
  }

  student->symptoms[student->symptomCnt - 1] = malloc(sizeof(char) * 101); //allocating space for symptom name
  // check if allocation fails
  if(student->symptoms[student->symptomCnt-1] == NULL){
    return -1;
  }

  strcpy(student->name, firstWord); //copy first entry to student's name

  strcpy(student->symptoms[student->symptomCnt - 1], secondWord); //copy second entry to student's symptom

  students[studentCount] = *student; //adding student to the students list

  return 0;
}

int addSymptom (Student * student, char * sympt) {
  int i;
  char ** newList = malloc(sizeof(char *) * (student->symptomCnt + 1) ); //new temp symptoms list with an extra spot
  // check if allocation fails
  if(newList == NULL){
    return -1;
  }

  char * temp = calloc(101, sizeof(char)); //new temp symptom
  // check if allocation fails
  if(temp == NULL){
    return -1;
  }

  for (i = 0; i < student->symptomCnt; i++) {
    newList[i] = student->symptoms[i]; //copying previous list to new list
  }

  strcpy(temp, sympt); //copy new symptom into temp
  newList[student->symptomCnt] = temp; //assigning new symptom to newList
  student->symptomCnt++; //new symptomCnt is added by one
  free(student->symptoms); //free old list of symptoms
  student->symptoms = newList; //assign temp new list of symptoms to the real list of symptoms

  return 0;
}
