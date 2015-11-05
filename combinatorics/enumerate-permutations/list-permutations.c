#include <stdio.h>

void print(int *v, int size)
{
	if (v == 0)
		return;
	int i;

	for (i = 0; i < size; i++)
		printf("%4d", v[i]);
	printf("\n");
}

void visit(int *Value, int N, int k)
{
	static level = -1;
	level = level + 1;
	Value[k] = level;

	if (level == N)
		print(Value, N);
	else {
		int i;
		for (i = 0; i < N; i++)
			if (Value[i] == 0)
				visit(Value, N, i);
	}

	level = level - 1;
	Value[k] = 0;
}

int main(void)
{
	const int N = 6;
	int Value[N];
	int i;
	for (i = 0; i < N; i++) {
		Value[i] = 0;
	}
	visit(Value, N, 0);
}

