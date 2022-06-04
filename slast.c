#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>


void showtime(long);
void show_info(struct utmp *);
int isNumber(char number[]);
int ii=0;

int main(int args, char* argv[])
{
    struct utmp ut;
    int utmpfd;
    struct utmp utArr[1000];
    int all_good = isNumber(argv[1]);
    if(all_good == 0){
    	    perror("Sent words instead of number!");
            exit(-1);
            }
    else{ 
    if((utmpfd = open(WTMP_FILE,O_RDONLY)) == -1){
        perror(WTMP_FILE);
        exit(-1);
    }
    
    while(read(utmpfd,&ut,sizeof(ut)) == sizeof(ut)){
        int a =ut.ut_type;
        if( a == USER_PROCESS || a == BOOT_TIME){
            utArr[ii++]=ut;
        }

    }
    int lenArr =ii;
   
    if(args>1){
        
        int len = atoi(argv[1])+1;
        int end = lenArr-len;
        if((len-1)<0){
            perror("Sent negative length!");
            exit(-1);
        }
        else if(end<-1){
            for(int i = lenArr-1;i>=0;i--){
            		show_info(&utArr[i]);
            }
            }
        else{
            for(int i = lenArr-1;i>end;i--){
                show_info(&utArr[i]);
            }
        }
    }
    else{    
        perror("No Argument was sent!");
        exit(-1);
    }
    
    close(utmpfd);
    return 0;
}
	}

    
    


void show_info(struct utmp *utbufp)
{
    ii++;
    printf("%-9.9s",utbufp -> ut_name);
    printf(" ");
    if(utbufp -> ut_type == BOOT_TIME)
    {
        printf("system boot");
        printf(" ");
        printf("%-16.16s", utbufp -> ut_host);


    }
    else
    {
        printf("%-11.11s",utbufp -> ut_line);
        printf(" ");
        printf("%-16.16s", utbufp -> ut_line);

    }

    printf(" ");
    showtime(utbufp -> ut_time);
    printf("\n");

}
void showtime(long timeval)
{
    char *cp;
    cp = ctime(&timeval);
    printf("%16.16s",cp);
}    
int isNumber(char number[])
{
    int i = 0;
    for (; number[i] != 0; i++)
    {
        if (number[i] > '9' || number[i] < '0')
            return 0;
    }
    return 1;
}









