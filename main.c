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

void display_menu();

typedef char string[50];

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


void delay(float seconds) {
    float ms = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + ms); // run a while loop for seconds seconds.
}

// returns selected
int display_options(char prompt[60], char options[][20], size_t num_options) {


  int select = 0;
  int selected = 0;

  // clear loop
  while (!selected) {

    system("cls");

    printf("%s", prompt);

    for (int i = 0; i < num_options; i++) {
      printf("\t  %c - %s\n", (select == i) ? '>' : ' ', options[i]);
    }

    printf("\n\t-----------------------\n\n");
    printf("\n [k] up");
    printf("\n [j] down");
    printf("\n [d] select\n\n");

    switch(getch()) {
      case 'j': case 'J':
        if (select < num_options - 1) {
          select++;
        }
        break;
      case 'k': case 'K':
        if (select > 0) {
          select--;
        }
        break;
      case 'd': case 'D':
        selected = 1;
        break;
      }
  }

  return select;
}

void handle_cursor(int *select, int max, int *selected) {
  printf("test");
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

void manage_data(question_t *questions) {

  enum {
    ADD=0,
    EDIT=1,
    DELETE=2,
    IMPORT=3,
    EXPORT=4,
    BACK=5
  };

  int logged_in = prompt_password();

  if (logged_in) {

    char manage_options[6][20] = {"Add", "Edit", "Delete", "Import", "Export", "Back"};
    int select = display_options("   Welcome admin, what would you like to do?\n\n", manage_options, 6);

    switch(select) {
      case ADD:
        break;
      case EDIT:
        break;
      case DELETE:
        break;
      case IMPORT:

        system("cls");

        string file_name;
        strcpy(file_name, "test.txt");
        printf("\n Importing %s \n", file_name);
        printf(" ");

        // IMPORT LOGIC
        FILE* fptr;

        fptr = fopen("test.txt", "r");
        char format[] = "%[^\n]\n%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n"; // lmfao

        int i = 0; // count of questions in txt
        if (fptr != NULL) {

          // serialization
          while (!feof(fptr)) {
            fscanf(fptr, format,
              questions[i].topic,
              &questions[i].q_number,
              questions[i].question,
              questions[i].choice1,
              questions[i].choice2,
              questions[i].choice3,
              questions[i].answer);
            i++;
          }

        } else {
          printf("File not found. Terminating...\n\n");
        }

        if (fptr) {
          for (int i = 0; i < 12; i++) {
            printf("#");
            delay(0.1);
          }
          printf(" DONE!");
        }

        printf("\n\n Displaying file contents...\n");
        delay(0.5);

        for (int j = 0; j < i; j++) {

            printf("\n-----------------------------");
            printf("\nTOPIC: %s\n", questions[j].topic);
            printf("NO: %d\n", questions[j].q_number);
            printf("Q: %s\n\n", questions[j].question);
            printf("A. %s\n", questions[j].choice1);
            printf("B. %s\n", questions[j].choice2);
            printf("C. %s\n\n", questions[j].choice3);
            printf("ANS: %s\n", questions[j].answer);
            printf("\n-----------------------------");
        }

        fclose(fptr);
        printf("\n\n Press any key to continue...");

        getch();

        break;
      case EXPORT:
        break;
      case BACK:
        display_menu();
        break;
    }

  } else {

    char try_options[2][20] = { "Try Again", "Back" };
    int select = display_options("   You entered the wrong password!\n\n", try_options, 2);

    switch(select) {
      case 0:
        manage_data(questions);
        break;
      case 1:
        display_menu();
        break;
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
    PLAY=0,
    MANAGE=1,
    EXIT=2
  };

  char menu_options[3][20] = {"Play", "Manage Data", "Exit"};
  int selected = display_options("\n\t----- QUIZ MASTER -----\n\n", menu_options, 3);

  question_t questions[100]; // QUESTIONS STORE HERE AFTER LOAD

  switch(selected) {
    case PLAY:
      break;
    case MANAGE:
      manage_data(questions);
      break;
    case EXIT:
      break;
  }
}

int main(int argc, char **argv) {

  display_menu();

  return 0;
}
