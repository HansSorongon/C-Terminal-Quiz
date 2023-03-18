#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "helper.h"

/* safe_scan is a user defined implementation of scanf that allows for the
  input of spaces. Also controls the buffer size to prevent from buffer
  overflow. Flushes stdin before and after writing.
  @param *buffer - the buffer to write to.
  @param max - max characters to write.

  @return void
  Pre-condition: N/A
*/
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

/* display_options displays current options based on parameters passed in. Also
  handles the 'cursor-like' user input style. Clears the screen after every
  navigation.
  @param prompt[] - a string containing the prompt.
  @param options[] - an array of strings containing the options.
  @param num_options - the number of options.

  @return select - the selected option.
  Pre-condition: N/A
*/
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

/* display_options_score is a modified form iof display_options that allows for
  the display of score after each input. This was made because display_options clears
  the screen after every input erasing everything except for the elements it displays.
  @param prompt[] - a string containing the prompt.
  @param options[] - an array of strings containing the options.
  @param num_options - the number of options.
  @param score - the current score.

  @return select - the selected option.
  Pre-condition: N/A
*/
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

/* delay pauses the program for a number of seconds.
   @param seconds - the number of seconds to pause for.

  Pre-condition: N/A
*/

void delay(float seconds)
{
  float ms = 1000 * seconds;
  clock_t start_time = clock();
  while (clock() < start_time + ms);	// run a while loop for seconds seconds.
}

/* prompt_password prompts the user for password input. It also masks the
   password with asterisks * as the user is inputting.

   @return the status whether the input matches the hardcoded password "admin123"
   Pre-condition: N/A
*/
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

