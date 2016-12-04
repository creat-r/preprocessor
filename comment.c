/*
	Author: Chaitanya Kumar Borah
	***IMPROVEMENTS: line should have dynamic memory; warning for unterminated "; error for unterminated multiple line comment
Date:4/12/2016
*/
#include"header.h"

void remove_comments(FILE *fp,FILE* fp1)
{	
	back_slash(fp,fp1);//function to remove backslashes
	line_comment(fp1);//function to remove one line comments
	remove_multiple_line_comment(fp1);
}

void remove_multiple_line_comment(FILE *fp)
{
	FLAGS flag;	
	flag.comment_unbalanced=0;
	flag.if_blank=0;
	char *cp,line[1000],ch,*cp1,*q_tracker;
	int i,count_line=0;
	FILE *ftemp=fopen("mlc_temp","w+");
	rewind(fp);
	while(fgets(line,1000,fp))
	{
		count_line++;
		
		if((cp=strstr_uq(line,"/*",count_line)) && flag.comment_unbalanced==0)
		{
			
			flag.comment_unbalanced=1;
			if(cp1=strstr(line,"*/"))	//if comment terminated on the same line
			{
				flag.comment_unbalanced=0;
				
				for(i=cp-line;i<=cp1-line+1;i++)
				{
					line[i]=' ';
				}

			}
			else				//if not terminated in the same line
			{
				
				for(i=cp-line;line[i]!='\n';i++)
				{
				line[i]=' ';
				}
			}

		}
		else if(flag.comment_unbalanced==1)
		{
			if(cp1=strstr(line,"*/"))	//if comment terminated on the same line
			{
				flag.comment_unbalanced=0;
				for(i=0;i<=cp1-line+1;i++)
					line[i]=' ';

			}
			else				//if not terminated in the same line
			{
				for(i=0;line[i]!='\n';i++)
				{
				line[i]=' ';
				}
			}

		}
		fputs(line,ftemp);
			

	}
	rewind(fp);
	rewind(ftemp);
	while((ch=fgetc(ftemp))!=EOF)
	{
		fputc(ch,fp);
	}


}

void line_comment(FILE *fp)
{
	char *cp,line[1000],ch;//DMA
	int i,count_line=0;
	FILE *ftemp=fopen("lc_temp","w+");
	rewind(fp);
	while(fgets(line,1000,fp))
	{
		count_line++;
		if(cp=strstr_uq(line,"//",count_line))
		{
				for(i=cp-line;line[i]!='\n';i++)
				{
					line[i]=' ';
				}
		}
		fputs(line,ftemp);
	}
	rewind(fp);
	rewind(ftemp);
	while((ch=fgetc(ftemp))!=EOF)
	{
		fputc(ch,fp);
	}

}
	


void back_slash(FILE *fp, FILE *fp1)//first to call
{
	char line[1000],ch;//use dynamic memory // make functions for counting lines char ...
	int i;
	FILE *ftemp=fopen("bl_temp","w+");
	while(fgets(line,1000,fp))
	{
		if(line[strlen(line)-2]=='\\')
		{
			for(i=0;line[i]!='\\';i++)
			fputc(line[i],fp1);
		}
		else
		{
			fputs(line,fp1);
		}
	}
	rewind(ftemp);
	while((ch=fgetc(ftemp))!=EOF)
	{
		fputc(ch,fp1);
	}
	
	remove("bl_temp");
	

}

int isnotbetween_q(char *line,char *cp,int n)//function to check if // or /* lies between "" by checking the number of " before // or /*
{
	int i,c=0;
	for(i=0;(line+i)!=cp;i++)
	{
		if(line[i]=='\"')
		{
			c++;
		}
	}
	//	printf("%d:%s\n ",c,line);
		if(!(c%2))
			return 1;
		else
		{
			
			//printf("\033[1;33mwarning[line:%d]:Unterminated \"\033[0m\n",n);make this work
			return 0;
		}


}

char* strstr_uq(char*line,char*needle,int n)//function to find the position of // or /*(if present) which is not within "" 
{
	char *pos=0,*str=line;

	int i,j=0;

	do
	{
		pos=strstr(str,needle);
		if(pos!=0)
		{
			if(isnotbetween_q(line,pos,n))// '/*' '//' not within ""
				return pos;
			else				//else keep on searching in the later part of the string
				str=pos+1;
		}
	}
	while(pos);

	return pos;

}
