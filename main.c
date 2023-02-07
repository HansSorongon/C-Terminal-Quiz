#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//
// Essential
//  Question File Handler:
//  Admin Login: x
//  Exit: x
//  Main Menu: x
//  Quiz Loop:
//

// main structure for questions
typedef struct {
  char topic[20];
  int q_number;
  char question[150];
  char choice1[30];
  char choice2[30];
  char choice3[30];
  char answer[30];
} question_t;

void delay(int seconds) {
    int ms = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + ms); // run a while loop for seconds seconds.
}

void handle_cursor(int *select, int max, int *selected) {
  switch(getch()) {
    case 'j': case 'J':
      if (*select < max) {
        *select = *select + 1;
      }
      break;
    case 'k': case 'K':
      if (*select > 1) {
        *select = *select - 1;
      }
      break;
    case 'd': case 'D':
      *selected = *select;
      break;
  }
}

// returns 1 if match, 0 if not match
int prompt_password() {
  char inp[30] = {}; // input stack
  char ch;
  char password[30] = "admin123";

  printf("Password: ");
  while (ch != 13) { // while not enter
    ch = getch();
    system("cls");
    printf("Password: ");

    if (ch == 8 && strlen(inp) > 0) {
      inp[strlen(inp)] = '\0'; // set last to null
    } else if (ch != 8 && ch != 13 && strlen(inp) < 30) { // if not bspace or not enter
      strncat(inp, &ch, 1); // append current ch to end
    }
    for (int i = 0; i < strlen(inp); i++) { // print *
      printf("*");
    }
  }
  return !abs(strcmp(inp, password));
}

void manage_data() {

  system("cls");

  // ask for password before continuing use return value to determine if should
  // let in
  if (prompt_password()) {
    printf("\n\n\t  Succesfully logged in!");
    delay(1);

    int select = 1;
    int selected = 0;

    while (!selected) {
      system("cls");
      printf("\n\tWelcome admin, what would you like to do?\n");

      printf("\n\t%c - Add questions", (select == 1) ? '>' : ' ');
      printf("\n\t%c - Remove questions", (select == 2) ? '>' : ' ');
      printf("\n\t%c - Back", (select == 3) ? '>' : ' ');

      handle_cursor(&select, 3, &selected);
      if (selected) {
        switch(select) {
          case 1:
            selected = 0; // continue the loop on this page
            printf("A");
            break;
          case 2:
            selected = 0;
            printf("B");
            break;
          case 3:
            break;
        }
      }
    }

  } else {
    printf("\n\n\t  Wrong password! Please try again.");
    delay(1);
  }
}

void display_menu() {

  int select = 1;
  int selected = 0;
  int end = 0;

  while (!end) {

    printf("\n\t------- Quiz Game! -------\n\n");
    printf("\t    %c  - Play\n", (select == 1) ? '>' : ' ');
    printf("\t    %c  - Manage Data\n", (select == 2) ? '>' : ' ');
    printf("\t    %c  - Exit\n", (select == 3) ? '>' : ' ');
    printf("\n\t--------------------------\n\n");

    handle_cursor(&select, 3, &selected);
    if (selected) {
      switch (select) {
        case 1:
          break;
        case 2:
          selected = 0;
          manage_data();
          break;
        case 3:
          printf("\n\t   See you again soon!");
          delay(1); // delay clear screen
          end = 1;
          break;
      }
    }

    system("cls");
  }
}

int main(int argc, char **argv) {

  display_menu(1);

  return 0;
}
