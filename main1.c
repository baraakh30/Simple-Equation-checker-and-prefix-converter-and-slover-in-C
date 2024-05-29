//Name : Baraa Khanfar
// Id : 1210640
//section No : 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct Node
{
    int data;
    struct Node* next;
};

typedef struct Node Node;
// linked list implemented stack
struct stack
{
    Node* top;
    int size;
};


typedef struct stack Stack;
// list for the equations list
struct eqList
{
    char* data;
    struct eqList* next;
    int size;
};
typedef struct eqList list;

// creating and returning a stacks
Stack* initialize()
{
    Stack* s = (Stack*) malloc(sizeof(Stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

//freeing the equations list
void freeList(list* l)
{
    if(l==NULL) return;
    list* current= l;
    while(current!=NULL)
    {
        list* temp= current;
        if(current->data!=NULL)
            free(current->data);
        current=current->next;
        free(temp);

    }

}
//initializing the list
list* createList()
{
    list* l = (list*) malloc(sizeof(list));
    l->data=NULL;
    l->next=NULL;
    l->size=0;
    return l;
}

//creating a list to insert it to to initial list
list* createListNode(char* eq)
{
    list* l = (list*) malloc(sizeof(list));
    l->data=eq;
    l->next=NULL;
    l->size=0;
    return l;
}
//inserting at the end of the list
void insertToList(list* l,char* eq)
{
    if(l==NULL) return;
    if(l->data==NULL)
    {
        l->data=eq;
        l->size++;
        return;
    }

    list* current= l;
    while(current->next!=NULL)
    {
        current=current->next;
    }
    current->next=createListNode(eq);
    l->size++;
    return;

}

//returning 1 if the stack is empty
int isEmpty(Stack* s)
{
    return s->size == 0;
}
//inserting at the top of the stack
void push(Stack* s, int c)
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = c;
    node->next = s->top;
    s->top = node;
    s->size++;
}
//deleting the top element
int pop(Stack* s)
{
    if (isEmpty(s))
    {
        printf("Stack underflow!\n");
        return '\0';
    }

    Node* temp = s->top;
    int c = temp->data;
    s->top = temp->next;
    free(temp);
    s->size--;
    return c;
}

//returning the top element without deleting it
int peek(Stack* s)
{
    if (isEmpty(s))
    {
        printf("Stack underflow!\n");
        return '\0';
    }
    return s->top->data;
}

//freeing the stack and its data
void destroyStack(Stack* s)
{
    if(s==NULL) return;
    if(s->size==0)
    {
        free(s);
        return;
    }
    Node* current=s->top;
    while (current != NULL)
    {
        Node* temp =current;
        current = temp->next;
        free(temp);
    }
    free(s);
}


//checking the character if its an operator or not
int isOperator(char c)
{
    return (c=='+' || c== '-' || c=='*' || c=='/');
}

//getting the priority of the operator
int operatorPriority(char c)
{
    switch (c)
    {
    case '*' :
    case '/' :
        return 2;
    case '+' :
    case '-' :
        return 1;
    default :
        return 0;

    }
}
//as the name says
char getOppositeParenthesis(char p)
{
    switch(p)
    {
    case ')' :
        return '(';
    case '(' :
        return ')';

    case ']' :
        return '[';
    case '[' :
        return ']';

    case '}' :
        return '{';
    case '{' :
        return '}';
    default:
        return 0;

    }
}

//checking if the close parenthesis is matching with the open
int areMatching(char first, char second)
{

    if (first == '{' && second == '}')
        return 1;
    else if (first == '[' && second == ']')
        return 1;
    else if (first == '(' && second == ')')
        return 1;
    else
        return 0;
}

//checking if the character is an open parenthesis
int isOpenParenthesis(char x)
{
    return x == '(' || x == '[' || x == '{';
}

// check if the char is an close parenthesis
int isCloseParenthesis(char x)
{
    return x == ')' || x == ']' || x == '}';
}

int isBalanced(char* eq,int mode)     // check the validity of parenthesis
{
    Stack* temp= initialize();
    int i,len=strlen(eq);
    for (i = 0; i < len; i++)   // traverse every index in the equation
    {
        if (isOpenParenthesis(eq[i])) //pushing the character if its an open parenthsesis
            push(temp,eq[i]);
        else if (isCloseParenthesis(eq[i]))
        {
            if (isEmpty(temp) || !areMatching(peek(temp), eq[i])) // checking if the stack is empty(no open parenthesis added)
            {
                // or the peek of the stack isnt matching with the close parenthesis
                if(mode)
                    printf("%s : Invalid , Reason : Close paranthesis %c isnt opened",eq,eq[i]);
                return 0;
            }
            else
            {
                pop(temp);
            }
        }
    }
    if(isEmpty(temp)) // if the stack is empty it means that no open parenthesis are lift not closed
    {
        destroyStack(temp); //freeing the stack
        return 1;
    }
    if(mode)
        printf("%s : Invalid , Reason : Open paranthesis : %c isnt closed",eq,peek(temp));
    destroyStack(temp);
    return 0;
}

//checking if the equation is valid or not
// the mode is for determining to print the reason or not
int isValid(char* eq,int mode)
{

    int len=strlen(eq)-1;
    // Check for invalid characters at the beginning and end of the equation
    if(isOperator(eq[0]) && (eq[0] != '-' || !isdigit(eq[1]))) //operator at the beginning and its not a negative number
    {
        if(mode)
            printf("%s : Invalid , Reason : The Equation starts with an Operator : %c\n",eq,eq[0]);
        return 0;
    }
    //the reasons is shown at the print statement
    if(isCloseParenthesis(eq[0])) //the equation starts with an close parenthesis
    {
        if(mode)
            printf("%s : Invalid , Reason : The Equation starts with a Close Parenthesis : %c\n",eq,eq[0]);
        return 0;
    }
    if(isOperator(eq[len]))
    {
        if(mode)
            printf("%s : Invalid , Reason : The Equation ends with an operator : %c\n",eq,eq[len]);
        return 0;
    }
    if(isOpenParenthesis(eq[len]))
    {
        if(mode)
            printf("%s : Invalid , Reason : The Equation ends with a open Parenthesis : %c\n",eq,eq[len]);
        return 0;
    }

    // Check for invalid combinations of characters within the equation
    for (int i = 0; i <= len; i++)
    {
        if(eq[i]==' ') continue;

        if (isOperator(eq[i]) && (i >=len || (isOperator(eq[i+1]) && eq[i+1] !='-') ))
        {
            // Two operators in a row or an operator at the end of the equation
            if(mode)
                printf("%s : Invalid , Reason : Two operators in row : %c %c\n",eq,eq[i],eq[i+1]);
            return 0;
        }
        else if (eq[i] == '/' && (i >=len || eq[i+1] == '0'))
        {
            // Division by zero
            if(mode)
                printf("%s : Invalid , Reason : Division by zero : %c %c\n",eq,eq[i],eq[i+1]);
            return 0;
        }

        else if ((isdigit(eq[i]) && (i  < len && isOpenParenthesis(eq[i+1])) )  || (isCloseParenthesis(eq[i]) && (i < len && isdigit(eq[i+1]))) || (isCloseParenthesis(eq[i]) && (i < len && isOpenParenthesis(eq[i+1]))))
        {
            // No operator between the digit and the open parenthesis
            //or No operator between the c parenthesis and the digit
            // or No digit between the operator and the close parenthesis
            if(mode)
                printf("%s : Invalid , Reason : No operator between %c and %c\n",eq,eq[i],eq[i+1]);
            return 0;
        }
        else if ((isOpenParenthesis(eq[i]) && (i < len && eq[i+1] !='-' &&isOperator(eq[i+1])))  ||  (isOperator(eq[i]) && (i < len && isCloseParenthesis(eq[i+1]))) )
        {
            // No digit between the open parenthesis and the operator
            //Or No digit between the operator and the close parenthesis
            if(mode)
                printf("%s : Invalid , Reason : No digit between %c and %c\n",eq,eq[i],eq[i+1]);
            return 0;
        }

    }
    // Check if the equation has balanced parentheses
    return isBalanced(eq,mode);
}

int hasHigherP(char op1, char op2)   // return that the first operator has higher priority than the other one
{
    int p1 = operatorPriority(op1);
    int p2 = operatorPriority(op2);

    return p1 > p2;
}
//converting the reversed string of the equation to postfix
char* convertToPostfix(char* input)
{
    Stack* temp=initialize();
    int len = strlen(input); //calculating the length of the inoput
    char* eq=(char*) malloc(len*2*sizeof(char)); //allocating the postfix equation
    int i,j;
    for (i = 0,j=0; i <len; i++)
    {

        if (isdigit(input[i]))
        {
            eq[j++] = input[i];

            while(i+1<len&&isdigit(input[i+1])) //keep adding the continuous numbers
            {
                i++;
                eq[j++] = input[i];
            }
            // if number is negative it self
            // this will check if the number is followed by -
            //and its the last number or its not followed by and open parenthesis nor a digit
            if(i+1 < len && input[i+1] == '-' &&  (i+1==len-1 || (!isOpenParenthesis(input[i+2]) && !isdigit(input[i+2])) ))
            {

                i++;
                eq[j++]='-'; //adding - to the number if its negative
            }

            eq[j++] = ' '; //adding spaces between numbers
        }
        else if (isOperator(input[i]))
        {

            while (!isEmpty(temp) && isOperator(peek(temp)) && hasHigherP(peek(temp), input[i])) // checking that the current operators at the stack has more
                // priority than the current operator , if not it will pop them
                // and then push the current operator to the stack
            {
                eq[j++] = pop(temp);
                eq[j++] = ' '; // adding spaces between the elements
            }
            push(temp, input[i]);


        }
        else if (isOpenParenthesis(input[i])) // it will push the open parenthesis
        {
            push(temp, input[i]);
        }
        else if (isCloseParenthesis(input[i]))                       //if the current element is a close parenthesis
        {
            while (!isEmpty(temp) && !isOpenParenthesis(peek(temp))) // popping every element at the stack
                //until its empty or the peek of the stack
                //isnt the open parenthesis
            {
                eq[j++] = pop(temp);
                eq[j++] = ' ';
            }
            pop(temp); // remove the opening parenthesis
        }
    }
    while (!isEmpty(temp)) // popping the elements left at the stack
    {
        eq[j++] = pop(temp);
        eq[j++] = ' '; //adding spaces
    }

    destroyStack (temp);
    eq=(char*)realloc(eq,j*sizeof(char));
    eq[j-1] = '\0';

    return eq;
}
int parseInt(char* number) //returning the integer from a string
{
    int len=strlen(number),sum=0,sign=0;
    for(int i=0; i<len; i++)
    {
        if(number[i] == '-')   sign=1;   //if the number contains - , we will return its negative
        else
            sum+=(number[i]-'0') * pow(10,i);
    }
    if(sign) return -1*sum;
    return sum;
}
int evaluatePrefix (char* prefix)
{
    int len=strlen(prefix);
    Stack* operands = initialize();
    //traversing the prefix from the end
    for(int i=len-1; i>=0; i--)
    {
        if(prefix[i]==' ') continue;
        else if(isdigit(prefix[i]))
        {
            int j=0;
            char* numbers=(char*) malloc(100*sizeof(char)); //string to add the continuous numbers to it
            numbers[0]=prefix[i];

            while(i-1>=0 && (isdigit(prefix[i-1]) || prefix[i-1] == '-'))
            {
                numbers[++j]=prefix[--i];
            }
            numbers[++j] ='\0';
            int sum=parseInt(numbers); //getting the number from the string
            free(numbers); //freeing the string
            push(operands,sum); // pushing the number to the operands stack

        }

        else if(isOperator(prefix[i]))
        {
            //popping the top 2 elements and calculating them
            // depending on what is the operator
            //and pushing their result
            int value2 = pop(operands);
            int value1=pop(operands);
            switch(prefix[i])
            {
            case '+' :
                push(operands,value2+value1);
                break;
            case '-' :
                push(operands,value2-value1);
                break;
            case '*' :
                push(operands,value2*value1);
                break;
            case '/' :
                push(operands,value2/value1);
                break;
            }
        }
    }
    //the result will be at the top of the stack
    int res=pop(operands);
    destroyStack(operands); //freeing the stack
    return res;
}

char * reverse (char* eq)
{
    int len=strlen(eq);
    char* temp= (char*) malloc((len+1)*sizeof(char)); //allocating a string to put the reversed input string in it

    for(int i=0; i<len; i++) //putting every element from the begging of the first one in the last of the reversed string
    {
        if(isOpenParenthesis(eq[i]) || isCloseParenthesis(eq[i])) // getting the opposite parenthesis of the current one
            // because we want the equation to be corrupted
        {
            temp[len-i-1] =getOppositeParenthesis(eq[i]);
            continue;

        }
        temp[len-i-1]=eq[i];

    }
    temp[len]='\0';
    return temp;
}


char* infixToPrefix(char* infix)
{
    char* temp=reverse(infix); //reversing the equation
    char* temp2=convertToPostfix(temp); // converting the reversed equation to postifx
    char* temp3=reverse(temp2); //reversing the postfix which will give us the prefix
    free(temp);
    free(temp2);
    return temp3;
}

void DisplayMeun ()
{

    printf("\033[0;32m"); // sets the color to green
    printf("=========================================================\n");
    printf("|   Welcome To equations validation System              |\n");
    printf("=========================================================\n");
    printf("|                                                       |\n");
    printf("|      1. Read input file                               |\n");
    printf("|      2. Print equations                               |\n");
    printf("|      3. Check equations validity                      |\n");
    printf("|      4. Convert valid equations from infix to prefix  |\n");
    printf("|      5. Evaluate the prefix expressions               |\n");
    printf("|      6. Print invalid equations.                      |\n");
    printf("|      7. Print all equations to a file                 |\n");
    printf("|      8. Reshow the menu                               |\n");
    printf("|      9. Exit                                          |\n");
    printf("|                                                       |\n");
    printf("=========================================================\n\n");
}

void printMenu ()
{

    printf("| 1. Print equations along with there validity only      |\n");
    printf("| 2. Print equations along with their prefixes           |\n");
    printf("| 3. Print equations along with their prefixes and value |\n");
    printf("| 4. cancel                                              |\n");
    printf("Choose one of these options:\n");

}
//reading one line from the file
char*  readEq(FILE* fp)
{
    int size=50;
    char* eq=(char*)malloc(size*sizeof(char));
    int ch = fgetc(fp),i=0;
    if(ch==EOF)
    {
        free(eq);
        return "EOF";
    }
    //checking if the file contains an invalid characters
    if(!isdigit(ch) && !isOperator(ch) && !isCloseParenthesis(ch) &&  !isOpenParenthesis(ch) && ch!=' ' && ch!='\n' && ch!='\0' && ch!=EOF)
    {
        return NULL;
    }
    //adding characters to the string until it reaches the end of the file or a new line
    while (ch!='\n' && ch!=EOF)
    {
        if(!isdigit(ch) && !isOperator(ch) && !isCloseParenthesis(ch) &&  !isOpenParenthesis(ch) && ch!=' ' && ch!='\n' && ch!='\0' && ch!=EOF)
        {
            return NULL;

        }
        if(i==size-1)
        {
            //if the size exceeds it will reallocate it with a bigger size
            eq=(char*)realloc(eq,(size*2)*sizeof(char));
            size=size*2;
        }
        eq[i++]=ch;
        ch = fgetc(fp);
    }
    //reallocating the equation with the current size
    eq=(char*)realloc(eq,(i+1)*sizeof(char));
    eq[i]='\0';
    return eq;
}


list* readOption(int* read)
{
    //opening the input file
    printf("Enter the input file name.\n");
    FILE *fp;
    char* filename=(char*)malloc(50*sizeof(char));
    scanf("%s", filename);
    fp = fopen(filename, "r");
    //if the opening file doesnt exist , it will keep asking the user to input another one
    while (fp == NULL)
    {
        printf("Failed to open the file.\n\n");
        printf("Enter the correct name\n\n");
        scanf("%s", filename);
        fp = fopen(filename, "r");
    }
    free(filename);

//creating the equations list
    list*  eq=createList();
    char* eqs=readEq(fp);
    if(eqs==NULL)
    {
        printf("The file contains an invalid characters\n");
        freeList(eq);
        return NULL;
    }
    // the function will return "EOF" when the end of the file has been reached
    while( strcmp(eqs,"EOF") !=0)
    {
        insertToList(eq,eqs);
        eqs=readEq(fp);
        if(eqs==NULL)
        {
            printf("The file contains an invalid characters\n");
            freeList(eq);
            return NULL;
        }

    }
    //if the file doesnt contain any thing
    if(eq->size==0)
    {
        freeList(eq);
        printf("No equations in the file\n\n");
        return NULL;
    }
    fclose(fp);
    //flag to indicate that the file has been read
    *read=1;
    printf("\n\n");
    return eq;

}
int main()
{
    //a flag to indicate that the file has been read
    int read=0;
    DisplayMeun();
    list* eqs=NULL;
    while(1)
    {
        printf("Select an option : \n");
        int n;
        int buffer= scanf("%d",&n);
        if (buffer == 0)
        {
            printf("Invalid input. Please enter an integer.\n");
            // clearing the input buffer if the user entered a non integer value
            scanf("%*[^\n]%*c");
            continue;
        }

        printf("\n");
        switch (n)
        {
        case 1:
            if(!read)
            {
                //reading the equations from a file to a list
                eqs=  readOption(&read);
                if(eqs!=NULL)
                    printf("%d Equations have been read\n\n",eqs->size);
                break;
            }
            else
            {
                printf("The file has already been read\n\n");
                //it will ask the user if he wants to read another file
                printf("If you want to read another file enter 1 ,else enter 0 : ");
                int q;
                scanf("%d",&q);
                if(q==1)
                {
                    freeList(eqs); //freeing the current list to add it
                    eqs= readOption(&read);
                    if(eqs!=NULL)
                        printf("%d Equations have been read\n\n",eqs->size);
                    break;
                }
                else break;
            }
        case 2:
            if(!read) // if the user didnt read a file it will break
            {
                printf("Please read the file first\n");
                break;
            }
            list* current=eqs; // traversing through the list to print each one
            for(int i=0; i<eqs->size; i++)
            {
                printf("Equation No %d : %s\n",i+1,current->data);
                current=current->next;
            }
            printf("\n\n");
            break;
        case 3:
            if(!read) // if the user didnt read a file it will break
            {
                printf("Please read the file first\n");
                break;
            }
            current= eqs; // traversing through the list to print each one along with its validity
            for(int i=0; i<eqs->size; i++)
            {
                printf("Equation No %d : ",i+1); // passing the mode to be printed as the index

                if(isValid(current->data,1))
                {
                    printf("%s : Valid\n",current->data);
                }
                current=current->next;


            }
            printf("\n\n");
            break;
        case 4 :
            if(!read)// if the user didnt read a file it will break
            {
                printf("Please read the file first\n");
                break;
            }
            printf("Infix expression of the valid equations :\n");
            current= eqs;  // traversing through the list to print the prefix of each one if its valid
            for(int i=0; i<eqs->size; i++)
            {

                if(isValid(current->data,0)) //the print mode is zero, it will not print
                {
                    char* prefix = infixToPrefix(current->data);
                    printf("Equation No %d : %s\n    Prefix : %s\n\n",i+1,current->data,prefix);
                    free(prefix);
                }
                current=current->next;

            }
            printf("\n\n");
            break;
        case 5:
            if(!read)// if the user didnt read a file it will break
            {
                printf("Please read the file first\n");
                break;
            }
            current= eqs;
            // traversing through the list to print the prefix and the result of each one if its valid
            for(int i=0; i<eqs->size; i++)
            {

                if(isValid(current->data,0)) //the printing mode is zero
                {
                    char* prefix = infixToPrefix(current->data);
                    printf("Equation No %d : %s\n    Prefix : %s\n    Value : %d\n\n",i+1,current->data,prefix,evaluatePrefix(prefix));
                    free(prefix);
                }
                current=current->next;
            }
            printf("\n\n");
            break;
        case 6 :// if the user didnt read a file it will break
            if(!read)
            {
                printf("Please read the file first\n");
                break;
            }
            current= eqs;
            printf("Invalid equations :\n");
            // traversing through the list to print it if its not valid
            for(int i=0; i<eqs->size; i++)
            {

                if(!isValid(current->data,0))
                {
                    printf("Equation No %d : %s\n",i+1,current->data);

                }
                current=current->next;
            }
            printf("\n\n");
            break;
        case 7 :// if the user didnt read a file it will break
            if(!read)
            {
                printf("Please read the file first\n");
                break;
            }
            //printing the equations to the output file
            FILE* fp=fopen("output.txt","w");
            printMenu();
            int op;
            current= eqs;
            if (scanf ("%d",&op)==0)
            {
                scanf("%*[^\n]%*c");
                printf("Invalid option , cancelled.\n\n");
                break;
            }
            switch(op)
            {
            //printing the equations along with their validity
            case 1 :

                for(int i=0; i<eqs->size; i++)
                {
                    if(isValid(current->data,0))
                    {
                        fprintf(fp,"%s : Valid\n",current->data);
                    }
                    else fprintf(fp,"%s : Invalid\n",current->data);
                    current=current->next;

                }
                printf("Successfully Printed to : output.txt\n");
                break;
            //printing the equations along with their validity and prefixes
            case 2 :

                for(int i=0; i<eqs->size; i++)
                {

                    if(isValid(current->data,0))
                    {
                        char *prefix=infixToPrefix(current->data);
                        fprintf(fp,"%s , prefix : %s \n",current->data,prefix);
                        free(prefix);
                    }
                    else fprintf(fp,"%s : Invalid\n",current->data);
                    current=current->next;

                }
                printf("Successfully Printed to : output.txt\n");
                break;

            //printing the equations along with their validity  and the prefix and the result
            case 3 :

                for(int i=0; i<eqs->size; i++)
                {

                    if(isValid(current->data,0))
                    {
                        char *prefix=infixToPrefix(current->data);
                        fprintf(fp,"%s , prefix : %s  = %d \n",current->data,prefix,evaluatePrefix(prefix));
                        free(prefix);
                    }
                    else fprintf(fp,"%s : Invalid\n",current->data);
                    current=current->next;

                }
                printf("Successfully Printed to : output.txt\n");
                break;
            case 4 :
                break;

            default :
                printf("Invalid option , cancelled.\n\n");

            }

            fclose(fp);
            break;
        case 8 :
            //reshowing the menu
            printf("\033[2J\033[H");
            DisplayMeun();
            break;
        case 9 :
            //freeing the list
            freeList(eqs);
            exit(0);
        default :
            printf("Enter a valid option\n");
            break;
        }
    }
    return 0;
}
