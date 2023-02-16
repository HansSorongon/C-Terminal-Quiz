#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// try adding typedefs for each string

// function prot for display_menu()
void display_menu();
void manage_data();

// main structure for questions
typedef struct
{
  char topic[20];
  int q_number;
  char question[150];
  char choice1[30];
  char choice2[30];
  char choice3[30];
  char answer[30];
} question_t;

typedef struct {
  char topics[100][20];
  size_t size;
} topics_t;

// struct for file properties, list of questions, size, and file name.
typedef struct
{
  question_t questions[100];
  size_t size;
  char file_name[30];
} file_t;

void delay(float seconds)
{
  float ms = 1000 * seconds;
  clock_t start_time = clock();
  while (clock() < start_time + ms);	// run a while loop for seconds seconds.
}

// returns selected
int display_options(char prompt[60], char options[][20], size_t num_options)
{
  int select = 0;
  int selected = 0;

 	// clear loop
  while (!selected)
  {
    system("cls");

    printf("%s", prompt);

    for (int i = 0; i < num_options; i++)
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

void handle_cursor(int *select, int max, int *selected)
{
  printf("test");
}

// returns 1 if match, 0 if not match
int prompt_password()
{
  char inp[30] = {};
	// input stack
  char ch;
  char password[30] = "admin123";

  system("cls");
  printf("Password: ");
  while (ch != 13)
  {
  	// while not enter
    ch = getch();
    system("cls");
    printf("Password: ");

    if (ch == 8 && strlen(inp) > 0)
    {
      inp[strlen(inp) - 1] = '\0';	// set last to null
    }
    else if (ch != 8 && ch != 13 && strlen(inp) < 30)
    {
    	// if not bspace or not enter
      strncat(inp, &ch, 1);	// append current ch to end
    }

    for (int i = 0; i < strlen(inp); i++)
    {
    	// print *
      printf("*");
    }
  }

  return !abs(strcmp(inp, password));
}

void print_question(question_t question)
{
  printf("\n-----------------------------");
  printf("\nTOPIC: %s\n", question.topic);
  printf("NO: %d\n", question.q_number);
  printf("Q: %s\n\n", question.question);
  printf("A. %s\n", question.choice1);
  printf("B. %s\n", question.choice2);
  printf("C. %s\n\n", question.choice3);
  printf("ANS: %s\n", question.answer);
  printf("\n-----------------------------");

}

/* char * gen_unique_topics(file_t file_props) { */

/*   topics_t unique_topics[]; */

/*   static char topics[100][20];	// 100 worst case scenario possible topics */
/*  	// variable *sized array in switch case is */
/*  	// forbidden */
/*   int topic_count = 0; */

/*  	// generate list of unique topics. */
/*   for (int i = 0; i < file_props->size; i++) */
/*   { */
/*     int in = 0; */
/*     for (int j = 0; j < i; j++) */
/*     { */
/*       if (!strcmp(file_props->questions[i].topic, file_props->questions[j].topic)) */
/*       { */
/*       	in = 1; */
/*       } */
/*     } */

/*     if (! in) */
/*     { */
/*       strcpy(topics[topic_count], file_props->questions[i].topic); */
/*       topic_count++; */
/*     } */
/*   } */

  return unique_topics;
}

void edit_record(file_t *file_props) {

  char topics[100][20];	// 100 worst case scenario possible topics
 	// variable *sized array in switch case is
 	// forbidden
  int topic_count = 0;

 	// generate list of unique topics.
  for (int i = 0; i < file_props->size; i++)
  {
    int in = 0;
    for (int j = 0; j < i; j++)
    {
      if (!strcmp(file_props->questions[i].topic, file_props->questions[j].topic))
      {
      	in = 1;
      }
    }

    if (! in)
    {
      strcpy(topics[topic_count], file_props->questions[i].topic);
      topic_count++;
    }
  }
}

int import_data(file_t *file_props)
{
  system("cls");

  char file_name[30];
  printf("\n Enter the file name: ");
  scanf("%s", file_name);

  strcpy(file_props->file_name, file_name);	// set in file props

  printf("\n Importing %s \n", file_name);
  printf(" ");

  // IMPORT LOGIC
  FILE * fptr;

  fptr = fopen(file_name, "r");
  char format[] = "%[^\n]\n%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n";	// lmfao

  int i = 0;	// count of questions in txt
  if (fptr != NULL)
  {
   	// serialization
    while (!feof(fptr))
    {
      fscanf(fptr, format,
        file_props->questions[i].topic,	// question at index i
        &(file_props->questions[i].q_number),
        file_props->questions[i].question,
        file_props->questions[i].choice1,
        file_props->questions[i].choice2,
        file_props->questions[i].choice3,
        file_props->questions[i].answer);
      i++;
    }
  }
  else
  {
    printf("File not found. Terminating...\n");
  }

  if (fptr)
  {
    for (int i = 0; i < 15; i++)
    {
      printf("#");
      delay(0.1);
    }

    char confirm_options[2][20] = { "Yes", "No" };

    int confirm = display_options("  Would you like to display the contents?\n\n", confirm_options, 2);

    if (!confirm)
    {
      printf("\n\n Displaying file contents...\n");
      for (int j = 0; j < i; j++)
      {
        print_question(file_props->questions[j]);
      }
    }
  }

  fclose(fptr);
  printf("\n\n Press any key to continue...");
  getch();

  return i;	// size
}

void export(file_t *file_props) {

  char file_name[30];
  printf("Please enter the file name: ");
  scanf("%s", file_name);

  FILE *fptr = fopen(file_name, "w+");	// need file name
  char format[] = "%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n";

  // export
  for (int i = 0; i < file_props->size; i++)
  {
    fprintf(fptr, format,
      file_props->questions[i].topic,	// question at index i
      file_props->questions[i].q_number,
      file_props->questions[i].question,
      file_props->questions[i].choice1,
      file_props->questions[i].choice2,
      file_props->questions[i].choice3,
      file_props->questions[i].answer);
  }

  fclose(fptr);

  printf("\n\n  Successfully exported file %s", file_name);
  printf("\n  Press any key to continue...");
  getch();


}

void add_cont(file_t *file_props) {

  char new_question[150];
  char new_answer[30];

  char new_topic[30];
  char new_choice1[30];
  char new_choice2[30];
  char new_choice3[30];

  int max = 0;
  int listed = 0;

  printf("\n\n  Please type in the question to add: \n\n  - ");
  scanf(" %[^\n]", new_question);

  printf("\n\n  Please type in the answer to add: \n\n  - ");
  scanf(" %[^\n]", new_answer);

  for (int i = 0; i < file_props->size; i++)
    {

    // if same question and same answer as something
    if (!strcmp(new_question, file_props->questions[i].question) &&
        !strcmp(new_answer, file_props->questions[i].answer))
      {
        printf("  The record is already listed.\n");
        listed = 1;
        print_question(file_props->questions[i]);
        printf("\n\n  Press any key to continue...\n");
        getch();
      }
    }

    if (!listed)
      {
        system("cls");

        printf("Please enter the following:");

        printf("\n\n Topic: ");
        scanf(" %[^\n]", new_topic);
        printf("\n\n Choice 1: ");
        scanf(" %[^\n]", new_choice1);
        printf("\n\n Choice 2: ");
        scanf(" %[^\n]", new_choice2);
        printf("\n\n Choice 3: ");
        scanf(" %[^\n]", new_choice3);

        // find max q_number
        for (int i = 0; i < file_props->size; i++)
          {
            if (!strcmp(file_props->questions[i].topic, new_topic))
              {
                if (file_props->questions[i].q_number > max)
                  {
                    max = file_props->questions[i].q_number;
                  }
              }
          }

        printf("\n Attempting to append record...\n");
        strcpy(file_props->questions[file_props->size].topic, new_topic);
        file_props->questions[file_props->size].q_number = max + 1;
        strcpy(file_props->questions[file_props->size].question, new_question);
        strcpy(file_props->questions[file_props->size].choice1, new_choice1);
        strcpy(file_props->questions[file_props->size].choice2, new_choice2);
        strcpy(file_props->questions[file_props->size].choice3, new_choice3);
        strcpy(file_props->questions[file_props->size].answer, new_answer);

        file_props->size++;

        printf("\n  Successfully added record.");
        printf("\n\n  Press any key to continue...\n");
        getch();
        manage_data(file_props);
      }

    system("cls");
}

void add_record(file_t *file_props) {

  if (file_props->size)
    {
      add_cont(file_props);
    }
    else
    {
      char import_options[2][20] = { "Yes", "No" };

      int select = display_options("You have not imported a file! Import one?\n\n", import_options, 2);

      switch (select)
      {
        case 0:
          system("cls");
          file_props->size = import_data(file_props);	// import fallback
          add_cont(file_props);

          break;
        case 1:
          display_menu(file_props);	// no size

          break;
      }
    }
}


void delete_cont(file_t *file_props)
{
  char topics[100][20];	// 100 worst case scenario possible topics
 	// variable *sized array in switch case is
 	// forbidden
  int topic_count = 0;

 	// generate list of unique topics.
  for (int i = 0; i < file_props->size; i++)
  {
    int in = 0;
    for (int j = 0; j < i; j++)
    {
      if (!strcmp(file_props->questions[i].topic, file_props->questions[j].topic))
      {
      	in = 1;
      }
    }

    if (! in)
    {
      strcpy(topics[topic_count], file_props->questions[i].topic);
      topic_count++;
    }
  }

  system("cls");
 	// remember this is an int
  int sel_topic = display_options("  Please choose a topic.\n\n", topics, topic_count);

 	// show all questions under that topic
  for (int i = 0; i < file_props->size; i++)
  {
    if (!strcmp(topics[sel_topic], file_props->questions[i].topic))
    {
      print_question(file_props->questions[i]);
    }
  }

  int q_num;

 	// prompt to select which question to delete
  printf("\n\n  Enter the question number: ");
  scanf("%d", &q_num);

 	// iter through all questions in struct
  for (int i = 0; i < file_props->size; i++)
  {
   	// NOTE: i here will be the index of the selected question

   	// if topic matches selected AND question number matches entered
    if ((!strcmp(topics[sel_topic], file_props->questions[i].topic)) && (q_num == file_props->questions[i].q_number))
    {
      system("cls");
      printf("You selected question %d.\n", file_props->questions[i].q_number);
      print_question(file_props->questions[i]);

     	// DELETION CONFIRMATION
      printf("\n\n Are you sure you want to delete this question? y/n");
      int selected = 0;
      char select = '\0';

     	// while not selected
      while (!selected)
      {
        select = getch();
        if (select == 'y' || select == 'Y')
        {
          selected = 1;

          for (int j = i; j < file_props->size - 1; j++)
          {
            file_props->questions[j] = file_props->questions[j + 1];	// shift
           	// left
           	// from i
          }

          (file_props->size) --;	// decrement size

          system("cls");
          printf("\n\n  Record deleted.");
          printf("\n\n  Press any key to continue...");
          manage_data(file_props);
        }
        else if (select == 'n' || select == 'N')
        {
          selected = 1;
          printf("\n\n  Terminating...");
          manage_data(file_props);
        }
      }
    }
  }

 	// decrement all here
  for (int j = 0; j < file_props->size; j++)
  {
    if (!strcmp(topics[sel_topic], file_props->questions[j].topic))
    {
    	// if same
     	// topic as
     	// deleted
      if (file_props->questions[j].q_number > q_num)
      {
      	// if q_number is
       	// greater than the
       	// deleted it will
       	// be shifted left
        file_props->questions[j].q_number -= 1;
      }
    }
  }

 	// print new list
  if (file_props->size < 7)
  {
  	// dont print if too big
    printf("\n\nNew List: \n\n");
    for (int i = 0; i < file_props->size; i++)
    {
      print_question(file_props->questions[i]);
    }
  }

  printf("\n\nFinished rewriting.");

}

void delete_record(file_t *file_props)
{

  int init_size = 0;

  if (file_props->size)
  {
  	// if array already imported, size will be initialized.

    delete_cont(file_props);
  }
  else
  {
    char import_options[2][20] = { "Yes", "No" };

    int select = display_options("You have not imported a file! Import one?\n\n", import_options, 2);

    switch (select)
    {
      case 0:

        system("cls");
        init_size = import_data(file_props);	// import fallback
        file_props->size = init_size;

        delete_cont(file_props);

        break;
      case 1:
        display_menu(file_props);	// no size
        break;
    }
  }
}

void manage_data(file_t *file_props)
{

  static int logged_in = 0;

  enum
  {
    ADD = 0,
      EDIT = 1,
      DELETE = 2,
      IMPORT = 3,
      EXPORT = 4,
      BACK = 5
  };

  if (!logged_in) logged_in = prompt_password();

  if (logged_in)
  {
    char manage_options[6][20] = { "Add", "Edit", "Delete", "Import", "Export", "Back" };

    int select = display_options("   Welcome admin, what would you like to do?\n\n", manage_options, 6);

    switch (select)
    {
      case ADD:
        add_record(file_props);
        break;
      case EDIT:
        edit_record(file_props);
        break;
      case DELETE:
        delete_record(file_props);
        break;
      case IMPORT:
        file_props->size = import_data(file_props);	// if we import data, size gets init
        manage_data(file_props); // have to call again here because import
                                 // returns something
        break;
      case EXPORT:
        export(file_props);
        break;
      case BACK:
        display_menu(file_props);
        logged_in = 0; // log out
        break;
    }
  }
  else
  {
    char try_options[2][20] = { "Try Again", "Back" };

    int select = display_options("   You entered the wrong password!\n\n", try_options, 2);

    switch (select)
    {
      case 0:
        manage_data(file_props);	// recursive fn to try again

        break;
      case 1:
        display_menu();
        break;
    }
  }
}

void play(question_t *questions)
{
  printf("Play here");
}

void play_menu(question_t *questions)
{
  enum
  {
    PLAY = 0,
      VIEW = 1,
      EXIT = 2
  };

  char play_options[3][20] = { "I'm Ready", "View Scores", "Exit" };

  int select = display_options("\n    Welcome challenger, are you ready?\n\n", play_options, 3);

  switch (select)
  {
    case 0:
      play(questions);
      break;
    case 1:
      break;
    case 2:
      display_menu();
      break;
  }
}

void display_menu(file_t *file_props)
{
  enum
  {
    PLAY = 0,
      MANAGE = 1,
      EXIT = 2
  };

  char menu_options[3][20] = { "Play", "Manage Data", "Exit" };

  int selected = display_options("\n\t----- QUIZ MASTER -----\n\n", menu_options, 3);

  switch (selected)
  {
    case PLAY:
      break;
    case MANAGE:
      manage_data(file_props);
      break;
    case EXIT:
      break;
  }
}

int main(int argc, char **argv)
{
 	// *questions always comes with *size

  file_t file_props;	// def struct for file holding questions, size, and file
 	// name
  file_props.size = 0;	// init size as 0

  display_menu(&file_props);

  return 0;
}
