#include <iostream>
#include "OrdFract.h" // ���������� ����� ������
#include "FractExc.h" //���������� ����� ����������
#include <ctime>

using namespace std;

int main() {
	try {
		setlocale(0, ""); // ���������� ������� �������
		OrdFract Arr[7];
		srand(time(NULL));
		int i(0);
		for (i; i < 2; i++) {
			Arr[i]=OrdFract(2+rand()%8,2+rand()%8);
		}
		for (i; i < 5; i++) Arr[i] = Arr[i - 1] + Arr[i - 2];
		for (i; i < 7; i++) Arr[i] = Arr[i - 3] - 2 * Arr[i - 5];
		for (i = 0; i < 7; i++) cout << Arr[i] << " ";
		OrdFract Max(Arr[0]);
		int Ind(0);
		for (i = 0; i < 7; i++) {
			if (Arr[i] > Max && Arr[i].GetID() % 2 ==0) {
				Max = Arr[i];
				Ind = i;
			}
		}
		cout << endl;
		for (i = 0; i < 7; i++) {
			cout << Arr[i] << " ID=" << Arr[i].GetID()<<endl;
		}
		//cout << "\n������������ � ������ ��������������� " << Max <<" � ���������������� " << Max.GetID()+Ind-1;
		system("pause");
		//cout << "������� ������ �����: ";// ����� ���������� � �������
		//cin >> F1;// ���� 1 ����� � ����������
		//cout << "������� ������ �����: ";// ����� ���������� � �������
		//cin >> F2;// ���� 2 ����� � ����������
		//cout << F1 << " � " << F2 << endl<<endl;// �������� ���������� � ����������� ����
		////cout<<a.GetID()<<endl;
		////cout<<f.GetID()<<endl;// ��������� ������ ����� (� 6)
		////cout << g.GetID() << endl;// ��������� ������ ����� (� 5)
		//OrdFract q = F1, w = F2;
		//cout << "�� " << q << " ����� " << ++q << endl;//���������� ��������
		//q = F1;
		//cout << "�� " << q << " ����� " << q++ << endl;//����������� ��������
		//q = F1;
		//cout << "�� " << q << " ����� " << --q << endl; //���������� ���������
		//q = F1;
		//cout << "�� " << q << " ����� " << q-- << endl << endl;//����������� ���������
		//q = F1;

		//cout << q << " + " << w << " = " << q + w << endl; //�������� ���� ������
		//q = F1, w = F2;
		//cout << q << " - " << w << " = " << q - w << endl;//��������� ���� ������
		//q = F1, w = F2;
		//cout << q << " * " << w << " = " << q * w << endl;//��������� ���� ������
		//q = F1, w = F2;
		//cout << q << " / " << w << " = " << q / w << endl<<endl;//������� ���� ������
		//q = F1, w = F2;

		//cout << q << "+" << 23 << " = " << q + 23 << endl;//�������� ����� � ������
		//q = F1;
		//cout << q << " - " << 23 << " = " << q - 23 << endl;//��������� ����� � �����
		//q = F1;
		//cout << q<<" * "<<23<<" = "<<q * 23 << endl;//��������� ����� � �����
		//q = F1;
		//cout << q << " / " << 23 << " = " << q / 23 << endl<<endl;//������� ����� �� �����
		//q = F1;

		//cout << 23 << " + " << q << " = " << 23 + q << endl;//�������� ����� � ������
		//q = F1;
		//cout << 23 << " - " << q << " = " << 23 - q << endl;//��������� ����� � �����
		//q = F1;
		//cout << 23 << " * " << q << " = " << 23 * q << endl;//��������� ����� � �����
		//q = F1;
		//cout << 23 << " / " << F1 << " = " << 23 / q << endl << endl;//������� ����� �� �����
		//q = F1;

		//q += w; //�������� �������� ����� � ������ ������ � ������������ �������� �������� �����
		//cout << F1 << " += " << F2 << " = " << q << endl;
		//q = F1, w = F2;
		//q -= w; //��������� �������� ����� � ������ ����� � ������������ �������� �������� �����
		//cout << F1 << " -= " << F2 << " = " << q << endl;
		//q = F1, w = F2;
		//q *= w; //��������� �������� ����� � ������ ����� � ������������ �������� �������� �����
		//cout << F1 << " *= " << F2 << " = " << q << endl;
		//q = F1, w = F2;
		//q /= w; //������� �������� ����� � ������ ����� � ������������ �������� �������� �����
		//cout << F1 << " /= " << F2 << " = " << q << endl<<endl;
		//q = F1, w = F2;

		//q += 23;//�������� �������� ����� ������ � ������������ �������� �������� �����
		//cout << F1 << " += " << 23 << " = " << q << endl;
		//q = F1;
		//q -= 23; //��������� �������� ����� � ����� � ������������ �������� �������� �����
		//cout << F1 << " -= " << 23 << " = " << q << endl;
		//q = F1;
		//q *= 23; //��������� �������� ����� � ����� � ������������ �������� �������� �����
		//cout << F1 << " * " << 23 << " = " << q << endl;
		//q = F1;
		//q /= 23; //������� �������� ����� � ����� � ������������ �������� �������� �����
		//cout << F1 << " /= " << 23 << " = " << q << endl << endl;
		//q = F1, w = F2;

		//// ��������� ���������
		//OrdFract r = F1;
		//if (q == r) cout << "����� " << q << " � " << r << " �����\n";
		//if (q != w) cout << "����� " << q << " � " << w << " �� �����\n";
		//if (q > w) cout << "����� " << q << " ������ " << w << endl;
		//if (q >= w) cout << "����� " << q << " ������ ���� �����" << w << endl;
		//if (q < w) cout << "����� " << q << " ������ " << w << endl;
		//if (q <= w) cout << "����� " << q << " ������ ���� ����� " << w << endl<<endl;

		////�������� � �����
		//cout << q << " + " << 0 << " = " << q + 0<<endl;
		//cout << q << " - " << 0 << " = " << q - 0<<endl;
		//cout << q << " * " << 0 << " = " << q * 0<<endl;
		//cout << q << " / " << 0 << " = " << q / 0<<endl<<endl;
		//q = F1;
	}
	catch (FractExc& e) { // ����� ���������� � ���� ����� ������
		cout << e.what() << endl; // ������� ������
	}
}