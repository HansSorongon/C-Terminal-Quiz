#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "helper.h"

// try adding typedefs for each string

// function prototypes for crucial helper functions
void manage_data(file_t *file_props);
int import_data(file_t *file_props);
void display_menu(file_t *file_props);
void play_menu(file_t file_props);

// --------------------------------------- MANAGE DATA FNS ------------------------

/* print_question prints the question in labelled and formatted form.
  @param question - The question to be printed in question_t type.

  @return void
  Pre-condition: question is in proper format and type.
*/
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

/* prompt_import asks the user if they want to import a file. It calls the
 * appropriate functions depending on the user's input.
  @param *file_props - The pointer to the file props containing the contents of the imported file.

  @return success - 1 or 0 respectively depending on whether or not the operation was successful.
  Pre-condition: A file has not yet been imported.
*/
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

/* find_unique_topics finds all unique topics in a given list of questions and
 * edits an array of topics under the type string30_t to reflect that.
  @param *file_props - A pointer to the struct representing the properties of the file including the questions.
  @param topics[100] - An array of unique topics. Set to 100 as the max number of unique topics is 100.
  @param *topic_count - a pointer to an integer containing the topic count to be set after topics
  are appended to the topics array.

  @return success - 1 or 0 respectively depending on whether or not the operation was successful.
  Pre-condition: N/A
*/
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

/* edit_record prompts the user to change a specific element about a record based on user input.
  This function does not follow the same structure as add or delete with a _cont function as it is shorter.
  @param *file_props - A pointer to the struct representing the properties of the file including the questions.

  @return void
  Pre-condition: N/A
*/
void edit_record(file_t *file_props)
{
  if (file_props->size) // if a file has been imported already
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
              safe_scan(file_props->questions[i].question, 150);
              break;
            case 3:
              printf("\nPlease enter the new entry: ");
              safe_scan(file_props->questions[i].choice1, 30);
              break;
            case 4:
              printf("\nPlease enter the new entry: ");
              safe_scan(file_props->questions[i].choice2, 30);
              break;
            case 5:
              printf("\nPlease enter the new entry: ");
              safe_scan(file_props->questions[i].choice3, 30);
              break;
            case 6:
              printf("\nPlease enter the new entry: ");
              safe_scan(file_props->questions[i].answer, 30);
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

/* import_data takes a file name and deserializes the contents of the file into
   a file_t struct the program can read. This struct will be present for most of the application.
   @param *file_props - A pointer to the struct representing the properties of the file including the questions.

  @return i - the count of questions imported.
  Pre-condition: N/A
*/
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
  char format[] = "%[^\n]\n%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n";

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

/* export takes the current file properties and serializes it into a text file
   that can be used in future instances of the program. It asks the user for
   the file name.
   @param *file_props - A pointer to the struct representing the properties of the file including the questions.

  @return void
  Pre-condition: N/A
*/
void export (file_t *file_props)
{
  if (file_props->size)
  {
    string30_t file_name;
    int i;

    printf("Please enter the file name: ");
    safe_scan(file_name, 30);

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

/* add_cont is a helper function and continues the process of adding a
   question into the file properties currently being used in the program..
   @param *file_props - A pointer to the struct representing the properties of the file including the questions.

  @return void
  Pre-condition: A file has been imported already..
*/
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
  safe_scan(new_question, 150);

  printf("\n\n  Please type in the answer to add: \n\n  - ");
  safe_scan(new_answer, 30);

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
    safe_scan(new_topic, 30);

    printf("\n\n Choice 1: ");
    safe_scan(new_choice1, 30);
    printf("\n\n Choice 2: ");
    safe_scan(new_choice2, 30);
    printf("\n\n Choice 3: ");
    safe_scan(new_choice3, 30);

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

    printf("\n  Attempting to append record...\n");
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

/* add_record manages the first part of adding a record to the current file
  properties. It checks if there is a file already imported and calls prompt_import if not.
  @param *file_props - A pointer to the struct representing the properties of the file including the questions.

  @return void
  Pre-condition: N/A
*/
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

/* delete_cont manages the second part of the process of deleting a record(question)
  currently in the file properties being used.
  @param *file_props - A pointer to the struct representing the properties of the file including the questions.

  @return void
  Pre-condition: A file has been imported already.
*/
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
            file_props->questions[j] = file_props->questions[j + 1];	// shift left
          }

          (file_props->size) --;	// decrement size

          system("cls");
          printf("\n\n  Record deleted.");
         	// decrement all question numbers here
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

/* delete_record manages the first part of deleting a record in the current file
  properties. It checks if there is a file already imported and calls prompt_import if not.
  @param *file_props - A pointer to the struct representing the properties of the file including the questions.

  @return void
  Pre-condition: N/A
*/
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

/* manage_data handles the menu for all the data management related processes.
  It also prompts the user for admin credentials before allowing the user to
  use any of the functions stored.
  @param *file_props - A pointer to the struct representing the properties of the file including the questions.

  @return void
  Pre-condition: N/A
*/
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
        export(file_props);
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
        display_menu(file_props);
        break;
    }
  }
}

