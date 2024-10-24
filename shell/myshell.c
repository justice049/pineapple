#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>
#include<errno.h>
#include<sys/wait.h>

#define SkipPath(p) do{ p += (strlen(p) - 1); while (*p != '/')p--;}while(0)

#define SIZE 512
#define ZERO '\0'
#define SEP " "
#define NUM 32

#define None_REDIR 0
#define In_REDIR 1
#define Out_REDIR 2
#define App_REDIR 3

#define SkipSpace(usercommand,pos) do{\
	while (1){\
		if(isspace(usercommand[pos]))\
			pos++;\
		else break;\
	}\
}while (0)

int redir_type = None_REDIR;
char* filename = NULL;

int lastcode = 1;
char cwd[SIZE * 2];
char* gArgv[NUM];

void Die()
{
	exit(1);
}

const char* Home()
{
	const char* home = getenv("HOME");
	if (home == NULL)
	{
		return "/";
	}
	return home;
}

void Cd()
{
	const char* path = gArgv[1];
	if (path == NULL)
	{
		path = Home();
	}
	chdir(path);
	char temp[SIZE * 2];
	getcwd(temp, sizeof(temp));
	snprintf(cwd, sizeof(cwd), "PWD=%s", temp);
	putenv(cwd);
}

const char* GetUserName()
{
	const char* name = getenv("USER");
	if (name == NULL)
	{
		return "None";
	}
	return name;
}

const char* GetHostName()
{
	const char* hostname = getenv("HOSTNAME");
	if (hostname == NULL)
	{
		return "None";
	}
	return hostname;
}

const char* GetCwd()
{
	const char* cwd = getenv("PWD");
	if (cwd == NULL)
	{
		return "None";
	}
	return cwd;
}

void MakeCommandLine()
{
	char line[SIZE];
	const char* username = GetUserName();
	const char* hostname = GetHostName();
	const char* cwd = GetCwd();

	SkipPath(cwd);
	snprintf(line, sizeof(line), "[%s@%s %s]#", username, hostname, strlen(cwd) == 1 ? "/" : cwd + 1);
	printf("%s", line);
	fflush(stdout);
}

int GetUserCommand(char command[], size_t n)
{
	char* s = fgets(command, n, stdin);
	if (s == NULL)
	{
		return -1;
	}
	command[strlen(command) - 1] = ZERO;
	return strlen(command);
}


void splitCommand(char command[], size_t n)
{
	gArgv[0] = strtok(command, SEP);
	int index = 1;
	while ((gArgv[index++] = strtok(NULL, SEP)));
}

void ExecuteCommand()
{
	pid_t id = fork();
	if (id < 0)
	{
		Die();
	}
	else if (id == 0)
	{
		if (filename != NULL)
		{
			if (redir_type == In_REDIR)
			{
				int fd = open(filename, O_RDONLY);
				dup2(fd, 0);
			}
			else if (redir_type == Out_REDIR)
			{
				int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
				dup2(fd, 1);
			}
			else if (redir_type == App_REDIR)
			{
				int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
				dup2(fd, 1);
			}
			else
			{

			}
		}
		execvp(gArgv[0], gArgv);
		exit(errno);
	}
	else
	{
		int status = 0;
		pid_t rid = waitpid(id, &status, 0);
		if (rid > 0)
		{
			lastcode = WEXITSTATUS(status);
			if (lastcode != 0)
			{
				printf("%s:%s:%d\n", gArgv[0], strerror(lastcode), lastcode);
			}
		}
	}
}

int CheckBuildin()
{
	int yes = 0;
	const char* enter_cmd = gArgv[0];
	if (strcmp(enter_cmd, "cd") == 0)
	{
		yes = 1;
		Cd();
	}
	else if (strcmp(enter_cmd, "echo") == 0 && strcmp(gArgv[1], "$?") == 0)
	{
		yes = 1;
		printf("%d\n", lastcode);
		lastcode = 0;
	}
	return yes;
}

void CheckRedir(char usercommand[])
{
	int pos = 0;
	int end = strlen(usercommand);
	while (pos<end)
	{
		if (usercommand[pos] == '>')
		{
			if (usercommand[pos + 1] == '>')
			{
				usercommand[pos++] = 0;
				pos++;
				redir_type = App_REDIR;
				SkipSpace(usercommand, pos);
				filename = usercommand + pos;
			}
			else
			{
				usercommand[pos++] = 0;
				pos++;
				redir_type = In_REDIR;
				SkipSpace(usercommand, pos);
				filename = usercommand + pos;
			}
		}
		else if (usercommand[pos] == '<')
		{
			usercommand[pos++] = 0;
			redir_type = In_REDIR;
			SkipSpace(usercommand,pos);
			filename = usercommand + pos;
		}
		else
		{
			pos++;
		}
	}
}

int main()
{
	int quit = 0;
	while (!quit)
	{
		redir_type = None_REDIR;
		filename = NULL;
		MakeCommandLine();

		char usercommand[SIZE];
		int n = GetUserCommand(usercommand, sizeof(usercommand));
		if (n < 0)
		{
			return 1;
		}

		CheckRedir(usercommand);

		splitCommand(usercommand, sizeof(usercommand));

		n = CheckBuildin();
		if (n)
		{
			continue;
		}

		ExecuteCommand();
	}
	return 0;
}