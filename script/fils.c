#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

#define LINE_BUFSIZE 128

void ON (int sig){

        FILE *fp;
        int status;
        char line[LINE_BUFSIZE];
        int linenr;

        //execution script bash ON//

        fp = popen("./script_LEDon.sh", "r");
        if (fp == NULL)
        /* Handle error */;

        //Lecture reponse ESP32//

        linenr = 1;
        while (fgets(line, LINE_BUFSIZE, fp) != NULL) {
        printf("Reponse %d: %s", linenr, line);
        ++linenr;}

        status = pclose(fp);
        printf("Programme fils termine");
        exit(0);
}
void OFF (int sig){

        FILE *fp;
        int status;
        char line[LINE_BUFSIZE];
        int linenr;

        //execution script bash ON//

        fp = popen("./script_LEDoff.sh", "r");
        if (fp == NULL)
                /* Handle error */;

        //Lecture reponse ESP32//

        linenr = 1;
        while (fgets(line, LINE_BUFSIZE, fp) != NULL) {
                printf("Reponse %d: %s", linenr, line);                                                                                     ++linenr;}

        status = pclose(fp);
        printf("Programme fils termine");
        exit(0);

}
int main(void)
{
        signal(SIGUSR1, ON);
        signal(SIGUSR2, OFF);
        for(;;)
        {
                sleep(1);
        }

}

