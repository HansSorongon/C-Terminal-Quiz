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

  question_t q;

  FILE *fp;
  char ch;

  fp = fopen("test.txt", "r");

  if (fp != NULL) {
    fscanf(fp, "%[^\n]\n%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]", q.topic, &q.q_number, q.question, q.choice1, q.choice2, q.choice3, q.answer);
  }

  printf("%s\n", q.topic);
  printf("%d\n", q.q_number);
  printf("%s\n", q.question);
  printf("%s\n", q.choice1);
  printf("%s\n", q.choice2);
  printf("%s\n", q.choice3);
  printf("%s\n", q.answer);

  fclose(fp);

  return 0;
}
