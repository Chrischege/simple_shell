#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void FreeSepList(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void FreeLineList(line_list **head);

/* aux_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void FreeRvarList(r_var **head);

/* aux_str functions */
char *stringcat(char *dest, const char *src);
char *stringcopy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _IsDigit(const char *s);

/* aux_str3.c */
void Reverse_String(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int Error_Sep_Op(char *input, int i, char last);
int FirstChar(char *input, int *i);
void Print_Syntax_Error(data_shell *datash, char *input, int i, int bool);
int Check_Syntax_Error(data_shell *datash, char *input);

/* ShellLoop.c */
char *WithoutComment(char *in);
void ShellLoop(data_shell *datash);

/* ReadLine.c */
char *ReadLine(int *i_eof);

/* split.c */
char *SwapChar(char *input, int bool);
void AddNodes(sep_list **head_s, line_list **head_l, char *input);
void GoNext(sep_list **list_s, line_list **list_l, data_shell *datash);
int SplitCommands(data_shell *datash, char *input);
char **SplitLine(char *input);

/* RepVar.c */
void CheckEnv(r_var **h, char *in, data_shell *data);
int CheckVars(r_var **h, char *in, char *st, data_shell *data);
char *ReplacedInput(r_var **head, char *input, char *new_input, int nlen);
char *RepVar(char *input, data_shell *datash);

/* get_line.c */
void BringLine(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int ExecLine(data_shell *datash);

/* Cmd_Exec.c */
int IsCdir(char *path, int *i);
char *_Whch(char *cmd, char **_environ);
int IsExecutable(data_shell *datash);
int Check_Err_Cmd(char *dir, data_shell *datash);
int Cmd_Exec(data_shell *datash);

/* env1.c */
char *_GetEnv(const char *name, char **_environ);
int _ENV(data_shell *datash);

/* env2.c */
char *Copy_Info(char *name, char *value);
void Set_Env(char *name, char *value, data_shell *datash);
int _SetEnv(data_shell *datash);
int _UnsetEnv(data_shell *datash);

/* cd.c */
void Cd_Dot(data_shell *datash);
void Cd_To(data_shell *datash);
void Cd_Previous(data_shell *datash);
void Cd_To_Home(data_shell *datash);

/* cd_shell.c */
int Cd_Shell(data_shell *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(data_shell *datash);

/* _exit.c */
int ExitShell(data_shell *datash);

/* aux_stdlib.c */
int Get_Length(int n);
char *AuxiliaryItoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *Error_Get_Cd(data_shell *datash);
char *Error_Not_Found(data_shell *datash);
char *Error_Exit_Shell(data_shell *datash);

/* aux_error2.c */
char *error_get_alias(char **args);
char *Error_Env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *err_Path_126(data_shell *datash);


/* GetError.c */
int GetError(data_shell *datash, int eval);

/* GetSigint.c */
void GetSigint(int sig);

/* aux_help.c */
void AuxHelpEnv(void);
void AuxHelpSetenv(void);
void AuxHelpUnsetenv(void);
void AuxHelpGeneral(void);
void AuxHelpExit(void);

/* aux_help2.c */
void AuxHelp(void);
void AuxHelpAlias(void);
void AuxHelpCd(void);

/* Get_Help.c */
int Get_Help(data_shell *datash);

#endif
