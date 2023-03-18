
typedef char string30_t[31];
typedef char string150_t[151];

// main structure for questions
struct Question
{
  string30_t topic;
  int q_number;
  string150_t question;
  string30_t choice1;
  string30_t choice2;
  string30_t choice3;
  string30_t answer;
};

typedef struct Question question_t;

struct Topics
{
  string30_t topics[101];	// we'll store Back in the same list
  size_t topic_count;
};

typedef struct Topics topics_t;

// struct for file properties, list of questions, size, and file name.
struct File
{
  question_t questions[100];
  size_t size;
  string30_t file_name;
};

typedef struct File file_t;

// FUNCTIONS

void delay(float);

void safe_scan(char *buffer, size_t max);

int display_options(char prompt[], string30_t options[], size_t num_options);

int display_options_score(char prompt[], string30_t options[], size_t num_options, int score);

int prompt_password();

int prompt_import(file_t *file_props);
