#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#define PORT 2400
void * robinth(void* p_client_socket);
void * serifth(void* p_client_socket);
void * nobilth(void* p_client_socket);
void * clientthread(void* p_client_socket);
extern int errno;
char mesaj[100];
char nobilmesaj[100];
char serifmesaj[100];
char robinmesaj[100];
time_t seconds;
struct tm *timeStruct;
long lSize;
char *buffer;
int sir;
char *sir2;
char mesaj[100];
int away;
char msg[100];
int robin=0;
int nobil=0;
int serif=0;
int serifaici=0;
int nobilcount=0;
int nobilcoins[100];
int nobilid;
int check[100];
int main()
{   
       
    
    pthread_t c;
    
    struct sockaddr_in server;
    struct sockaddr_in from;
    
    char msgrasp[100] = " ";
    int sd;
    
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[server]Eroare la socket().\n");
        return errno;
    }
    int on = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    bzero(&server, sizeof(server));
    bzero(&from, sizeof(from));

    server.sin_family = AF_INET;

    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(PORT);

    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[server]Eroare la bind().\n");
        return errno;
    }

    if (listen(sd, 5) == -1)
    {
        perror("[server]Eroare la listen().\n");
        return errno;
    }
    
    while (1)
    {
        int client;
        int length = sizeof(from);

        fflush(stdout);
        
        client = accept(sd, (struct sockaddr *)&from, &length);

        if (client < 0)
        {
            perror("[server]Eroare la accept().\n");
            continue;
        }
        
        
        int *pclient = malloc(sizeof(int));
        *pclient=client;
        pthread_create(&c, NULL, clientthread, pclient);

    }
}

void * robinth(void* p_client_socket)
{   
    int client_socket=*((int*)p_client_socket);
    robin=1;
    seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
    printf("robin a intrat in padure\n");
    while(1)
    {
        if(serifaici==1)
            {robin=0;
            serifaici=0;
            seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
            printf("robin hood a plecat din padure\n");
            strcpy(robinmesaj,"robin hood a plecat din padure\n");
            sleep(15);
            write(client_socket,robinmesaj,100);
            close(client_socket);
            free(p_client_socket);
            return NULL;
            }
    }
    
}
void * nobilth(void* p_client_socket)
{  
    int client_socket=*((int*)p_client_socket);
    
    char rol_local[50];
    int id_local=0;
   
    int coins_local=0;
    
    char mesaj[100];
    strcpy(mesaj, msg);
    
    sscanf(mesaj,"%s %d %d\n", rol_local, &id_local, &coins_local);
    
    
    while(1)
    {   
        if(robin==1)
        {
            
            nobilcoins[id_local]=nobilcoins[id_local]-100;
            seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
            printf("Nobilul cu id-ul %d are %d galbeni\n",id_local,nobilcoins[id_local]);
            if(nobilcoins[id_local]<=0)
            {
                strcpy(nobilmesaj,"nu mai am bani de drum\n");
                write(client_socket,nobilmesaj,100);
                close(client_socket);
                nobil=nobil-1;
                return NULL;
            }
            else
            {
                strcpy(nobilmesaj,"taxa de intrare in padure - 100 galbeni\n");
                write(client_socket,nobilmesaj,100);
                close(client_socket);
                return NULL;

            }
        }
        else if(robin==0)
        {   seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
            printf("Nobilul cu id-ul %d a scapat din padure\n",id_local);
            strcpy(nobilmesaj,"Ai trecut!!\n");
            write(client_socket,nobilmesaj,100);
            close(client_socket);
            nobil=nobil-1;
            return NULL;
        }
    }
    


    
    free(p_client_socket);
    return NULL;
}
void * serifth(void* p_client_socket)
{   
    int client_socket=*((int*)p_client_socket);  
        serifaici=1;
        seconds = time(NULL);
            timeStruct = localtime(&seconds);
            printf("[%d:%d] ",timeStruct->tm_min, timeStruct->tm_sec);
        printf("seriful a venit\n");
        strcpy(serifmesaj,"seriful se deconecteaza\n");
        write(client_socket,serifmesaj,100);
        close(client_socket);
    free(p_client_socket);
    return NULL;
}
void * clientthread(void* p_client_socket)
{       char rol[50]; 
        int id;
        int coins;
        int client_socket=*((int*)p_client_socket);
        pthread_t r;
        pthread_t n;
        pthread_t s;
        int *pclient_2 = malloc(sizeof(int));
        *pclient_2=client_socket;
        bzero(msg, 100);
        read(client_socket, msg, 100);
        fflush(stdout);
        if(strcmp(msg,"serif\n")==0)
        {
            serif=serif+1;
            pthread_create(&s, NULL, serifth,pclient_2);
        }
        else if(strstr(msg,"robin"))
        {
            robin=robin+1;
            
            pthread_create(&r, NULL, robinth, pclient_2);
        }

        else if(strstr(msg,"nobil"))
        {  nobil=nobil+1;
            sscanf(msg,"%s %d %d\n", rol, &id, &coins);
            if(coins>10000)
            {
                            nobil=nobil-1;
                           strcpy(mesaj,"nr maxim de galbeni: 10000\n");
                           write(client_socket,mesaj,100);
                           close(client_socket);
            }
            else if(check[id]==1)
                {  nobil=nobil-1;
               
                pthread_create(&n, NULL, nobilth, pclient_2);
                }
            else if(check[id]==0)
                {
                    if(nobil>=4)
                       {    
                        nobil=nobil-1;
                           strcpy(mesaj,"maxim 3 nobil in acelasi timp\n");
                           write(client_socket,mesaj,100);
                           close(client_socket);
                       } 
                    else if(nobil<=3)
                        {   
                            check[id]=1;
                            
                check[id]=1;
                nobilcoins[id]=coins;
                pthread_create(&n, NULL, nobilth, pclient_2);

                        }
                }

        }

}
        