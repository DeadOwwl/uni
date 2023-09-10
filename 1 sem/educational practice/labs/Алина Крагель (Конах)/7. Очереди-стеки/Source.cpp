#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

using namespace std;

int N(0), Xs(0), Ys(0), Xf(0), Yf(0), K(0);
int** ArrSv, **ArrTr;
int NeighX[] = { 1, 0, -1, 0 };
int NeighY[] = { 0, -1, 0, 1 };

struct Robo 
{
	int x = 0;
	int y = 0;
	int key = 0;
};

struct Q 
{
	int Size;
	int Front;
	int Rear;
	Robo* Array;
};

void Init(int len, Q& q) 
{
	q.Size = len;
	q.Front = 0;
	q.Rear = 0;
	q.Array = new Robo[len + 1];
}

void Del(Q& q)
{
	delete[] q.Array;
	q.Front = 0;
	q.Rear = 0;
	q.Size = 0;
}

void Push(Robo& p, Q& q) 
{
	if ((q.Rear + 1 == q.Front) || ((q.Front == 0) && (q.Rear == q.Size)))
		throw "Queue is full";
	q.Array[q.Rear++] = p;
	if (q.Rear == q.Size + 1)
		q.Rear = 0;
}

Robo Pop(Q& q)
{
	if (q.Rear == q.Front)
		throw "Queue is empty";
	Robo p = q.Array[q.Front++];
	if (q.Front == q.Size + 1)
		q.Front = 0;
	return p;
}

bool Empty(Q& q)
{
	return q.Rear == q.Front;
}

void PrintArray(int** Array, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << Array[i][j];
		cout << endl;
	}
}

void Input()
{
	cout << "Доброгo времени суток!\nДла начала работы с программой, необходимо ввести базовые денные.\n\nВведите число N (целочисленное), определяющее размер матрицы: ";
	cin >> N;
	while (N <= 0) 
	{
		cout << "Введено неверное значение размера матрицы. Повторите ввод: ";
		cin >> N;
	}
	ArrTr = new int* [N];
	for (int i(0); i < N; i++)
		ArrTr[i] = new int[N];
	cout << "\nЗаполните значения высот над уровнем моря для квадратов матрицы: ";
	for (int i(0); i < N; i++)
	{
		for (int j(0); j < N; j++) 
		{
			cin >> ArrTr[i][j];
			while (ArrTr[i][j] < 0)
			{
				cout << "Значение высоты отрицательно, повторите ввод: ";
				cin >> ArrTr[i][j];
			}
		}
	}
	// матрица связей
	ArrSv = new int* [N];
	for (int i(0); i < N; i++) 
		ArrSv[i] = new int[N];
	for (int i(0); i < N ; i++)
	{
		for (int j(0); j < N; j++)
			ArrSv[i][j] = 1874919424;
	}
	cout << "\nВведите начальные(целочисленные) координаты робота (Xs, Ys). Учтите, что счет координат идет от 1 до N, Х - горизонталь, Y - вертикаль: ";
	cin >> Xs >> Ys;
	while (Xs <= 0 || Ys <= 0 || Xs > N || Ys > N)
	{
		cout << "Введено неверное значение координат. Повторите ввод: ";
		cin >> Xs >> Ys;
	}
	cout << "\nВведите конечные(целочисленные) координаты робота (Xf, Yf).  Учтите, что счет координат идет от 1 до N, Х - горизонталь, Y - вертикаль: ";
	cin >> Xf >> Yf;
	while (Xf <= 0 || Yf <= 0 || Xf > N || Yf > N)
	{
		cout << "Введено неверное значение координат. Повторите ввод: ";
		cin >> Xf >> Yf;
	}
	cout << "\nВведите длину К(целочисленное) - расстояние между клетками матрицы: ";
	cin >> K;
	while (K <= 0) 
	{
		cout << "Введено неверное значение расстояния между клетками. Повторите ввод: ";
		cin >> K;
	}
	Xs--;
	Ys--;
	Xf--;
	Yf--;
}

