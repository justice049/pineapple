#define A 1
#define B 2
struct msgbuf message;
message.mtype = B;
message.mtext = ("hello world");
msgsnd(msgid,&message,sizeof(message),0);