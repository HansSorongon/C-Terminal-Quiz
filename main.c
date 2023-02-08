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
//
// NOTES:
//
// set selected = 0 if it brings you somewhere else.

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
      *selected = 1;
      break;
  }
}

// returns 1 if match, 0 if not match
int prompt_password() {
  char inp[30] = {}; // input stack
  char ch;
  char password[30] = "admin123";

  system("cls");
  printf("Password: ");
  while (ch != 13) { // while not enter
    ch = getch();
    system("cls");
    printf("Password: ");

    if (ch == 8 && strlen(inp) > 0) {
      inp[strlen(inp) - 1] = '\0'; // set last to null
    } else if (ch != 8 && ch != 13 && strlen(inp) < 30) { // if not bspace or not enter
      strncat(inp, &ch, 1); // append current ch to end
    }

    for (int i = 0; i < strlen(inp); i++) { // print *
      printf("*");
    }
  }
  return !abs(strcmp(inp, password));
}

void import_data() {
  char file_name[30];
  printf("Enter the name of the file you would like to import.\n\n");
  printf(" -");
  scanf("%s", file_name);

  // TEMPORARY RECORD STUFF HERE
  FILE* fptr;
  fptr = fopen(file_name, "r");
  char str[150];

  if (fptr != NULL) {
    printf("File opened. Displaying contents...\n\n");

    while (fgets(str, 150, fptr)) {
      printf("%s", str);
    }
  } else {
    printf("File not found. Terminating...\n\n");
  }

  getch();
  fclose(fptr); // cleanup

}

void manage_data() {

  enum {
    ADD=1,
    EDIT=2,
    DELETE=3,
    IMPORT=4,
    EXPORT=5,
    BACK=6
  };

  int logged_in = prompt_password();

  if (logged_in) {
    // run data management while loop

    int select = 1;
    int selected = 0;


    while (!selected) {
      system("cls");
      printf("Welcome admin.\n\n") ;
      printf("%c - Add a record\n", (select == 1) ? '>' : ' ') ;
      printf("%c - Edit a record\n", (select == 2) ? '>' : ' ') ;
      printf("%c - Delete a record\n", (select == 3) ? '>' : ' ') ;
      printf("%c - Import data\n", (select == 4) ? '>' : ' ') ;
      printf("%c - Export data\n", (select == 5) ? '>' : ' ') ;
      printf("%c - Back\n\n", (select == 6) ? '>' : ' ') ;


      handle_cursor(&select, 6, &selected);

      if (selected) {
        switch (select) {
          case ADD:
            break;
          case EDIT:
            break;
          case DELETE:
            break;
          case IMPORT:
            import_data();
            break;
          case EXPORT:
            break;
          case BACK:
            break;
        }
      }
    }
  } else {

    int select = 1; // this is in scope of while that runs within else
    int selected = 0;

    while (!selected) {
      system("cls");
      printf("You entered the wrong password!\n\n") ;
      printf("%c - Try again\n", (select == 1) ? '>' : ' ') ;
      printf("%c - Back", (select == 2) ? '>' : ' ') ;
      handle_cursor(&select, 2, &selected);

      if (selected) {
        switch(select) {
          case 1:
            manage_data(); // Recursive
            break;
          case 2:
            break;
        }
      }
    }
  }
}

void play(char topics[][20], size_t size) {

  system("cls");
  printf("\n");

  int select = 1;
  int selected = 0;

  while (!selected) {
    system("cls");

    for (int i = 0; i < size; i++) {
      printf("\t%c%s\n", (select == i + 1) ? '>' : ' ', topics[i]);
    }
    handle_cursor(&select, size, &selected);
  }
}

void play_menu() {

  enum {
    PLAY=1,
    VIEW=2,
    EXIT=3,
  };

  int select = 1;
  int selected = 0;

  // write to score.txt
  FILE* fptr;
  fptr = fopen("score.txt", "w+");

  // get NUM_TOPICS from file with something like count()
  // assign each topic to topics[]

  char topics[5][20];

  for (int i = 0; i < 5; i++) {
    strcpy(topics[i], "Geology");
  }

  // READ FILE INTO TOPICS HERE!

  while (!selected) {

    system("cls");
    printf("\t      Are you ready?\n\n");
    printf("\t    %c  - Play\n", (select == 1) ? '>' : ' ');
    printf("\t    %c  - View Scores\n", (select == 2) ? '>' : ' ');
    printf("\t    %c  - Exit\n", (select == 3) ? '>' : ' ');
    handle_cursor(&select, 3, &selected);

    if (selected) {
      switch (select) {
        case PLAY:

          system("cls");
          char name[20];
          printf("\n\tWhat is your name, challenger?\n\t\t - ");

          scanf("%s", name);

          printf("\n\n\tWelcome to the arena, %s.", name);
          delay(1);

          play(topics, sizeof(topics) / sizeof(topics[0]));

          break;
        case VIEW:
          break;
        case EXIT:
          break;
      }
    }
  }

  fclose(fptr); // cleanup
}

void display_menu() {

  enum {
    PLAY=1,
    MANAGE=2,
    EXIT=3
  };

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
        case PLAY:
          selected = 0; // reset selected because we want to go back here
                        // later.
          play_menu();
          break;
        case MANAGE:
          selected = 0;
          manage_data();
          break;
        case EXIT:
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
