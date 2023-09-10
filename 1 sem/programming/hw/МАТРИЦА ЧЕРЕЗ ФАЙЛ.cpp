#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#pragma warning(disable:4996);
using namespace std;
int main() {
	setlocale(0, "");
	int m, n;
	FILE* f1, * f2;
	if ((f1 = fopen("array.txt", "r"))) {
		fscanf(f1, "%d%d", &m, &n);
		if (feof) {
			cout << "Файл пустой. ";
			return 0;
		}
		int**array;
		array = new int*[m];
		for (int i = 0; i < m; i++) array[i] = new int[n];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				(f1, "%d%", &array[i][j]);
				if (feof) {
					cout << "Для полного заполнения матрицы не хватает элементов. ";
					return 0;
				}
			}
		}
		int* max = new int[m];
		int* min = new int[m];
		for (int i = 0; i < m; i++) {
			max[0] = array[i][0];
			min[0] = array[i][0];
			for (int j = 0; j < n; j++) {
				if (array[i][j] > max[i]) max[i] = array[i][j];
				if (array[i][j] < min[i]) min[i] = array[i][j];
			}
		}
		if (!(f2 = fopen("output.txt", "w"))) {
			fprintf(f2, "Максимальный элемент каждой строки матрицы: ");
			for (int i = 0; i < m; i++) {
				fprintf(f2, "%d", i, " - ");
				fprintf(f2, "%d", max[i]);
			}
			fprintf(f2, "Минимальный элемент каждой строки матрицы: ");
			for (int i = 0; i < m; i++) {
				fprintf(f2, "%d", i, " - ");
				fprintf(f2, "%d", min[i]);
			}
		}
		else cout << "Файл не доступен для записи. ";
		for (int i = 0; i < m; i++) delete[] array[i];
		delete[] array;
	}
	else cout << "Файл пустой или не открывается. Введите необходимую информаацию в файл и перезагрузите программу. ";
	fclose (f1), (f2);
	return 0;
}