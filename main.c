#include"header.h" 

void include_header(FILE*);
int main(int argc, char** argv)
{
	FLAGS flag;
	flag.comment_unbalanced=0;
	if(argc!=2)
	{
		printf("\033[1;33mUsage pr filename.c\033[0m\n");
		return;
	}
	if(!(strlen(argv[1])>=3) || strcmp(argv[1]+strlen(argv[1])-2,".c"))
	{
		printf("\033[1;33mInvalid File selection\033[0m\n");
		return;
	}

	FILE *fp=fopen(argv[1],"r");
	FILE *fp1=fopen("temp.i","w+");
	int count_line=0,line_tracker,count_char=0,char_tracker,i;
	char *tempfile="temp.i";
	remove_comments(fp,fp1);	/*removes comment*/
	rewind(fp1);
	/*Allocate dynamic memory to buffer as required by the file*/
	include_header(tempfile);
}

int size_of_file(FILE *fp)
{
	int size;
	rewind(fp);
	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	rewind(fp);
	return size;
	
}


void create_space(FILE *fp,int size)
{
	int i;
	for(i=1;i<=size;i++)
	fputc('\n',fp);

}
