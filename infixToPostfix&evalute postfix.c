#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
typedef struct
{
    float data;
    struct node*next;
} node;
node*newnode(float x)
{
    node*n=malloc(sizeof(node));
    n->data=x;
    n->next=NULL;
    return n;
}
//goz2 el linked list
typedef struct
{
    node*top;
} stack; //stack fyha pointer 3la awl node bs mfehash items(data)...l data mwgoda fel node
stack* init()
{
    stack*s=malloc(sizeof(stack));
    s->top=NULL;
    return s;
}
void push (stack*s,float x)
{
    node*n=newnode(x);
    n->next=s->top;
    s->top=n;
}
float pop(stack*s)
{
    float value;
    if (!s->top)
        printf("stack is empty!\n");
    else
    {
        node*temp=s->top;
        s->top=s->top->next;
        value=temp->data;
        free(temp);
        //printf("%d\n",value); test push & pop
    }
    return value;
}
float peek (stack*s)
{
    return s->top->data;
}
int isempty (stack*s)
{
    if (s->top==NULL)
        return 1;
    return 0;
}
int priority (char c)
{
    switch(c)
    {
    case '(':
        return 3 ;
    case '^':
        return 2;
    case '*':
    case '%':
    case '/':
        return 1 ;
    case '+':
    case '-':
        return 0 ;
    }
}
float evaluate (char c,float x,float y)
{
    float value;
    switch (c)
    {
    case ('^'):
        value=pow(x,y);
        return value;
    case ('*'):
        value=x*y;
        return value;
    case ('+'):
        return x+y;
    case ('-'):
        value=x-y;
        return value;
    case ('/'):
        value=x/y;
        return value;
        //case ('%'):
        //  value=x%y;
        //return value;
    }
}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME multi-digit operands
* ASSUME ^*+-/ operators
* e.g., 22 + 31 --> 22 31 +
* e.g., ( 2 + 3 ) * 4 --> 2 3 + 4 *
*/
char*  infixToPostfix(char* infix)
{
    int i,length,j,index=0;
    int count =0;
    int flag=1;
//    char *infix=strtok(infix1," ");
    length=strlen(infix);
    //printf("sizeof length=%d\n",length);
    char*postfix=malloc(100);
    stack*s=init();
    char multidigit[1];
    float term;
    for (i=0; i<length; i++)
    {
        //printf("helo\n");
        if (infix[i]!=' ')
        {
            j=i+1;
            if(!(j==length))
            {
                if(!i)//handel lw fe negtive a awl rkm 5ales
                {

                    if (infix[i]=='-')
                    {
                        /*do
                        {               printf("%d",0);

                            flag=0;
                            postfix[index++]=infix[i];
                         i++;
                        }while(isdigit(infix[i])||infix[i]=='.');
                        i--;
                        */
                        postfix[index++]=infix[i];
                        i++;
                        while(isdigit(infix[i])||infix[i]=='.')
                        {
                            flag=0;
                            //          printf("0");
                            postfix[index++]=infix[i];
                            i++;
                        }
                        postfix[index++]=' ';

                    }

                }


                if (isdigit(infix[i])&&infix[j]=='.'&&flag)
                {
                    //printf("1");
                    while (isdigit(infix[i])||infix[i]=='.')
                    {
                        //  multidigit[count]=infix[i];
                        // count++;
                        postfix[index++]=infix[i];
                        i++;
                    }
                    i--;
                    //count=0;
                    //  postfix[index++]= atof(multidigit);
                    postfix[index++]=' ';
                }

                else if (infix[i]=='-'&&(infix[i-1]=='%'||infix[i-1]=='('||

                                         infix[i-1]=='*'||
                                         infix[i-1]=='/'||
                                         infix[i-1]=='+'||
                                         infix[i-1]=='-'))//handel l negtive f nos l rkm
                {

                    postfix[index++]=infix[i];
                    i++;
                    while(isdigit(infix[i])||infix[i]=='.')
                    {

                        //   printf(":>");
                        postfix[index++]=infix[i];
                        i++;
                    }
                    i--;
                    postfix[index++]=' ';

                }

                else if (isdigit(infix[i])&&!isdigit(infix[j]))
                {
                    //printf("2");
                    postfix[index++]=infix[i];
                    postfix[index++]=' ';

                }

                else if (infix[i]==')')
                {
                    //printf("3");

                    while (peek(s)!='(')
                    {
                        postfix[index++]=pop(s);
                        postfix[index++]=' ';
                    }
                    pop(s);
                }
                else if (isempty(s)&&!isdigit(infix[i]))
                {
                    //printf("4");

                    push(s,infix[i]);
                }
                else if (isdigit(infix[i])&&isdigit(infix[j]))
                {
                    //    printf("5");

                    while (isdigit(infix[i])||infix[i]=='.')
                    {
                        // multidigit[count]=infix[i];
                        //count=count+1;
                        postfix[index++]=infix[i];

                        i++;
                    }
                    i--;
                    // count=0;
                    //printf("\nmultidigit =%s\n",multidigit);
                    //term=atof(multidigit);
                    //postfix[index++]=multidigit;
                    // printf("\nterm =%f and i =%d\n",term,i);
                    postfix[index++]=' ';
                }
                else
                {
                    //  printf("6");

                    while(!isempty(s)&& peek(s)!='('&& priority(peek(s))>=priority(infix[i]))
                    {
                        postfix[index++]=pop(s);
                        postfix[index++]=' ';

                    }
                    push(s,infix[i]);
                }
            }
            else
            {
                printf("7");
                if(isdigit(infix[i]))
                {
                    postfix[index++]=infix[i];
                    postfix[index++]=' ';
                }
                else // aked  closed braket
                {
                    while (peek(s)!='(')
                    {
                        postfix[index++]=pop(s);
                        postfix[index++]=' ';
                    }
                    pop(s);
                }
            }

        }
    }
    while(!isempty(s))
    {
        postfix[index++]=pop(s);
        postfix[index++]=' ';
    }
    index--;
    postfix[index]='\0';
    return postfix;
}

