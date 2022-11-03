#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>




int main(void)
{

while(1)
{
        int pid, choix;
        FILE *fp;
        int stat, ch2;
        int i = 0;
        char ch;
        char * argv[2];

        pid=fork();

        if(pid == 0){
                argv[0]="F";
                argv[1]=NULL;
			 execv("F",argv);
                }
        else{
                printf("\nMenu\n");
                printf("0.Quitter\n");
                printf("1.Allumer/Eteindre LED\n");
                printf("2.Faire clignoter LED\n");

                printf("Choix : ");
                scanf("%d",&choix);


                switch(choix)
                {
                        case 0 :
                                printf("\nProgramme termine\n");
                                exit(1);
                                break;

                        case 1 :
                                printf("PARENT : press ON/OFF pour allumer/eteindre la LED\n");
                                scanf("%s",&ch);

                                if(strcmp(&ch, "ON") == 0)
                                        {kill(pid,SIGUSR1);}

 						  if(strcmp(&ch, "OFF") == 0)
                                        {kill(pid,SIGUSR2);}

                                break;


                        case 2 :
                                printf("PARENT : Combien de fois souhaitez-vous faire clignoter la LED ?\n");
                                scanf("%d",&ch2);

                                while(i != ch2)
                                {

                                        //execution script bash ON
                                        fp = popen("./script_LEDon.sh", "r");
                                        if (fp == NULL)
                                                /* Handle error */;

                                        sleep(1);

                                        //execution script bash OFF
                                        fp = popen("./script_LEDoff.sh", "r");
                                        if (fp == NULL)
                                                /* Handle error */;

                                        sleep(1);
								i++;
                                }
                                break;

                        default :
                                exit(1);
                                break;

                }

                stat = pclose(fp);
                wait(NULL);
                printf("\nProgramme termine\n");
        }
}
}
