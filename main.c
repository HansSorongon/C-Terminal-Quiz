#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// try adding typedefs for each string

// function list
void delay(float);
int display_options();
int prompt_password();
void print_question();
int prompt_import();
void find_unique_topics();
void edit_record();
int import_data();
void export ();
void add_cont();
void add_record();
void delete_cont();
void delete_record();
void manage_data();
void play();
void play_menu();
void display_menu();

typedef char string30_t[30];
typedef char string150_t[150];

// main structure for questions
typedef struct
{
  string30_t topic;
  int q_number;
  string150_t question;
  string30_t choice1;
  string30_t choice2;
  string30_t choice3;
  string30_t answer;
}

question_t;

typedef struct
{
  string30_t topics[101];	// we'll store Back in the same list
  size_t topic_count;
}

topics_t;

// struct for file properties, list of questions, size, and file name.
typedef struct
{
  question_t questions[100];
  size_t size;
  string30_t file_name;
}

file_t;

void delay(float seconds)
{
  float ms = 1000 * seconds;
  clock_t start_time = clock();
  while (clock() < start_time + ms);	// run a while loop for seconds seconds.
}

// scanf implementation that allows spaces to be input and prevents buffer
// overflow, flushes input buffer before and after.
void safe_scan(char *buffer, size_t max) {

  fflush(stdin);
  fgets(buffer, max - 1, stdin);
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

// --------------------------------------- MANAGE DATA FNS ------------------------

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

// prompt if not yet imported
int prompt_import(file_t *file_props)
{
  string30_t import_options[2] = { "Yes", "No" };

  int select = display_options("You have not imported a file! Import one?", import_options, 2);
  int init_size = 0;

  int success = 0;

  switch (select)
  {
    case 0:

      system("cls");
      init_size = import_data(file_props);	// import fallback
      file_props->size = init_size;
      success = 1;

      break;
    case 1:
      success = 0;
      break;
  }

  return success;
}

// reformat this to return struct
void find_unique_topics(file_t *file_props, string30_t topics[100], size_t *topic_count)
{
  int i, j;
  int in = 0;
  int count = 0;

  for (i = 0; i < file_props->size; i++)
  {
  	in = 0;
    for (j = 0; j < i; j++)
    {
      if (!strcmp(file_props->questions[i].topic, file_props->questions[j].topic))
      {
       	// if dupe
        in = 1;
      }
    }

    if (! in)
    {
      strcpy(topics[count], file_props->questions[i].topic);
      count++;
    }
  }

  *topic_count = count;

}

void edit_record(file_t *file_props)
{
  if (file_props->size)
  {
    string30_t topics[100];	// 100 worst case scenario possible topics
   	// variable *sized array in switch case is
   	// forbidden
    size_t topic_count = 0;
    int i;

    int q_num;
    int sel_topic;
    int select;

    find_unique_topics(file_props, topics, &topic_count);	// create list of
   	// unique topics

    strcpy(topics[topic_count], "Back");	// append Back to topics array

    printf("\n");
    sel_topic = display_options("Please choose a topic.", topics, topic_count + 1);

   	// BACK
    if (sel_topic == topic_count)
    {
      manage_data(file_props);
    }
    else
    {
     	// display all under that topic
      system("cls");
      for (i = 0; i < file_props->size; i++)
      {
        if (!strcmp(topics[sel_topic], file_props->questions[i].topic))
        {
          print_question(file_props->questions[i]);
        }
      }

      printf("\n\n Please enter the question number: ");
      scanf("%d", &q_num);

      for (i = 0; i < file_props->size; i++)
      {
       	// NOTE: i here will be the index of the selected question
       	// if topic matches selected AND question number matches entered
        if ((!strcmp(topics[sel_topic], file_props->questions[i].topic)) && (q_num == file_props->questions[i].q_number))
        {
         	// file_props->questions[i] is the question

          system("cls");
          print_question(file_props->questions[i]);
          printf("\n\n  Which field would you like to edit?\n\n");

          printf("[1] Topic\n");
          printf("[2] Question\n");
          printf("[3] Choice A\n");
          printf("[4] Choice B\n");
          printf("[5] Choice C\n");
          printf("[6] Answer\n\n");

          select = getch();
          printf("You selected: %d", select - 48);

          switch (select - 48)
          {
            case 1:
              printf("\nPlease enter the new entry: ");
              safe_scan(file_props->questions[i].topic, 30);
              break;
            case 2:
              printf("\nPlease enter the new entry: ");
              scanf(" %[^\n]", file_props->questions[i].question);
              break;
            case 3:
              printf("\nPlease enter the new entry: ");
              scanf(" %[^\n]", file_props->questions[i].choice1);
              break;
            case 4:
              printf("\nPlease enter the new entry: ");
              scanf(" %[^\n]", file_props->questions[i].choice2);
              break;
            case 5:
              printf("\nPlease enter the new entry: ");
              scanf(" %[^\n]", file_props->questions[i].choice3);
              break;
            case 6:
              printf("\nPlease enter the new entry: ");
              scanf(" %[^\n]", file_props->questions[i].answer);
              break;
          }

          edit_record(file_props);	// recursive
        }
      }
    }
  }
  else
  {
    if (prompt_import(file_props))
    {
      edit_record(file_props);
    }
    else
    {
      manage_data(file_props);
    }
  }
}

int import_data(file_t *file_props)
{
  string30_t file_name;
  int i = 0;	// count of questions in txt
  int j;
  int confirm;

  system("cls");
  printf("\n Enter the file name: ");
  scanf("%s", file_name);

  strcpy(file_props->file_name, file_name);	// set in file props

  printf("\n Importing %s \n", file_name);
  printf(" ");

 	// IMPORT LOGIC
  FILE * fptr;

  fptr = fopen(file_name, "r");
  char format[] = "%[^\n]\n%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n";	// lmfao

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
    string30_t confirm_options[2] = { "Yes", "No" };

    confirm = display_options("Would you like to display the contents?", confirm_options, 2);

    if (!confirm)
    {
      printf("\n\n Displaying file contents...\n");
      for (j = 0; j < i; j++)
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

void
export (file_t *file_props)
{
  if (file_props->size)
  {
    string30_t file_name;
    int i;

    printf("Please enter the file name: ");
    scanf("%s", file_name);

    FILE *fptr = fopen(file_name, "w+");	// need file name
    char format[] = "%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n";

   	// export
    for (i = 0; i < file_props->size; i++)
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
  else
  {
    system("cls");
    printf("\n\n  You have not imported a file yet!\n");
    printf("\n  Press any key to continue...\n");
    getch();
  }

  manage_data(file_props);

}

void add_cont(file_t *file_props)
{
 	// variables to store new entries
  string150_t new_question;
  string30_t new_answer;
  string30_t new_topic;
  string30_t new_choice1;
  string30_t new_choice2;
  string30_t new_choice3;

  int max = 0;
  int listed = 0;
  int i;

  system("cls");
  printf("\n\n  Please type in the question to add: \n\n  - ");
  scanf(" %[^\n]", new_question);

  printf("\n\n  Please type in the answer to add: \n\n  - ");
  scanf(" %[^\n]", new_answer);

  for (i = 0; i < file_props->size; i++)
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
    for (i = 0; i < file_props->size; i++)
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

void add_record(file_t *file_props)
{
  if (file_props->size)
  {
    add_cont(file_props);
  }
  else
  {
    if (prompt_import(file_props))
    {
      add_cont(file_props);
    }
    else
    {
      manage_data(file_props);
    }
  }
}

void delete_cont(file_t *file_props)
{
  string30_t topics[100];	// 100 worst case scenario possible topics
 	// variable *sized array in switch case is
 	// forbidden
  size_t topic_count = 0;
  int i;
  int j;
  int q_num;
  int selected;
  char select;
  int sel_topic;

 	// generate list of unique topics.
  find_unique_topics(file_props, topics, &topic_count);

  system("cls");
 	// remember this is an int
  sel_topic = display_options("Please choose a topic.", topics, topic_count);

 	// show all questions under that topic
  for (i = 0; i < file_props->size; i++)
  {
    if (!strcmp(topics[sel_topic], file_props->questions[i].topic))
    {
      print_question(file_props->questions[i]);
    }
  }

 	// prompt to select which question to delete
  printf("\n\n  Enter the question number: ");
  scanf("%d", &q_num);

 	// iter through all questions in struct
  for (i = 0; i < file_props->size; i++)
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
      selected = 0;
      select = '\0';

     	// while not selected
      while (!selected)
      {
        select = getch();
        if (select == 'y' || select == 'Y')
        {
          selected = 1;

          for (j = i; j < file_props->size - 1; j++)
          {
            file_props->questions[j] = file_props->questions[j + 1];	// shift
           	// left
           	// from i
          }

          (file_props->size) --;	// decrement size

          system("cls");
          printf("\n\n  Record deleted.");
         	// decrement all here
          for (j = 0; j < file_props->size; j++)
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

          printf("\n\n Press any key to continue...\n");
          getch();
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
}

void delete_record(file_t *file_props)
{
  if (file_props->size)
  {
   	// if array already imported, size will be initialized.
    delete_cont(file_props);
  }
  else
  {
    if (prompt_import(file_props))
    {
      delete_cont(file_props);
    }
    else
    {
      manage_data(file_props);
    }
  }
}

void manage_data(file_t *file_props)
{
  static int logged_in = 0;
  string30_t manage_options[6] = { "Add", "Edit", "Delete", "Import", "Export", "Back" };

  string30_t try_options[2] = { "Try Again", "Back" };

  int select;

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
    select = display_options("Welcome admin, what would you like to do?", manage_options, 6);

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
        manage_data(file_props);	// have to call again here because import
       	// returns something
        break;
      case EXPORT:
        export (file_props);
        break;
      case BACK:
        logged_in = 0;	// log out
        display_menu(file_props);
        break;
    }
  }
  else
  {
    select = display_options("You entered the wrong password!", try_options, 2);

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

// ------------------------------END OF MANAGE DATA FUNCTIONS ---------------

void play(file_t file_props, FILE *fptr)	// play can just receive the value of file_props
// since we're not editing it.
{
  string30_t name;
  unsigned int score = 0;
  int game_over = 0;
  int select;
  int i;
  int j;
  int random_index;
  char choice;
  string30_t user_answer;

  topics_t topic_list;	// this not only is the list of topics but the topics
 	// but the size as well

 	// topic_map has the same length as topic_count
  struct map
  {
    string30_t key;
    int length;
    int indices[100];	// 100 possible indices worst case
  }

  topic_map[100];	// 100 worst case unique topics
 	//

 	// THE CURRENT LIST OF QUESTIONS UNDER A SPECIFIC TOPIC

 	// we put back in the list of topics so it can appear in the same select
 	// screen.

  find_unique_topics(&file_props, topic_list.topics, &topic_list.topic_count);
  strcpy(topic_list.topics[topic_list.topic_count], "Back");	// at very last index

  for (i = 0; i < topic_list.topic_count; i++)
  {
  	// append with list of topics
    strcpy(topic_map[i].key, topic_list.topics[i]);
    topic_map[i].length = 0;	// init to 0
  }

  for (i = 0; i < file_props.size; i++)
  {
  	// increment each value based on
   	// count of questions under x topic.
    for (j = 0; j < topic_list.topic_count; j++)
    {
      if (!strcmp(file_props.questions[i].topic, topic_map[j].key))
      {
        topic_map[j].indices[topic_map[j].length] = i;
        topic_map[j].length++;	// length of each topic
      }
    }
  }

  system("cls");
  printf("\n  What is your name?");
  printf("\n  - ");
  scanf(" %[^\n]", name);

  string30_t current_choices[3];

  while (!game_over)
  {
  	// not game over or not

    system("cls");
    select = display_options_score("Please select a topic.", topic_list.topics, topic_list.topic_count + 1, score);

    if (select == topic_list.topic_count)
    {
    	// if back was selected
      printf("\n\n Thank you for playing!");
      printf("\n Your final score is %d.", score);

     	// export score here. when done exporting, close
      fprintf(fptr, "%s\n%d\n\n", name, score);
      fclose(fptr);

      game_over = 1;
      delay(1);
    }
    else
    {
      random_index = topic_map[select].indices[rand() % topic_map[select].length];

      system("cls");


     	// current questions into a list
      strcpy(current_choices[0], file_props.questions[random_index].choice1);
      strcpy(current_choices[1], file_props.questions[random_index].choice2);
      strcpy(current_choices[2], file_props.questions[random_index].choice3);


      choice = display_options_score(file_props.questions[random_index].question, current_choices, 3, score);	// display the choices

      switch (choice)
      {
        case 0:
          strcpy(user_answer, file_props.questions[random_index].choice1);
          break;
        case 1:
          strcpy(user_answer, file_props.questions[random_index].choice2);
          break;
        case 2:
          strcpy(user_answer, file_props.questions[random_index].choice3);
          break;
      }

      if (!strcmp(user_answer, file_props.questions[random_index].answer))
      {
        score += 10;
        printf("\n Correct! + 10!");
        delay(0.5);
      }
      else
      {
        printf("\n Wrong!");
        delay(0.5);
      }
    }
  }

  display_menu(&file_props);
}

void view_scores(file_t file_props, FILE *fptr)
{
  struct player
  {
    string30_t name;
    int score;
  }

  players[100];

  size_t count = 0;
  char format[12] = "%[^\n]\n%d\n";

  while (!feof(fptr))
  {
    fscanf(fptr, format, players[count].name, &players[count].score);
    count++;
  }

  // SORT
  int i, j, min_idx;
  struct player temp;

  for (i = 0; i < count - 1; i++) {
    min_idx = i;

    for (j = i; j < count; j++) {
      if (players[j].score > players[min_idx].score)
        min_idx = j;
    }

    if (min_idx != i) {

      temp = players[min_idx];
      players[min_idx] = players[i];
      players[i] = temp;

    }
  }

  fclose(fptr);	// close here to be reopened when play_menu gets called again

  system("cls");
  printf("\n\n  %-5s | %-12s | %-6s\n", "NO.", "NAME", "SCORE");

  for (i = 0; i < count; i++)
  {
    printf("  %-5d | %-12s | %-6d\n", i + 1, players[i].name, players[i].score);
  }

  printf("\n\n Press any key to continue...");
  getch();

  play_menu(file_props);
}

void play_menu(file_t file_props)
{
  enum
  {
    PLAY = 0,
      VIEW = 1,
      BACK = 2
  };

  string30_t play_options[3] = { "I'm Ready", "View Scores", "Back" };

  FILE * fptr;
  fptr = fopen("score.txt", "a+");

  int select = display_options("Welcome challenger, are you ready?", play_options, 3);

  switch (select)
  {
    case PLAY:

      play(file_props, fptr);
      break;
    case VIEW:
      view_scores(file_props, fptr);	// pass file props for recursion
      break;
    case BACK:
      display_menu(&file_props);	// only this one passes address
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

  string30_t menu_options[3] = { "Play", "Manage Data", "Exit" };

  int selected = display_options("\t----- QUIZ MASTER -----", menu_options, 3);

  switch (selected)
  {
    case PLAY:
      play_menu(*file_props);	// dereference here instead of passing pointer
     	// for safety
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
 	//
  srand((unsigned) time(NULL));

  file_t file_props;	// def struct for file holding questions, size, and file
 	// name
  file_props.size = 0;	// init size as 0

  display_menu(&file_props);

  return 0;
}
