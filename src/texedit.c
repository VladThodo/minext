/* 
   Copyright (c) Vlad Todosin 2023 
   Simple text editor capable of running in the linux terminal. 
   Used this a a project for getting a bit more familiar with C
*/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdbool.h>

struct termios init_config;
char CURRENT_CMD[10];                              // We'll use this to store commands

/* Raw print functions */

void printRaw(char c){
    write(STDOUT_FILENO, &c, 1);
}

void printRawMessage(char c[]){
    for(int i = 0; i < strlen(c); i++){
        write(STDOUT_FILENO, &c[i], 1);
    }
}

void stopRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &init_config);
}

void rawMode(){
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    init_config = raw;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void clearCommandBuffer(){
    for(int i = 0; i < 10; i++){
        CURRENT_CMD[i] = ' ';
    }
}

void handleCommand(){
    clearCommandBuffer();
}

int main(){

    rawMode();
    char c;
    bool IS_COMMAND_MODE = false;
    int i = 0;                                          // Use this as an index for our commands
    clearCommandBuffer();                               // Make sure we start out with a clear buffer

    while(read(STDIN_FILENO, &c, 1) == 1){
        if(!IS_COMMAND_MODE) {
            printRaw(c);

            if(c == 27){                                // Check for esc key
                printRawMessage("enter a command: ");     // Whatever follows will be handled as a command for our text editor   
                IS_COMMAND_MODE = true; 
            }

        } else {                                        // This means we're in command mode
          
            if(c == 13){                                // Check for enter key
                handleCommand();
                printRaw('c');
            }

            if(i < 10){
                CURRENT_CMD[i] = c;
                i++;
            } else {
                i = 0;                                  // Reset CMD index
            }

            printRaw(c);                                // Print our character
        }
    }
}
