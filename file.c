#include <stdio.h>
#include <string.h>

typedef struct {
  char topic[40];
} question_t;

void insert_here(question_t *question) {
  strcpy(question[0].topic, "Hello");
}

int main() {

  question_t questions[20];
  insert_here(questions);

  printf("%s", questions[0].topic);

}
