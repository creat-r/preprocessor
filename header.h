#include<stdio.h>
#include<string.h>
#include<stdint.h>
typedef struct{
	uint8_t comment_unbalanced:1;
	uint8_t comment_line:1;
	uint8_t if_blank:1;
	uint8_t unused3:1;
	uint8_t unused4:1;
	uint8_t unused5:1;
	uint8_t unused6:1;
	uint8_t unused7:1;

}FLAGS;


void back_slash(FILE*,FILE*);
void line_comment(FILE*);
void remove_multiple_line_comment(FILE*);
int isnotbetween_q(char*,char*,int);
char* strstr_uq(char*,char*,int);
void remove_comments(FILE *,FILE*);
