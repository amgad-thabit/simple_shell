#ifndef MAIN_H
#define MAIN_H

#define MAX_INPUT_LENGTH 100

void display_prompt(void);
void remove_newline(char *str);
int tokenize_input(char *input, char **args);
int check_command_exists(char *command);
void execute_command(char **args);

#endif

