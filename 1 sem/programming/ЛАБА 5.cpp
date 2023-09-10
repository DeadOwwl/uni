#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double f_1(double x) {
	return x * sqrt(1+x);
}
double f_2(double x) {
	return asin(sqrt(x))/sqrt(x*(1-x));
}
double f_3(double x) {
	return pow(2, x) / (1 + pow(4, x));
}
double integral_middlerectangles(double a, double b, double e, double (*function)(double), int *r) {
	int z;
	if (a == b) return 0.0; //���� ������ � ������� ������� ���������, ������� ����� ����
	else {
		if (a > b) { //���� a>b ������ �� �������, � �������� �� ������ �������� �� -1 (���������� z)
			double temp;
			temp = a;
			a = b;
			b = a;
			z = -1;
		}
		else z = 1;
	}
	int n = 4; //����� ���������� ���������������
	double s1, s2, h;
	s2 = (b-a)*(function((b+a)*0.5));
	do {
		s1 = s2;
		n *= 2;
		h = (b - a) / n;
		s2 = 0;
		for (int i = 0; i < n; i++) s2 += function(a + i * h);
		s2 *= h;
	} while (fabs(s2 - s1) > e);
	*r = n;
	return s2 * z;
}
double integral_method_of_Simpson(double a, double b, double e, double (*function)(double), int *r) {
	int z;
	if (a == b) return 0.0; 
	else {
		if (a > b) { 
			double temp;
			temp = a;
			a = b;
			b = a;
			z = -1;
		}
		else z = 1;
	}
	int n = 4;//����� ��������
	double s1, s2, h;
	s2 = (function(a) + function(b)) / 3;
	do {
		s1 = s2;
		n *= 2;
		h = (b - a) / (2*n);
		s2 = function(a) + function(b);
		//cout << function(a) << "   " << function(b) << endl;
		for (int i = 1; i < n; i++) s2 += 2 * function(a + (2*i) * h);
		for (int i = 1; i <= n ; i++) s2 += 4 * function(a + (2*i-1) * h);
		s2 = (double)(s2*h)/ 3;
	} while (fabs(s2 - s1) > e);
	*r = n;
	return s2 * z;
}
int main() {
	setlocale(0, "");
	double e;
	int n = 0;
	cout << "������� �������� �������� ������ 1, ������ 0: ";
	cin >> e;
	cout << endl;
	cout << "����������� �������� ���������� �� ������ ������� ���������������: " << endl;
	integral_middlerectangles(2.0, 7.0, e, f_1, &n);
	cout << "������ ��������: " << integral_middlerectangles(2.0, 7.0, e, f_1, &n) << " " << "; ����� ����� �������: " << n << endl;
	cout << "������ ��������: " << integral_middlerectangles(0.2, 0.3, e, f_2, &n) << " " << "; ����� ����� �������: " << n << endl;
	cout << "������ ��������: " << integral_middlerectangles(-13, -2, e, f_3, &n) << " " << "; ����� ����� �������: " << n << endl;
	cout << "����������� �������� ���������� �� ������ ��������: " << endl;
	cout << "������ ��������: " << integral_method_of_Simpson(2.0, 7.0, e, f_1, &n) << " " << "; ����� ����� �������: " << n << endl;
	cout << "������ ��������: " << integral_method_of_Simpson(0.2, 0.3, e, f_2, &n) << " " << "; ����� ����� �������: " << n << endl;
	cout << "������ ��������: " << integral_method_of_Simpson(-13, -2, e, f_3, &n) << " " << "; ����� ����� �������: " << n << endl;
}
//������: 79kGX5ev