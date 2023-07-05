#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <errno.h>

#include <unistd.h>

#include <stdio.h>

#include <stdlib.h>

#include <netdb.h>

#include <string.h>

#include <time.h> 

extern int errno;
int port;
time_t seconds;
struct tm *timeStruct;
int main(int argc, char * argv[]) {
  int p=0;
  
  srand(time(NULL));
  int sd;
  int sdcount=0;
  int sdnr[100];
  int ok=0;
  int nobilid=0;
  struct sockaddr_in server;
  char msg[100];
  char mesaj[100];
  if (argc != 3) {
    printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
    return -1;
  }
  port = atoi(argv[2]);
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Eroare la socket().\n");
    return errno;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_port = htons(port);
  int on = 1;
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, & on, sizeof(on));
  if (connect(sd, (struct sockaddr * ) & server, sizeof(struct sockaddr)) == -1) {
    perror("Eroare la connect().\n");
    return errno;
  }
  while (1) 
  {
    bzero(msg, 100);
    printf("Introduceti un rol: ");
    fflush(stdout);
    read(0, msg, 100);
    
    if (write(sd, msg, 100) <= 0) 
    {
      perror("Eroare la write spre server.\n");
      return errno;
    }

    if (strcmp(msg, "quit\n") == 0) {
      close(sd);
      break;
    }
    strcpy(mesaj,msg);
    if(strstr(msg,"nobil")) 
    { char rol_local[50]; int id_local=0;int coins_local=0;
      sscanf(mesaj,"%s %d %d\n", rol_local, &id_local, &coins_local);
      while (1) 
      { bzero(msg, 100);
        if(sdcount!=0)
        read(sdnr[sdcount], msg, 100);
        

      else
      
        read(sd, msg, 100);
       
      
        
        if (strcmp(msg, "taxa de intrare in padure - 100 galbeni\n") == 0) 
        { p=p+100;
        seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
          printf("taxa de intrare in padure - 100 galbeni\n");
          printf("mai am %d galbeni\n", coins_local-p);
          
          sleep(5); 
          sdcount++;
          if ((sdnr[sdcount] = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
            {
                perror("Eroare la socket().\n");
                return errno;
            }
          if (connect(sdnr[sdcount], (struct sockaddr * ) & server, sizeof(struct sockaddr)) == -1) 
            {
                perror("Eroare la connect().\n");
                return errno;
            } 
            else { ok=1;
            
            
            write(sdnr[sdcount], mesaj, 100);
        }}

        else if (strcmp(msg,"Ai trecut!!\n")==0)
        {   sleep(3);
        seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
            printf("Am scapat!!!\n");
            exit(0);
        }

        else if(strcmp(msg,"maxim 3 nobil in acelasi timp\n")==0)
        {
          printf("maxim 3 nobil in acelasi timp\n");
          exit(0);
        }

        else if(strcmp(msg,"nr maxim de galbeni: 10000\n")==0)
        {
            printf("nr maxim de galbeni: 10000\n");
            exit(0);
        }

        else if(strcmp(msg,"nu mai am bani de drum\n")==0)
          {seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
            printf("%s\n",msg);
            exit(0);
          }
        bzero(msg,100);

      }

    }

    else if(strstr(msg,"serif"))
    {   while(1)
        {bzero(msg, 100);
        if(sdcount!=0)
        read(sdnr[sdcount], msg, 100);
        

      else
      
        read(sd, msg, 100);
        seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
        if(strcmp(msg, "seriful se deconecteaza\n") == 0)
        {
          int r = rand()%(60-30+1) +30;
        printf("seriful se va intoarce in %d secunde \n", r);
        sleep(r);
        sdcount++;
        if ((sdnr[sdcount] = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
            {
                perror("Eroare la socket().\n");
                return errno;
            }
          if (connect(sdnr[sdcount], (struct sockaddr * ) & server, sizeof(struct sockaddr)) == -1) 
            {
                perror("Eroare la connect().\n");
                return errno;
            } 
            else { ok=1;
            
            
            write(sdnr[sdcount], mesaj, 100);
            }

        }}
    }

    else if(strstr(msg,"robin"))
    {
      while(1)
      {
        bzero(msg, 100);
        if(sdcount!=0)
        read(sdnr[sdcount], msg, 100);
        

      else
      
        read(sd, msg, 100);

        if(strcmp(msg, "robin hood a plecat din padure\n") == 0)
        {
          sdcount++;
        
          if ((sdnr[sdcount] = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
            {
                perror("Eroare la socket().\n");
                return errno;
            }
          if (connect(sdnr[sdcount], (struct sockaddr * ) & server, sizeof(struct sockaddr)) == -1) 
            {
                perror("Eroare la connect().\n");
                return errno;
            } 
            else { ok=1;
            
            
            write(sdnr[sdcount], mesaj, 100);
            }

        }
      }
    }


  }
}