// ------------------------------END OF MANAGE DATA FUNCTIONS ---------------

/* play handles all of the game logic as well as prompts the user for each
  input needed in the game loop. For generating random questions, the play
  function creates a map of indices under each specific topic before the game
  loop to utilize O(1) array indexing instead of what would be O(n) searches
  per iteration. This reduces the max number of game loops to 100.
  @param *file_props - A pointer to the struct representing the properties of the file including the questions.
  @param *fptr - A pointer to a file for editing. This will be used to edit the score.txt file.

  @return void
  Pre-condition: A file has already been imported (best case).
*/
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
  int map_rand;

  topics_t topic_list;	// this not only is the list of topics but the topics but the size as well

  // topic_map has the same length as topic_count
  struct map
  {
    string30_t key;
    int length;
    int indices[100];	// 100 possible indices worst case
  } topic_map[100];	// 100 worst case unique topics

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

    if (select == topic_list.topic_count) // if back was selected
    {
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
      map_rand = rand() % topic_map[select].length;
      random_index = topic_map[select].indices[map_rand];

      system("cls");


     	// current choices into a list
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

      if (!strcmp(user_answer, file_props.questions[random_index].answer)) // IF
                                                                           // CORRECT
      {
        printf(("Correct! +10\n"));
        score += 10;

        // remove the index from the list of indices under topic
        for (int i = map_rand; i < topic_map[select].length; i++) {
          topic_map[select].indices[i] = topic_map[select].indices[i + 1];
        }
        topic_map[select].length--;

        // if no questions left under this topic, remove it
        if (topic_map[select].length == 0) {
          for (int i = select; i <= topic_list.topic_count; i++) {
            strcpy(topic_list.topics[i], topic_list.topics[i + 1]);
          }
          topic_list.topic_count--;
        }

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

/* play handles all of the game logic as well as prompts the user for each
  input needed in the game loop. For generating random questions, the play
  function creates a map of indices under each specific topic before the game
  loop to utilize O(1) array indexing instead of what would be O(n) searches
  per iteration. This reduces the max number of game loops to 100.
  @param *file_props - A pointer to the struct representing the properties of the file including the questions.
  @param *fptr - A pointer to a file for editing. This will be used to edit the score.txt file.

  @return void
  Pre-condition: A file has already been imported (best case).
*/
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

/* play_menu handles the menu welcoming the user to the main functionality of
  the program, the quiz game.
  @param file_props - the file properties are passed in by value.

  @return void
  Pre-condition: A file has already been imported (best case).
*/
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

/* display_menu displays the main menu where the user select between play,
  manage data, and exit.
  @param file_props - the file properties are passed in by value.

  @return void
  Pre-condition: N/A
*/
void display_menu(file_t *file_props)
{
  enum
  {
    PLAY = 0,
      MANAGE = 1,
      EXIT = 2
  };

  string30_t menu_options[3] = { "Play", "Manage Data", "Exit" };
  string30_t imp_options[2] = { "Yes", "No" };


  int selected = display_options("\t----- QUIZ MASTER -----", menu_options, 3);

  switch (selected)
  {
    case PLAY:

      if (file_props->size) {
        play_menu(*file_props);	// dereference here instead of passing pointer
      } else {

        // if not yet imported, prompt the user to import.
        selected = display_options(" You have not imported a file yet! Import one?", imp_options, 2);

        if (selected == 0) {

          if (prompt_password()) {
            file_props->size = import_data(file_props);

            if (file_props->size) {
              play_menu(*file_props);
            } else {
              display_menu(file_props);  // file does not exist
            }

          } else {
            printf("\n\n You entered the wrong password!\n\n");
            printf(" Press any key to continue...\n");
            getch();
            display_menu(file_props);  // wrong password
          }

        } else {
          display_menu(file_props); // user does not want to import
        }

      }

     	// for safety
      break;
    case MANAGE:
      manage_data(file_props);
      break;
    case EXIT:
      break;
  }
}

// Entry Point
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
