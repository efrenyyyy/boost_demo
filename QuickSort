#include <iostream>
int array[10] = {6,1,2,5,4,3,9,7,10,8};

void quick_sort(int left, int right)
{
	if (left > right)
	{
		return;
	}
	int i = left;
	int j = right;
	int temp = array[left];

	while (i != j)
	{
		while (array[j] >= temp && i < j)
			j--;
		while (array[i] <= temp && i < j)
			i++;

		if (i < j)
		{
			int t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
	}
	array[left] = array[j];
	array[j] = temp;
	quick_sort(left, i - 1);
	quick_sort(i + 1, right);
}

int main()
{
	quick_sort(0, 9);
	getchar();
}
