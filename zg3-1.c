#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;

void push(char* stack, int* top, char item)
{
    if(*top>=19)
        printf("stack is full\n");
    else
        stack[++(*top)]=item;
    return;
}

char pop(char* stack, int* top)
{
    if(*top==-1)
        printf("stack is empty\n");
    //return stack[(*top)--];
    switch  (stack[(*top)--])   
    { 
        case lparen : return '('; 
        case rparen : return ')'; 
        case plus : return  '+'; 
        case minus : return  '-'; 
        case divide : return '/'; 
        case times : return  '*'; 
        case mod : return  '%'; 
        case eos : return ' '; 
        default : return  operand;  /* no error checking, default is operand */ 
    } 
}


precedence getToken(char *symbol, int *n, char* expr) 
{ /*  get the next token, symbol is the character representation, which is returned, the token is represented by its enumerated value, which is returned in the function name  */ 
    *symbol = expr[(*n)++]; 
    switch  (*symbol)   
    { 
        case '(' : return  lparen; 
        case ')' : return  rparen; 
        case '+' : return  plus; 
        case '-' : return  minus; 
        case '/' : return  divide; 
        case '*' : return  times; 
        case '%' : return  mod; 
        case ' ' : return eos; 
        default : return  operand;  /* no error checking, default is operand */ 
    } 
}

void postfix(char* expr, int top, char* stack) 
{ /*  output the postfix of the expression. 
      The expression string, stack, and the top are global  */ 
    char symbol; 
    int n = 0; 
    int isp[] = { 0,19,12,12,13,13,13,0 };
    int icp[] = { 20,19,12,12,13,13,13,0 };
    precedence token;
    stack[0] = eos; 
    for  (token = getToken(&symbol, &n, expr); token != eos; token = getToken(&symbol, &n, expr))  
    { 
        if (token == operand) 
            printf("%c", symbol); 
        else  if (token == rparen)  
        { /*  unstack tokens until left parenthesis  */ 
            while (stack[top] != lparen) 
                printf("%c",pop(stack,&top)); 
            pop(stack,&top);  
            /* discard the left parenthesis  */ 
        }
        else  
        { /*  remove and print symbols whose isp is greater than or equal to the current token’s icp */ 
            while (isp[stack[top]] >= icp[token]) 
                printf("%c",pop(stack,&top)); 
            push(stack,&top,token); 
        }
    } 
    while ( (token = pop(stack,&top)) != eos) 
        printf("%c",token); 
    printf("\n");
}

int eval(char* expr, int top, char* stack) 
{ /*  evaluate a postfix expression, expr, maintained as a global  variable.
      ‘\0’ is the end of the expression. 
      The stack and  top of the stack are global variables.  
      getToken is used to return the tokentype and the character symbol.  
      Operands are assumed to be single character digits  */ 
    precedence  token; 
    char  symbol; 
    int  op1, op2; 
    int  n = 0;  
    /*  counter for the expression string  */
    token = getToken(&symbol, &n, expr);
    while (token != eos) 
    {
        printf("TOP=%d!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",top);
        if (token == operand) 
            push(stack, &top, symbol-'0'); 
        /* stack insert */ 
        else 
        { /* remove two operands, perform operation, and return result to the stack */ 
            op2 = pop(stack, &top); 
            /* stack delete */ 
            op1 = pop(stack, &top); 
            switch (token) 
            { 
                case plus : push(stack, &top, op1+op2); break; 
                case minus : push(stack, &top, op1-op2); break; 
                case times : push(stack, &top, op1*op2); break; 
                case divide: push(stack, &top, op1/op2); break; 
                case mod : push(stack, &top, op1%op2); 
            } 
        } 
        token = getToken(&symbol, &n, expr); 
    } 
    return pop(stack, &top); 
    /* return result */
}

int main()
{
    int top=0;
    char *expr=(char*)malloc(sizeof(char)*20);
    char* stack=(char*)malloc(sizeof(char)*20);
    printf("Input: ");
    scanf("%20s",expr);
    printf("Postfix: ");
    postfix(expr,top,stack);
    printf("------------------------\n");
    printf("Result: %d\n",eval(expr,top,stack));
    free(expr);
    free(stack);
    return 0;
}
