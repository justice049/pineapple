#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/wait.h>
#include<ctype.h>
#include<fcntl.h>
#define SIZE 512
#define ZERO '\0'
#define SEP " "
#define NUM 32

int lastcode=0;
char* argv[SIZE];
char userCommand[SIZE];

int redir=0;

#define SkipSpace(pos) do{while(isspace(*pos)) pos++; }while(0)

int checkChild();
void Redirection();
void checkRedir();
int length(char* arr[]);
const char* getUser()
{
  char* user=getenv("USER");
  if(user)
  {
    return user;
  }
  else
  {
    return "None";
  }
}

const char* getHost()
{
  char* host=getenv("HOSTNAME");
  if(host)
  {
    return host;
  }
  else
  {
    return "None";
  }
}

const char* getPwd()
{
  static char cwd[SIZE];
  if(getcwd(cwd,sizeof(cwd))!=NULL)
  {
    return cwd;
  }
  else
  {
    return "None";
  }
}

void MakeCommandLine()
{
  char line[SIZE];
  const char* username=getUser();
  const char* hostname=getHost();
  const char* cwd=getPwd();
  snprintf(line,sizeof(line), "[%s@%s %s]#", username, hostname, cwd);
  printf("%s",line);
  fflush(stdout);
}

int getCommand(char userCommand[],int n)
{
  char* s=fgets(userCommand,n,stdin);
  if(s==NULL)
  {                                  
    return -1;
  }
  userCommand[strlen(userCommand)-1]=ZERO;
  return strlen(userCommand);
}                         

void commandSplit(char* in,char* out[])
{
  int argc=0;
  out[argc++]=strtok(in,SEP);
  while((out[argc++]=strtok(NULL,SEP))!=NULL);
  out[argc]=NULL;
#ifdef debug 
    int i=0;
    for(i=0;out[i];i++){
      printf("%s\n",out[i]);
    }
#endif
}

int execute()
{
  pid_t id=fork();
  if(id==0)
  {
    Redirection();
    printf("son process begining...");
    execvp(argv[0],argv);
    exit(0);
  }
  else
  {
    int status=0;
    pid_t rid=waitpid(-1,&status,0);
    if(rid==id)
    {
      printf("wait success\n");
      lastcode=WEXITSTATUS(status);
      printf("%d",lastcode);
      return 0;
    }
  }
  return 0;  
}

const char*Home()
{
  const char* home=getenv("Home");
  if(home==NULL)
  {
    return "/";
  }
  return home;
}

void cd()
{
  const char* path=argv[1];
  if(path==NULL)
  {
    path=Home();
  }
  if(chdir(path)==0)
  {
    setenv("PWD",getcwd(NULL,0),1);
  }
  else
  {
    perror("cd faild");
  }
}

int echo()
{
  if(strcmp(argv[0],"echo")==0)
  {
    if(argv[1]==NULL)
    {
      printf("\n");
      return 1;
    }
    // else   //逻辑不对吧
    // {
    //   printf("%s\n",argv[1]);
    //   return 1;
    // }
    if(*(argv[1])=='$'&&strlen(argv[1])>1)
    {
      char *val=argv[1]+1;
      if(strcmp(val,"?")==0)
      {
        printf("%d\n",lastcode);
        lastcode=0;
      }
      else
      {
        char* enval=getenv(val);
        if(enval)
        {
          printf("%s\n",enval);
        }
        else
        {
          printf("\n");
        } 
      }
      return 1;
    }
  }
  return 1;
}
void checkRedir()
{
  //ls -a -l > log.txt
  //ls -a -l >> log.txt
  char* filename=NULL;
  int len=strlen(userCommand);
  char* start=userCommand;
  char* end=userCommand+len-1;
  while(end>start)
  {
    if((*end)=='>')
    {
      if(*(end-1)=='>')
      {
        *(end-1)='\0';
        filename=end+1;
        SkipSpace(filename);
        redir=1;
        break;
      }
      else
      {
        *end='\0';
        filename=end+1;
        SkipSpace(filename);
        redir=2;
        break;
      }
    }
    else if(*end=='<')
    {
      *end='\0';
      filename=end+1;
      SkipSpace(filename);
      redir=3;
      break;
    }
    else
    {
      end--;
    }
  }
  //新加入个判断，判断文件名不为空
  if(filename != NULL)
  {
    while (isspace(*filename))
    {
      filename++;
    }
    
  }
}
void Redirection()
{
  checkRedir();
  //新判断
  if(redir == 0)
  {
    return;
  }
  char *filename=userCommand+strlen(userCommand)+1;
  int fd;  
  if(redir==3)
  {
      fd=open(filename,O_RDONLY);
      if (fd < 0) 
      {
          perror("open output file");
          exit(EXIT_FAILURE);
      }
      dup2(fd,STDIN_FILENO);
      close(fd);
    }
    else if(redir==2)
    {
      fd=open(filename,O_WRONLY | O_CREAT | O_TRUNC,0666);
      if (fd < 0) 
      {
        perror("open output file");
        exit(EXIT_FAILURE);
      }
      dup2(fd,STDOUT_FILENO);
      close(fd);
    }
    else if(redir==1)
    {
      fd=open(filename,O_WRONLY | O_CREAT | O_APPEND,0666);
      if (fd < 0) 
      {
        perror("open output file");
        exit(EXIT_FAILURE);
      }
      dup2(fd,STDOUT_FILENO);
      close(fd);
    }
  }



int checkChild()
{
  int yes=0;
  const char* enter_cmd=argv[0];
  if(strcmp(enter_cmd,"cd")==0)
  {
    yes=1;
    cd();
  }
  else
  {
    if(strcmp(enter_cmd,"echo")==0)
    {
        if(redir==0)
        {
            echo();
            return 1;
        }
    }
  } 
  return 0;
}

int length(char* arr[])
{
  int i=0;
  while(arr[i]!=NULL)
  {
    i++;
  }
  return i;
}

int main()
{
  while(1)
  {
    MakeCommandLine();
    getCommand(userCommand,sizeof(userCommand));
    commandSplit(userCommand,argv);
    if(checkChild())
    continue;
    execute();
  } 
  return 0;
}

