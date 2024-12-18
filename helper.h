
typedef char string30_t[31]; // extra 1 for null byte
typedef char string150_t[151]; // extra 1 for null byte

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

// struct for file properties, list of questions, size, and file name.
struct File
{
  question_t questions[100]; // questions array
  size_t size; // current size of the data
  string30_t file_name; // file name for use within program
};

typedef struct File file_t;

// FUNCTIONS | Descriptions in helper.c file.

void delay(float);

void safe_scan(char *buffer, size_t max);

int display_options(char prompt[], string30_t options[], size_t num_options);

int display_options_score(char prompt[], string30_t options[],
                          size_t num_options, int score);

int prompt_password();

int is_in(string30_t arr[], size_t size, string30_t key);
