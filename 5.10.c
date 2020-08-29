#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100

void push(double);
double pop(void);

int
main(int argc, char **argv)
{
	int type;
	double op2;
	char s[MAXOP];

	while (--argc > 0) {
		argv++;
		if (**argv == '+')
			push(pop() + pop());
		else if (**argv == '*')
			push(pop() * pop());
		else if (**argv == '-') {
			op2 = pop();
			push(pop() - op2);
		} else if (**argv == '/') {
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
		} else
			push(atof(*argv));

	}
	printf("%.8g\n", pop());
	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}
