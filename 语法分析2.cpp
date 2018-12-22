#include <stdio.h>
#include <string.h>
char word[1000];
char scan[100];
int line=1;
int t=0,i=0,sum=0;
char c;
int syn=0;

void scanner();
void program();
void constExp(int shendu);
void constDef(int shendu);
void constRec(int shendu);
void uInt(int shendu);
void ide(int shendu);
void varExp(int shendu);
void ideRec(int shendu);
void sen(int shendu);
void assSen(int shendu);
void expression(int shendu);
void itemRec(int shendu);
void item(int shendu);
void factorRec(int shendu);
void factor(int shendu);
void addOpt(int shendu);
void mulOpt(int shendu);
void conSen(int shendu);
void conOpt(int shendu);
void condition(int shendu);
void relOpt(int shendu);
void cirSen(int shendu);
void comSen(int shendu);
void senRec(int shendu);
void scanner();


/*
1: Const
2: Var
3: if
4: then
5: else
6: while
7: do
8: begin
9: end
10: Indetifier
11: Number
12: >=
13: >
14: <=
15: <>
16: <
17: ==
18: =
19: ,
20: ;
21: (
22: )
23: +
24: -
25: *
26: /
*/

void star(int shendu){       //用于输出所在层次****
	for(int i=0;i<shendu;i++)
		printf("****");
}


void program()  // <程序>→[<常量说明>][<变量说明>]<语句>
{
	int shendu=1;//常量说明
	if(syn==1)
	{
		star(shendu);
		printf("constExp\n");
		constExp(shendu);
	}
	else if(syn==2)//变量说明
	{
		star(shendu);
		printf("VarExp\n");
		varExp(shendu);
	}
	else if(syn==3 || syn==6 || syn==8)//语句
	{
		star(shendu);
		printf("Sen\n");
		sen(shendu);
	}
}

void constExp(int shendu)   //<常量说明>→Const <常量定义>{，<常量定义>}；
{
	if(syn==1)
	{
		shendu++;
		star(shendu);
		printf("Const\n");
		scanner(   );
		constDef(shendu);  //常量定义
		if(syn==20)
		{
			star(shendu);
			printf(";\n");

			scanner();
			program();
		}
		else
			printf("; Error!\n");
	}
	else
		printf("const Error!\n");
}
void varExp(int shendu)
{
	if(syn==2)
	{
		shendu++;
		star(shendu);
		printf("Var\n");
		scanner();
		ide(shendu);
		ideRec(shendu);
		if(syn==20)
		{
			star(shendu);
			printf(";\n");
			scanner();
			program();
		}
		else
			printf("; Error!\n");
	}
	else
		printf("var Error!\n");
}
void constDef(int shendu)  // <常量定义>→<标识符>＝<无符号整数>
{
	star(shendu);
	printf("ConstDef\n");
	shendu++;
	ide(shendu);
	if(syn==18)
	{
		star(shendu);
		printf("=\n");
		scanner(    );
		uInt(shendu);
		constRec(shendu-1);
	}
	else
		printf("constDef Error!\n");
}
void constRec(int shendu)
{
	if(syn==19)
	{
		star(shendu);
		printf(",\n");
		scanner();
		constDef(shendu);
	}
}
void uInt(int shendu)
{
	if(syn==11)
	{
		star(shendu);
		printf("Number: %s\n",scan);
		scanner();
	}
	else
		printf("Number Error!");
}

void ide(int shendu)
{
	if(syn==10)
	{
		star(shendu);
		printf("Identifier: %s\n",scan);
		scanner();
		//printf("%d",syn);
		//ideRec();
	}
	else
		printf("Identifier Error!");
}
void ideRec(int shendu)
{
	if(syn==19)
	{
		star(shendu);
		printf(",\n");
		scanner();
		ide(shendu);
		ideRec(shendu);
	}
}

