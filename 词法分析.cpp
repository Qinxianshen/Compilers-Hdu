#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char word[1000];
char scan[100];
int line=1;
int t=0,i=0,sum=0;
char c;

void scanner()
{
	for(i=0;i<100;i++)
		scan[i]=NULL;
	i=0;
	c=word[t++];
	while(c==' ')
	{
		c=word[t];
		t++;
	}
	if(c>='a' && c<='z' || c>='A' && c<='Z')
	{
		while(c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9')
		{
			scan[i++]=c;
			c=word[t++];
		}
		scan[i++]='\0';
		if(!strcmp(scan,"Const") || !strcmp(scan,"Var") || !strcmp(scan,"if") || !strcmp(scan,"then") || !strcmp(scan,"else") || !strcmp(scan,"while") || !strcmp(scan,"do") || !strcmp(scan,"begin") || !strcmp(scan,"end"))
			printf("%d: Reserved words : %s\n",line,scan);
		else
			printf("%d: Identifier : %s\n",line,scan);
		t--;
		i=0;
	}
	else if(c>='0' && c<='9')
	{
		while(c>='0' && c<='9')
		{
			scan[i++]=c;
			c=word[t++];
		}
        char temp = c;
        if((temp>='a' && temp<='z')|| (temp >= 'A' && temp <= 'Z'))
        {
            t--;
            c = word[t];
            printf("Identifier error: %d    \n",line  );
            while((c>='a' && c<='z')|| (c >= 'A' && c <= 'Z') || (c >= '0' && c<= '9' ))
            {
              c = word[t++];
            }

        //exit(0);
        }
        else
            printf("%d: Number : %s\n",line,scan);
		t--;
		i=0;
	}
	else if(c=='\n')
		line++;
	else
	{
		switch(c)
		{
			case '>':
			i=0;
			scan[i++]=c;
			c=word[t++];
			t--;
			if(c=='=')
			{
				scan[i++]=c;
				scan[i]='\0';
				i=0;
				printf("%d: %s\n",line,scan);
				break;
			}
			else
			{
				i=0;
				printf("%d: %s\n",line,scan);
				break;
			}
			case '<':
			i=0;
			scan[i++]=c;
			c=word[t++];
			t--;
			if(c=='=')
			{
				scan[i++]=c;
				scan[i]='\0';
				i=0;
				printf("%d: %s\n",line,scan);
				break;
			}
			else if(c=='>')
			{
				scan[i++]=c;
				scan[i]='\0';
				i=0;
				printf("%d: %s\n",line,scan);
				break;
			}
			else
			{
				i=0;
				printf("%d: %s\n",line,scan);
				break;
			}
			case '=':
			i=0;
			scan[i++]=c;
			c=word[t++];
			t--;
			if(c=='=')
			{
				scan[i++]=c;
				scan[i]='\0';
				i=0;
				printf("%d: %s\n",line,scan);
				break;
			}
			else
			{
				i=0;
				printf("%d: %s\n",line,scan);
				break;
			}
			case ',':scan[0]=c;printf("%d: %s\n",line,scan);break;
			case ';':scan[0]=c;printf("%d: %s\n",line,scan);break;
			case '(':scan[0]=c;printf("%d: %s\n",line,scan);break;
			case ')':scan[0]=c;printf("%d: %s\n",line,scan);break;
			case '+':scan[0]=c;printf("%d: %s\n",line,scan);break;
			case '-':scan[0]=c;printf("%d: %s\n",line,scan);break;
			case '*':scan[0]=c;printf("%d: %s\n",line,scan);break;
			case '/':scan[0]=c;printf("%d: %s\n",line,scan);break;
			default:printf("Error!");
		}
	}
}

int main()
{
	char ch;
	FILE *fp;
	fp=fopen("examplse2.txt","r");
	int p=0;
	while((ch=fgetc(fp))!=EOF)
		word[p++]=ch;
	while(t!=p)
		scanner();
	fclose(fp);
}
