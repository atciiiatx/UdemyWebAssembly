#include <string.h>

extern void numLog(int n);
extern void strLog(char *s, int length);

int main()
{
	return 42;
}

int getDoubleNumber(int x)
{
	return x * 2;
}

void testNumLog(int x)
{
	numLog(x);
}

void testStrLog()
{
	char *msg = "Hello from C!";
	strLog(msg, strlen(msg));
}
