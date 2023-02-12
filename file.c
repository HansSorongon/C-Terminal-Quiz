#include <stdio.h>
#include <string.h>

typedef struct {
  char topic[20];
  int q_number;
  char question[150];
  char choice1[30];
  char choice2[30];
  char choice3[30];
  char answer[30];
} question_t;

int main() {

  question_t my_question;
  strcpy(my_question.topic, "Geology");
  my_question.q_number = 1;
  strcpy(my_question.question, "What is the choice?");
  strcpy(my_question.choice1, "Choice 1");
  strcpy(my_question.choice2, "Choice 2");
  strcpy(my_question.choice3, "Change 3");
  strcpy(my_question.answer, "Choice 1");

  FILE *fptr = fopen("new.txt", "w+");
  char format[] = "%s\n%d\n%s\n%s\n%s\n%s\n%s\n"; // lmfao

  if (fptr != NULL) {
    fprintf(fptr, format, my_question.topic, my_question.q_number, my_question.question,
          my_question.choice1, my_question.choice2, my_question.choice3, my_question.answer);
  }

  fclose(fptr);

  return 0;
}
