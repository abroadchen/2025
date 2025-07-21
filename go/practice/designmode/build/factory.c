#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <Windows.h>



char str[10] = { 0 };//需求
int isrun=0;
HANDLE event;


void facapple(void *p);
void facorange(void *p);
void serverfor();



void client(void *p)
{
    while (1)
    {
        scanf("%s", str);
        SetEvent(event)
    }
}

void server(void *p)
{
    while (1)
    {
        WaitForSingleObject(event, INFINITE);
        printf("\n客户提出需求%s", str);
        //void(*pfun)(void *p)=NULL;
        serverfor();
    }
}

void serverfor()
{
    if (strcmp(str, "apple") == 0)
    {
        void(*pfun)(void *p) = facapple;
        _beginthread(pfun, 0, NULL);
    }
    else if (strcmp(str, "orange") == 0)
    {
        _beginthread(facorange, 0, NULL);
    }
    else
    {
        printf("developing...");
    }
}

void facapple(void *p)
{
    isrun=1;
    Sleep(2000);
    printf("complete apple");
    isrun=0;
}

void facorange(void *p)
{
    Sleep(2000);
    printf("complete orange")
}




void main()
{
    event = CreateEvent(NULL,FALSE,FALSE,"1");
    _beginthread(client, 0, NULL);
    _beginthread(server, 0, NULL);


    //system("pause");
    while (1)
    {
        Sleep(2000);
    }
}
