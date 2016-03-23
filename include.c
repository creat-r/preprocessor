/*
 *
 *	description:
 *
 *	author: Chaitanya Borah
 *
 *	creation time: Tue Jan 12 15:06:58 2016
 *
 *
 */


#include"header.h"

void include_h(char*,char *,char *);
int getpath(char *,char*);
int is_valid_inclusion(char*);

void include_header(char* tempfile)
{
	char *s1="temp_inc1.tmp",*s2="temp_inc2.tmp";
	char ch;
	FILE *fp1=fopen(s1,"w");
	FILE *fp=fopen(tempfile,"r");
	while((ch=fgetc(fp))!=EOF)
	{
		fputc(ch,fp1);
	}
	rewind(fp);
	fclose(fp1);
	include_h(s1,s2,tempfile);
}


void include_h(char *s1,char * s2, char *tempfile)
{
	char ch;
	int flag=0;
	char s[1000];/*make dynamic*/
	char headerpath[50];
	FILE *fp1=fopen(s1,"r");	
	if(fp1==0)	
	{
		perror("fopen");
	}
	FILE *fp2=fopen(s2,"w");	
	if(fp2==0)	
	{
		perror("fopen");
	}

	while(fgets(s,1000,fp1) && flag<2)
	{
		/*to check for valid inclusion of header file*/
		if(is_valid_inclusion(s))
		{
			flag=1;
			/*function that assign the path of the header file to *headername*/
			int status=getpath(headerpath,s);
	//		printf("%s\n",headerpath);
			/*open the header file*/
			if(status)
			{
			
			printf("%s found\n",headerpath);
			FILE *header=fopen(headerpath,"r");
	//		if(header==0)
	//		{
	//			printf("%s\n",headerpath);
	//			flag=0;
	//			goto bhag;
	//		}	
			/*writing the header file into the second file*/
				while((ch=fgetc(header))!=EOF)
				{
					fputc(ch,fp2);
				}
				fclose(header);
			}
			else
			{
				printf("%s not found\n",headerpath);
				flag=2;/*missing header*/
			}
		}
		else
		{
			/*else wrting the first file to second file*/	
			fputs(s,fp2);
		}	
	}
//bhag:
	fclose(fp1);
	fclose(fp2);
	/*Make ifnedf functionality to not need below condition to avoid unending loops*/
	if(flag==2)
	{
		flag=0;
	}
	if(flag)
	{
		/*call the function with interchanged arguments*/
		include_h(s2,s1,tempfile);
	}
	else
	{
		printf("Done!\n");
		fp1=fopen(s1,"r");
		FILE *fp=fopen(tempfile,"w");
		/*Finally write the final form to the source file*/
		while((ch=fgetc(fp1))!=EOF)
		{
			fputc(ch,fp);
		}
	}
}

/*rudimentary header checker: does not conseder misplaced ' '*/
int is_valid_inclusion(char*s)
{
	int i,j=0;
	char truncated_s[1000];/*dynamic memory*/
	/*remove all the blank spaces*/
	for(i=0;s[i];i++)
	{
		if(s[i]!=' ')
		{
			truncated_s[j++]=s[i];
		}
	}
	truncated_s[j]=0;
	//strcpy(s,truncated_s);
	//printf("%s\n",truncated_s);
	if(strstr(truncated_s,"#include<") || strstr(truncated_s,"#include\""))
	{
		for(i=9;truncated_s[i];i++)
		{
			if((truncated_s[i]=='>' && truncated_s[8]=='<') || (truncated_s[i]=='"' && truncated_s[8]=='"'))
			{
				return 1;
			}
		}
	}
	
		return 0;
}


/*rudimentary path finder 1-success 0-failure*/
int getpath(char *path,char*s)
{
	int i,j=0,k;
	char truncated_s[1000];/*dynamic memory*/
	/*standard directories*/
	char* std_direc[]={"/usr/include/","/usr/include/c++/4.8/tr1/",
	"/usr/include/linux/","/usr/include/i386-linux-gnu/"
	};
	/*remove all the blank spaces,watch out for space in file name*/
	for(i=0;s[i];i++)
	{
		if(s[i]!=' ')
		{
			truncated_s[j++]=s[i];
		}
	}
	truncated_s[j]=0;
	/*for current directory*/
	if(truncated_s[8]=='"')/*#include"*/
	{	
		char str[]="./";
		/*adding ./ to path*/
		for(j=0;str[j];j++)
		{
			path[j]=str[j];
		}
		char *pos=0;
		pos=strchr(truncated_s,'"');
		if(pos)
		{
			for(i=pos-truncated_s+1;truncated_s[i]!='"';i++)
			{
				path[j++]=truncated_s[i];
			}
		}

		path[j]=0;
		FILE *fp=fopen(path,"r");
		if(fp)
		{
			fclose(fp);
			return 1;
		}
		for(k=0;k<4;k++)
		{
			for(j=0;std_direc[k][j];j++)
			{
				path[j]=std_direc[k][j];
			}
			char *pos=strchr(truncated_s,'"');
			if(pos)
			{
				for(i=pos-truncated_s+1;truncated_s[i]!='"';i++)
				{
					path[j++]=truncated_s[i];
				}
			}
			path[j]=0;
			FILE *fp=fopen(path,"r");
			if(fp)
			{
				fclose(fp);
				return 1;
			}
		}
		return 0;

	}
	else
	{
		/*FOR STANDARD DIRECTORY*/
		/*	char str[]="/usr/include/";*/
		for(k=0;k<4;k++)
		{
			for(j=0;std_direc[k][j];j++)
			{
				path[j]=std_direc[k][j];
			}
			char *pos=strchr(truncated_s,'<');
			if(pos)
			{
				for(i=pos-truncated_s+1;truncated_s[i]!='>';i++)
				{
					path[j++]=truncated_s[i];
				}
			}
			path[j]=0;
			FILE *fp=fopen(path,"r");
			if(fp)
			{
				fclose(fp);
				return 1;
			}
			//	fclose(fp);

		}
		return 0;
	}

}

/*
 *
 * /usr/local/include
 * /libdir/gcc/target/version/include
 * /usr/target/include
 * /usr/include
 *
 */