void sen(int shendu)
{//<语句>→<赋值语句>|<条件语句>|<当循环语句>|<复合语句>|ε
	shendu++;
	if(syn==10)
	{
		star(shendu);
		printf("assSen\n");
		assSen(shendu);   //赋值语句
	}
	else if(syn==8)
	{
		star(shendu);
		printf("comSen\n");
		comSen(shendu);
	}
	else if(syn==3)
	{
		star(shendu);
		printf("conSen\n");
		conSen(shendu);
	}
	else if(syn==6)
	{
		star(shendu);
		printf("cirSen\n");
		cirSen(shendu);
	}
}
void assSen(int shendu)//<赋值语句>→<标识符>＝<表达式>;
{
	shendu++;
	ide(shendu);   // 标识符
	if(syn==18)
	{
		star(shendu);
		printf("=\n");
		scanner();
		expression(shendu);  //表达式

		if(syn==20)
		{
			star(shendu);
			printf(";\n");
			scanner();
			sen(shendu-2);
		}
		else
			printf(";Error!\n");
	}
	else
		printf("assSen Error!");
}
void expression(int shendu)  //<表达式>→[＋|－]<项>{<加法运算符><项>}
{
	addOpt(shendu);   //+-符号
	item(shendu);   // 项
}
void item(int shendu) // <项>→<因子>{<乘法运算符><因子>}
{
	factor(shendu);   // 因子
	factorRec(shendu+1);     //乘法项
}
void itemRec(int shendu)    //??????????
{
	addOpt(shendu);
	item(shendu);
}
void factor(int shendu)  //<项>→<因子>{<乘法运算符><因子>}
{
	if(syn==10)
	{
		ide(shendu);  //标识符
		factorRec(shendu);
	}
	else if(syn==11)
	{
		uInt(shendu);     //整数
		factorRec(shendu+1);
	}
	else if(syn==21) //表达式
	{
		star(shendu);
		printf("(\n");
		scanner();
		expression(shendu);
		if(syn==22)
		{
			star(shendu);
			printf(")\n");
			scanner();
			factorRec(shendu+1);
		}
		else
			printf("expression Error!");
	}
}
void factorRec(int shendu)     //乘法项
{
	//star(shendu-1);
	//printf("factorRec\n");
	addOpt(shendu);
	mulOpt(shendu);
	factor(shendu);
}
void addOpt(int shendu)  //+-运算符
{
	if(syn==23)
	{
		star(shendu);
		printf("+\n");
		scanner();
	}
	else if(syn==24)
	{
		star(shendu);
		printf("-\n");
		scanner();
	}
}
void mulOpt(int shendu)
{
	if(syn==25)
	{
		star(shendu);
		printf("*\n");
		scanner();
	}
	else if(syn==26)
	{
		star(shendu);
		printf("/\n");
		scanner();
	}
}
void conSen(int shendu)
//<条件语句>→if <条件> then <语句>| if <条件> then <语句> else <语句>
{
	shendu++;
	if(syn==3)
	{
		star(shendu);
		printf("if\n");
		scanner();
		condition(shendu);
		if(syn==4)     //是不是少了then？
		{
			star(shendu);
			printf("then\n");
			scanner();
			sen(shendu-1);
			conOpt(shendu);
		}
		else
			printf("then Error!");
	}
	else
		printf("if Error!");
}
void conOpt(int shendu)
{
	if(syn==5)
	{
		star(shendu);
		printf("else\n");
		scanner();                //少输了else
		sen(shendu-1);
	}
}
void condition(int shendu)  //<条件>→<表达式><关系运算符><表达式>
{
	expression(shendu);
	relOpt(shendu);
	expression(shendu);
}
void relOpt(int shendu)
{
	if(syn==12)
	{
		star(shendu);
		printf(">=\n");
		scanner();
	}
	else if(syn==14)
	{
		star(shendu);
		printf("<=\n");
		scanner();
	}
	else if(syn==15)
	{
		star(shendu);
		printf("<>\n");
		scanner();
	}
	else if(syn==18)
	{
		star(shendu);
		printf("==\n");
		scanner();
	}
	else if(syn==13)
	{
		star(shendu);
		printf(">\n");
		scanner();
	}
	else if(syn==16)
	{
		star(shendu);
		printf("<\n");
		scanner();
	}
	else
		printf("relOpt Error!");
}
void cirSen(int shendu)    //<当循环语句>→while <条件> do <语句>
{
	shendu++;
	if(syn==6)
	{
		star(shendu);
		printf("while\n");
		scanner();
		condition(shendu);
		if(syn==7)                //是不是少输出了do
		{
			star(shendu);
			printf("do\n");
			scanner();
			sen(shendu-1);
		}
		else
			printf("do Error!\n");
	}
	else
		printf("while Error!\n");
}
void comSen(int shendu)   //<复合语句>→begin <语句>{；<语句>} end
{
	shendu++;
	if(syn==8)
	{
		star(shendu);
		printf("begin\n");
		scanner();
		sen(shendu-1);
		if(syn==9)
		{
			star(shendu);
			printf("end\n");
			scanner();
			sen(shendu-2);
			senRec(shendu-2);    //多个语句
		}
		else
			printf("end Error!\n");
	}
	else
		printf("begin Error!\n");
}
void senRec(int shendu)
{
	sen(shendu);
}

