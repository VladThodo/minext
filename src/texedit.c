/* 
   Copyright (c) Vlad Todosin 2023 
   Simple text editor capable of running in the linux terminal. 
   Used this a a project for getting a bit more familiar with C
   Let's see if this actually works :D
*/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

struct termios init_config;

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

int main(){
    rawMode();
    char c;
    while(read(STDIN_FILENO, &c, 1) == 1){
        printRaw(c);

        if(c == 27){            // Check for esc key
            printRawMessage("enter a command");     // Whatever follows will be handled as a command for our text editor
            
        }
    }
}
