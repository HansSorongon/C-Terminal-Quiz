#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void delay(int seconds) {
    int ms = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + ms); // run a while loop for seconds seconds.
}

int prompt_password() {

  int count = 0;
  char inp[30] = {}; // input stack
  char ch;
  char password[30] = "admin123";

  printf("Password: ");
  while (ch != 13) { // while not enter
    ch = getch();
    system("cls");
    printf("Password: ");

    if (ch == 8 && count > 0) {
      inp[count] = '\0'; // null
      count--;
    } else if (ch != 8 && ch != 13 && count < 30) { // if not bspace or not enter
                                                    // or count < 30
      inp[count] = ch;
      inp[count + 1] = '\0';
      count++;

    }

    for (int i = 0; i < count; i++) {
      printf("*");
    }

  }

  return strcmp(inp, password);
}

void manage_data() {

  system("cls");

  // ask for password before continuing use return value to determine if should
  // let in
  if (!prompt_password()) {
    printf("\n\n\t  Succesfully logged in!");
    delay(1);
  } else {
    printf("\n\n\t  Wrong password! Please try again.");
    delay(1);
  }
}

void display_menu(int select) {

  int selected = 0;

  while (!selected) {

    printf("\n\t------- Quiz Game! -------\n\n");
    printf("\t    %c  - Play\n", (select == 1) ? '>' : ' ');
    printf("\t    %c  - Manage Data\n", (select == 2) ? '>' : ' ');
    printf("\t    %c  - Quit\n", (select == 3) ? '>' : ' ');
    printf("\n\t--------------------------\n\n");

    switch (getch()) {
      case 'j': case 'J':
        if (select != 3) select++;
        break;
      case 'k': case 'K':
        if (select != 1) select--;
        break;
      case 'd': case 'D':
        switch (select) {
          case 1:
            break;
          case 2:
            manage_data();
            break;
          case 3:
            printf("\n\t   See you again soon!");
            delay(1); // delay clear screen
            selected = 1;
            break;
        }

        break;
    }

    system("cls");
  }
}

int main(int argc, char **argv) {


  display_menu(1);



  return 0;
}