void scanner()
{
	for(i=0;i<100;i++)
		scan[i]=NULL;
	i=0;
	c=word[t++];
	while(c==' ' || c=='\n')
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
		if(!strcmp(scan,"Const"))
			syn=1;
		else if(!strcmp(scan,"Var"))
			syn=2;
		else if(!strcmp(scan,"if"))
			syn=3;
		else if(!strcmp(scan,"then"))
			syn=4;
		else if(!strcmp(scan,"else"))
			syn=5;
		else if(!strcmp(scan,"while"))
			syn=6;
		else if(!strcmp(scan,"do"))
			syn=7;
		else if(!strcmp(scan,"begin"))
			syn=8;
		else if(!strcmp(scan,"end"))
			syn=9;
		else
			syn=10;
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
		syn=11;
		t--;
		i=0;
	}
	//else if(c=='\n')
		//line++;
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
				syn=12;
				scan[i++]=c;
				scan[i]='\0';
				i=0;
				//printf("%d: %s\n",line,scan);
				break;
			}
			else
			{
				syn=13;
				i=0;
				//printf("%d: %s\n",line,scan);
				break;
			}
			case '<':
			i=0;
			scan[i++]=c;
			c=word[t++];
			t--;
			if(c=='=')
			{
				syn=14;
				scan[i++]=c;
				scan[i]='\0';
				i=0;
				//printf("%d: %s\n",line,scan);
				break;
			}
			else if(c=='>')
			{
				syn=15;
				scan[i++]=c;
				scan[i]='\0';
				i=0;
				//printf("%d: %s\n",line,scan);
				break;
			}
			else
			{
				syn=16;
				i=0;
				//printf("%d: %s\n",line,scan);
				break;
			}
			case '=':
			i=0;
			scan[i++]=c;
			c=word[t++];
			t--;
			if(c=='=')
			{
				syn=17;
				scan[i++]=c;
				scan[i]='\0';
				i=0;
				//printf("%d: %s\n",line,scan);
				break;
			}
			else
			{
				syn=18;
				i=0;
				//printf("%d: %s\n",line,scan);
				break;
			}
			case ',':syn=19;scan[0]=c;break;
			case ';':syn=20;scan[0]=c;break;
			case '(':syn=21;scan[0]=c;break;
			case ')':syn=22;scan[0]=c;break;
			case '+':syn=23;scan[0]=c;break;
			case '-':syn=24;scan[0]=c;break;
			case '*':syn=25;scan[0]=c;break;
			case '/':syn=26;scan[0]=c;break;
		}
	}
}

int main()
{
	char ch;
	FILE *fp;
	fp=fopen("./examplse2.txt","r");
	int p=0;
	while((ch=fgetc(fp))!=EOF)
		word[p++]=ch;
	printf("program\n");
	scanner();
	program();
	fclose(fp);
}