/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/

float evaluatePostfix(char* postfix)
{
    int i;
    int length;
    float n1,n2,value;
    stack*s=init();
//   printf("\n post =%s",postfix);
//    printf("\n postfix length=%d\n",strlen(postfix));
    //  printf("%c",postfix[6]);
    //  printf("%c",'\0');
    char*token=strtok(postfix," ");
//printf("\n token =%f",atof(token));
    push(s,atof(token));
//printf("\npeek=%f",peek(s));
    while(1)
    {
        // printf("\nd5l mra\n");
        token=strtok(NULL," ");
        if (token==NULL)
            return pop(s);
        // printf("\n new token =%f",atof(token));
        // printf("\n new token =%c",token[0]);
        length=strlen(token);
        //printf("\nlength of this token=%d\n",length);

        if (length==1&&isdigit(token[0]))
        {
            value=atof(token);
            // printf("\nvalue el d5la stack=%f",token);
            push(s,value);
        }

        else if(length==1&&!isdigit(token[0]))
        {
            n2=pop(s);
            n1=pop(s);
            // printf("\ntoken l ryha levalute%c ",token[0]);
            value =evaluate(token[0],n1,n2);
            // printf("\nvalue el d5la stack=%.02f",value);
            push(s,value);
            // printf("\n el valee peek=%.02f",peek(s));
        }
        else // aked rkm positive aw rkm awlo negtive
        {
            value=atof(token);
            push(s,value);
        }

    }

//   value =pop(s);
    // printf("\nvalue l httb3t l main=%f",value);
    // return value;
}



void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
*
*/
int main()
{
    char infix[]="1+2*4+3 ";
    printf("Infix: %s\n",infix);
    char*postfix=infixToPostfix(infix);
    printf("Postfix: %s",postfix);
    float x=evaluatePostfix(postfix);
    printf("\nResult =%.1f",x);




    char infix2[]="(1+2)*4+3";
    printf("\n\nInfix: %s\n",infix2);
    char*postfix2=infixToPostfix(infix2);
    printf("Postfix: %s",postfix2);
    float x2=evaluatePostfix(postfix2);
    printf("\nResult =%.1f",x2);


    char infix3[]="10+3*5/(16-4)";
    printf("\n\nInfix: %s\n",infix3);
    char*postfix3=infixToPostfix(infix3);
    printf("Postfix: %s",postfix3);
    float x3=evaluatePostfix(postfix3);
    printf("\nResult =%.2f",x3);



    char infix4[]="2+3*4";
    printf("\n\nInfix: %s\n",infix4);
    char*postfix4=infixToPostfix(infix4);
    printf("Postfix: %s",postfix4);
    float x4=evaluatePostfix(postfix4);
    printf("\nResult =%.1f",x4);



    char infix5[]="2+(-2.5+3.14)*(-5.4+8.1)^(-0.5)";
    printf("\n\nInfix: %s\n",infix5);
    char*postfix5=infixToPostfix(infix5);
    printf("Postfix: %s",postfix5);
    float x5=evaluatePostfix(postfix5);
    printf("\nResult =%f\n\n",x5);


    char infixExpr[256] = "";

    printf("\nEnter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        char*postfix=infixToPostfix(infixExpr);
        printf("Postfix : %s\n", postfix);
        float result = evaluatePostfix(postfix);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }


    /* char x=' ';
     stack*s=init();
     push(s,4);
     push(s,7.2);
     push(s,x);
     */
    /*
    push(s,8);
    printf("%f  ",peek(s));
    pop(s);
    printf("%c  ",peek(s));
    pop(s);
    printf("%f  ",peek(s));
    */
    //   char infix[]="10";
//float test = atof(infix);
//printf("%f",test);
//char ahmed[5];
//ahmed[0]=test;
//ahmed[1]='5';
//ahmed[2]='a';
//printf("%s",ahmed);


    /*
        int i;
        char multidigit[100];
        float term;
        int count=0;
        while (isdigit(infix[i]))
        {
            printf("hi");
            multidigit[count]=infix[i];
            count=count+1;
            i++;
        }
        printf("\nmultidigit =%s\n",multidigit);
        term=atof(multidigit);
        printf("\nterm =%f\n",term);
        printf("value of i %d",i);
    */
    return 0;
}
