//!Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//!Constants
const int    ERROR        = -666;
const int    COUNT_POISON = -666;
const double DATA_POISON  = -666;

//!Types
typedef double Type;
typedef struct Stack_t
{
    Type * data;
    int size_counter;
    int maximum_element;
    int error;
    bool allocated = false;
}Stack_t;

//!Functions
int  Stack_ctor  (Stack_t * , size_t);
int  Stack_dtor  (Stack_t * );
bool Stack_OK    (const Stack_t * );
int  Stack_push  (Stack_t * , Type );
int  Stack_pop   (Stack_t * );
int  Stack_repush(Stack_t * , Type );

int main()
{
    Stack_t stk;
    Stack_ctor(&stk, 20);
    for (int i = 0; i < 20; i++)
    {
        Stack_push(&stk, i * 2);
        printf("%lg\n", Stack_pop(&stk));
    }
    Stack_dtor(&stk);
    return 0;
}

int Stack_ctor (Stack_t * This, size_t size)
{
    assert(This);

    if (This -> allocated)
    {
        if(size <= This -> maximum_element)
        {
            printf("ERROR!\nMemory is already full!\n");

            return -1;
        }

        This -> data = (Type * )realloc((Type *)This -> data, size * sizeof(* This -> data));

        for (int i = This -> size_counter; i < size; i++)
            This -> data[i] = DATA_POISON;

        This -> maximum_element = size;

        return 0;
    }

    This -> data = (Type *)calloc(size, sizeof(* This -> data));
    This -> allocated = true;

    for ( int i = 0; i < size; i++ )
		This -> data[i] = DATA_POISON;

	This -> maximum_element = size;

	This -> size_counter = 0;
	This -> error = 0;

	return 0;

	assert(This);
}

int Stack_dtor(Stack_t * This)
{
    assert(This);
    if (!This -> allocated)
    {
        printf("Stack is already freed\n");
        return -1;
    }
    free(This -> data);
    This -> data = NULL;
    This -> allocated = false;
    This -> maximum_element = 0;
    This -> error = ERROR;
    This -> size_counter = COUNT_POISON;
    return 0;
}

bool Stack_OK(const Stack_t * This)
{
    return  This                       &&
            This -> allocated          &&
            This -> error              &&
            (This -> size_counter >=0) &&
            This -> data               &&
            This -> maximum_element    &&
            This -> size_counter <= This -> maximum_element;
}

int Stack_push(Stack_t * This, Type variable)
{
    if (This -> size_counter >= This -> maximum_element)
    {
        printf("Cannot push stack!\n");
        Stack_repush(This, variable);
        return -1;
    }
    This -> data[This -> size_counter] = variable;
    This -> size_counter++;
    return 0;
}

int Stack_pop (Stack_t * This)
{
    if (!This -> size_counter)
    {
        printf("Cannot pop elements!\n");
        return DATA_POISON;
    }
    This -> size_counter--;
    Type returning = This -> data[This -> size_counter];
    This -> data[This -> size_counter] = DATA_POISON;
    return returning;
}

int Stack_repush (Stack_t * This, Type variable)
{
    printf("Input '1'(yes), if you want to repush stack\nInput '2'(no), if you do not want to repush stack\n");
    int answer;
    scanf("%d", &answer);
    switch(answer)
    {
    case 1:
        Stack_ctor(This, This -> maximum_element * 2);
        Stack_push(This, variable);
        break;
    case 2:
        break;
    default:
        printf("Print '1'(yes) or '2'(no):\n");
        Stack_repush(This, variable);
        return 0;
    }
    return 0;
}
