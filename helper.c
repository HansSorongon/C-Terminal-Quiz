#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "helper.h"

void safe_scan(char *buffer, size_t max) {

  fflush(stdin); // flush stdin before and after just to be sure

  int i = 0;

  scanf(" %c", buffer); // first ch deal with input buffer whitespace
  i++;

  for (i = 1; i < max && buffer[i-1] != '\n'; i++) {
    scanf("%c", buffer + i);
  }

  buffer[i-1] = '\0';

  fflush(stdin);

}

// returns selected
int display_options(char prompt[], string30_t options[], size_t num_options)
{
  int select = 0;
  int selected = 0;
  int i;

 	// clear loop
  while (!selected)
  {
    system("cls");

    printf("\n  %s\n\n", prompt);

    for (i = 0; i < num_options; i++)
    {
      printf("\t  %c - %s\n", (select == i) ? '>' : ' ', options[i]);
    }

    printf("\n\t-----------------------\n\n");
    printf("\n[k] up");
    printf("\n[j] down");
    printf("\n[d] select\n\n");

    switch (getch())
    {
      case 'j':
      case 'J':
        if (select < num_options - 1)
        {
          select++;
        }

        break;
      case 'k':
      case 'K':
        if (select > 0)
        {
          select--;
        }

        break;
      case 'd':
      case 'D':
        selected = 1;
        break;
    }
  }

  return select;
}

// an abstraction of display_choices but takes in score as well
int display_options_score(char prompt[], string30_t options[], size_t num_options, int score) {
  int select = 0;
  int selected = 0;
  int i;

 	// clear loop
  while (!selected)
  {
    system("cls");

    printf("  Score: %d\n", score);
    printf("\n  %s\n\n", prompt);

    for (i = 0; i < num_options; i++)
    {
      printf("\t  %c - %s\n", (select == i) ? '>' : ' ', options[i]);
    }

    printf("\n\t-----------------------\n\n");
    printf("\n[k] up");
    printf("\n[j] down");
    printf("\n[d] select\n\n");

    switch (getch())
    {
      case 'j':
      case 'J':
        if (select < num_options - 1)
        {
          select++;
        }

        break;
      case 'k':
      case 'K':
        if (select > 0)
        {
          select--;
        }

        break;
      case 'd':
      case 'D':
        selected = 1;
        break;
    }
  }

  return select;
}

void delay(float seconds)
{
  float ms = 1000 * seconds;
  clock_t start_time = clock();
  while (clock() < start_time + ms);	// run a while loop for seconds seconds.
}

// returns 1 if match, 0 if not match
int prompt_password()
{
  string30_t inp = {};

 	// input stack
  char ch;
  string30_t password = "admin123";
  int i;

  system("cls");
  printf("\n Password: ");
  while (ch != 13)
  {
   	// while not enter
    ch = getch();
    system("cls");
    printf("\n Password: ");

    if (ch == 8 && strlen(inp) > 0)
    {
      inp[strlen(inp) - 1] = '\0';	// set last to null
    }
    else if (ch != 8 && ch != 13 && strlen(inp) < 30)
    {
     	// if not bspace or not enter
      strncat(inp, &ch, 1);	// append current ch to end
    }

    for (i = 0; i < strlen(inp); i++)
    {
      printf("*");
    }
  }

  return !abs(strcmp(inp, password));
}

