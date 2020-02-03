
/* COP 3502C Midterm Assignment One
This program is written by: Ashwin Jegatheesan */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define size 100
char infix[size];
char postfix[size];
int stack[size];
int topOfStack = -1;




void push(int input)
{
    stack[++topOfStack] = input;
}

int pop()
{

     return stack[topOfStack--];

}

int priority(char input)
{
    switch(input)
    {
        case ' ':
        return 0;
        case '(':
        return 1;
        case '+':
        case '-':
        return 2;
        case '%':
        case '*':
        case '/':
        return 3;
        case '^':
        return 4;
    }
}

void DeleteSpaces(char *input)
{
    char *p = input;
    char *d = input;

    while(*d != 0)
    {
        *p = *d++;
        if (*p != ' ')
        {
            *p++;
        }
    }
    *p = 0;
}

void convert(char *infix, char *postfix)
 {
        char temp;
        char input;
        int i = 0;
        int j = 0;
        DeleteSpaces(infix);
        push(' ');
         while ((temp = infix[i++]) != '\n')
    {
      if (temp == '(')
      {
        push(temp);
      }
    else if (isalnum(temp))
    {//
        postfix[j++] = temp;
        int tempi = i;
        while (isalnum(infix[tempi]))
        {
            postfix[j++] = infix[tempi]; //Put infix[tempi] into postfix
            i++; //Increment i so we dont come back here next loop
            tempi++;
        }
        postfix[j++] =' '; //Put space at end of number
    }
    else if (temp == ')')
    {
    while (stack[topOfStack] != '(') //
        postfix[j++] = pop();
        input = pop();
    } //
    else
    {
        while (priority(stack[topOfStack]) >= priority(temp))
        postfix[j++] = pop();
        push(temp);
    }
    }
    while (stack[topOfStack] != ' ')
    postfix[j++] = pop();
    postfix[j] = 0;
    }

    int power(int var1, int var2)
    {
        int i;
        int result = 1;
        for (i=0; i < var2; i++)
        {
            result *= var1;
        }
        return result;

    }



int evaluation(char *postfix)
    {
        char temp;
        double exponent;
        int i = 0;
        int var1;
        int var2;
        while((temp = postfix[i++]) != 0)
            {
                if(isdigit(temp))
                {
                    char * temp2 = (char*)malloc(sizeof(char)*100); //Create Buffer
                    int j = 0;
                    temp2[j++] = temp;//Add temp to buffer
                    while(isdigit(postfix[i])) //loop if next character is also digit
                    {
                        temp2[j++] = postfix[i];//add next charcter to buffer
                        i++;//increment i
                    }
                    push(atoi(temp2));
                    i++;
                    free(temp2);
                }
                else
                    {
                        var2 = pop();
                        var1 = pop();
                        switch(temp)
                         {
                            case '+' : push(var1+var2); printf("Adding %d and %d\n", var1, var2);
                            break;
                            case '-' : push(var1-var2); printf("Subtracting %d and %d\n", var1, var2);
                            break;
                            case '*' : push(var1*var2); printf("Multiplying %d and %d\n", var1, var2);
                            break;
                            case '/' : push(var1/var2); printf("Dividing %d and %d\n", var1, var2);
                            break;
                            case '%' : push(var1 % var2); printf("Modding %d and %d\n", var1, var2);
                            break;
                            case '^' : push(power(var1, var2)); printf("Powering %d and %d\n", var1, var2);
                            break;

                        }
                    }
        }
return stack[topOfStack];
    }




int main(void)
{
    int eval;
    int t = 0;
    int p = 0;
    char temp;
    printf("Please enter the infix: ");
    fgets(infix, size, stdin);
     for (int i = 0; i < strlen(infix); i++)
    {
        if (infix[i] == '(')
        {
            t++;
        }
        if (infix[i] == ')')
        {
            p++;
        }
    }
    printf("There are %d open parenthesis and %d closed parenthesis\n", t, p);
    if ( t != p)
    {
        printf("You have entered an invalid expression. The balance of the parenthesis are not equal.\n");
        return 0;
    }
    printf("\n\n\n");
    convert(infix, postfix);
    printf("Infix Expression: %s \n\nPostfix Expression %s\n\n", infix, postfix);
    topOfStack = -1;
    eval = evaluation(postfix);
    printf("Evaluation of the Postfix: %d", eval);




    return 0;
}
