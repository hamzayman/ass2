#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    float data;
    struct Node* next;
} node;

typedef struct {
    node *top;
} stack;

stack *init() {
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

void push(stack *s, float x) {
    node *nn = malloc(sizeof(node));
    nn->data = x;
    nn->next = s->top;
    s->top = nn;
}

float pop(stack *s) {
    node *temp = s->top;
    float x = temp->data;
    s->top = temp->next;
    free(temp);
    return x;
}

float peek(stack *s) {
    return s->top->data;
}

int isEmpty(stack *s) {
    return s->top == NULL;
}


int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isNegativeNumber(char *token) {
    return token[0] == '-' && token[1] != '\0';
}


char* infixTopostfix(char *infix) {
    char *input = strdup(infix);
    char *output = malloc(strlen(infix) * 2 + 10);
    output[0] = '\0';

    stack *s = init();

    char *token = strtok(input, " ");
    while (token != NULL) {

        if (isNegativeNumber(token)) {
            strcat(output, token);
            strcat(output, " ");

        } else if (isOperator(token[0])) {
            while (!isEmpty(s) && isOperator((char)peek(s))) {
                if (token[0] == '^') {
                    if (precedence((char)peek(s)) <= precedence(token[0])) break;
                } else {
                    if (precedence((char)peek(s)) < precedence(token[0])) break;
                }
                char op[3] = {(char)pop(s), ' ', '\0'};
                strcat(output, op);
            }
            push(s, (float)token[0]);

        } else if (token[0] == '(') {
            push(s, (float)'(');

        } else if (token[0] == ')') {
            while ((char)peek(s) != '(') {
                char op[3] = {(char)pop(s), ' ', '\0'};
                strcat(output, op);
            }
            pop(s);

        } else {
            strcat(output, token);
            strcat(output, " ");
        }

        token = strtok(NULL, " ");
    }

    while (!isEmpty(s)) {
        char op[3] = {(char)pop(s), ' ', '\0'};
        strcat(output, op);
    }

    free(input);
    free(s);
    return output;
}


float evaluatePostfix(char *postfix) {
    char *input = strdup(postfix);
    stack *s = init();

    char *token = strtok(input, " ");
    while (token != NULL) {

        if (isOperator(token[0]) && token[1] == '\0') {
            float b = pop(s);
            float a = pop(s);

            if      (token[0] == '+') push(s, a + b);
            else if (token[0] == '-') push(s, a - b);
            else if (token[0] == '*') push(s, a * b);
            else if (token[0] == '/') push(s, a / b);
            else if (token[0] == '%') push(s, fmod(a, b));
            else if (token[0] == '^') push(s, pow(a, b));

        } else {
            push(s, atof(token));
        }

        token = strtok(NULL, " ");
    }

    float result = pop(s);
    free(input);
    free(s);
    return result;
}



int main() {
    char infix[200];

    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);


    infix[strcspn(infix, "\n")] = '\0';

    char *postfix = infixTopostfix(infix);
    float result  = evaluatePostfix(postfix);

    printf("Postfix: %s\n", postfix);
    printf("Result:  %.5f\n", result);

    free(postfix);
    return 0;
}