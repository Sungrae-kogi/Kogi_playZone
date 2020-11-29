#include <iostream>
using namespace std;

int main() {
	int i, j, temp;
	int array[10] = { 1,10,5,8,7,6,4,3,2,9 };
	for (i = 0; i < 9; i++) {
		j = i;
		while (array[j] > array[j + 1]) {
			temp = array[j];
			array[j] = array[j + 1];
			array[j + 1] = temp;
			cout << j << endl;
			j--;			//8줄에서 j는 0부터 9index의 값에서 시작해서 더 작은값이 있다면 --로 내려간다
		}
	}

	for (i = 0; i < 10; i++) {
		cout << array[i] << " ";
	}

	return 0;
}