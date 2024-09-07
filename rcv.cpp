#define A 1
#define B 2
struct msgbuf recvbuffer;
msgrcv(msgid,&recvbuffer,sizeof(recvbuffer),A,0);
msgrcv(msgid,&recvbuffer,sizeof(recvbuffer),B,0);