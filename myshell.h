// ********************************************************************
// date:    March 2023
// author:  Chee Hin Choa
// student number:  21100497
// A simple shell program with some built-in commands
// *******************************************************************/

//References

/*
I understand that the University regards breaches of academic integrity and plagiarism as
grave and serious.

I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the
penalties that may be imposed should I engage in practice or practices that breach this
policy.

I have identified and included the source of all facts, ideas, opinions and viewpoints of others
in the assignment references. Direct quotations, paraphrasing, discussion of ideas from
books, journal articles, internet sources, module text, or any other source whatsoever are
acknowledged and the sources cited are identified in the assignment references.
I declare that this material, which I now submit for assessment, is entirely my own work and
has not been taken from the work of others save and to the extent that such work has been
cited and acknowledged within the text of my work.

I have used the DCU library referencing guidelines (available at
https://www4.dcu.ie/library/classes_and_tutorials/citingreferencing.shtml and/or the
appropriate referencing system recommended in the assignment guidelines and/or
programme documentation.
*/
#ifndef MYSHELL_H
#define MYSHELL_H

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators
#define PATH_MAX 2048

void cat(char** args);
void help();
void echo(char** args);
void dir(char** args);
void cd(char** args);
void ls_environ();
void clr();

int redirection(char** args, char **inputfile, char **outputfile);

#endif