int main() {
	try {
		setlocale(0, "");
		Input();
		Q q;
		Robo r;
		bool found = false;
		Init(N * N, q);
		r.x = Xs; 
		r.y = Ys; 
		int d(0);
		ArrSv[Xs][Ys] = 0;
		Push(r, q);
		try 
		{
			while (!Empty(q)) 
			{
				r = Pop(q);
				if ((r.x == Xf) && (r.y == Yf)) 
				{
					found = true;
					break;
				}
				for (int i = 0; i < 4; i++) 
				{
					if ((r.x + NeighX[i] >= 0) && (r.x + NeighX[i] < N) && 
						(r.y + NeighY[i] >= 0) && (r.y + NeighY[i] < N) && 
						(ArrTr[r.y + NeighY[i]][r.x + NeighX[i]] != -1) &&
						(ArrSv[r.y + NeighY[i]][r.x + NeighX[i]] == 1874919424) &&
						(ArrSv[r.y + NeighY[i]][r.x + NeighX[i]] > r.key + abs(ArrTr[r.y][r.x] - ArrTr[r.y + NeighY[i]][r.x + NeighX[i]])))
					{
						Robo r1;
						r1.x = r.x + NeighX[i];
						r1.y = r.y + NeighY[i];
						r1.key = r.key + abs(ArrTr[r.x][r.y] - ArrTr[r.x + NeighX[i]][r.y + NeighY[i]]) + K;
						Push(r1, q);
						ArrSv[r1.y][r1.x] = ArrSv[r.y][r.x] + 1;
					}
				}
				ArrTr[r.y][r.x] = -1;
			}
		}
		catch (const char* e) 
		{
			cout << e << endl;
		}
		if (found) 
		{
			cout << "Маршрут: " << endl;
			d = ArrSv[Yf][Xf];
			int** way = new int* [2];
			for (int i = 0; i < 2; i++)
				way[i] = new int[d];
			int count = 0;
			way[0][count] = Xs; 
			way[1][count] = Ys;
			count++;

			int x = Xs, y = Ys;
			while (!((x == Xf) && (y == Yf))) 
			{
				for (int i = 0; i < 4; i++) 
				{
					if ((x + NeighX[i] >= 0) && (x + NeighX[i] < N) && (y + NeighY[i] >= 0) && (y + NeighY[i] < N) && (ArrSv[y + NeighY[i]][x + NeighX[i]] == count))
					{
						x += NeighX[i];
						y += NeighY[i];
						way[0][count] = x; 
						way[1][count] = y;
						count++;
						break;
					}
				}
			}
			for (int i(0); i < d; i++)
				cout << way[0][i] + 1 << " " << way[1][i] + 1 << endl;
			cout << Xf + 1 << " " << Yf + 1 << endl;

			cout << "Карта маршрута:" << endl;
			char** map = new char* [N];
			for (int i = 0; i < N; i++) 
				map[i] = new char[N];
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					map[i][j] = 'o';
			for (int i = 0; i < d; i++) 
			{
				x = way[0][i];
				y = way[1][i];
				map[y][x] = 'x';
			}
			map[Ys][Xs] = 's'; 
			map[Yf][Xf] = 'f';
			for (int i = 0; i < N; i++) 
			{
				for (int j = 0; j < N; j++)
					cout << setw(5) << map[i][j];
				cout << endl;
			}

			for (int i = 0; i < N; i++)
				delete[] map[i];
			delete[] map;

			for (int i = 0; i < 2; i++)
				delete[] way[i];
			delete[] way;
		}
		else 
		{
			cout << "Маршрута не существует. " << endl;
		}
		Del(q);
		for (int i = 0; i < N; i++) 
			delete[] ArrTr[i];
		delete[] ArrTr;
		for (int i = 0; i < N; i++)
			delete[] ArrSv[i];
		delete[] ArrSv;

	}
	catch (char *Error) 
	{
		cout << Error << endl;
		system("pause");
		return 0;
	}
	return 0;
}