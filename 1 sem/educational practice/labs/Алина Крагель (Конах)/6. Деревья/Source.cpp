#include <iostream>

using namespace std;

void Menu(int& Choice) {
	cout << "������� ����:\n1. ������������ ����� ������. \n2. �������� ����. \n3. ����� ���� \n4. ������� ���� �� ��������.\n5. ������ ����� ������\n6. �������� ����� ������\n0.��������� ������ � ����������.\n";
	cin >> Choice;
	system("cls");
}

struct StructTree {                      
	int Info;                          
	StructTree* Left, * Right;                      
};

bool ShowTreeSim(StructTree*& Tree) {              
	if (Tree == NULL)
		return false;
	else
	{
		ShowTreeSim(Tree->Left);
		cout << Tree->Info << "   ";
		ShowTreeSim(Tree->Right);
		return true;
	}
		
}

bool ShowTreeObr(StructTree*& Tree) {
	if (Tree != NULL) {
		ShowTreeObr(Tree->Left);
		ShowTreeObr(Tree->Right);
		cout << Tree->Info << "   ";
		return true;
	}
	else return false;
}

bool ShowTreePr(StructTree*& Tree) {
	if (Tree != NULL) {
		cout << Tree->Info << " ";
		ShowTreePr(Tree->Left);
		ShowTreePr(Tree->Right);
		return true;
	}
	else return false;
}

void AddNew(int inf, StructTree*& MyTree) {
	if (NULL == MyTree){
		MyTree = new StructTree;          
		MyTree->Info = inf;             
		MyTree->Left = MyTree->Right = NULL; 
	}
	if (inf < MyTree->Info) {  
		if (MyTree->Left != NULL) AddNew(inf, MyTree->Left); 
		else {
			MyTree->Left = new StructTree;                 
			MyTree->Left->Left = MyTree->Left->Right = NULL;  
			MyTree->Left->Info = inf;                   
		}
	}
	if (inf > MyTree->Info) {           
		if (MyTree->Right != NULL) AddNew(inf, MyTree->Right); 
		else {
			MyTree->Right = new StructTree;                
			MyTree->Right->Left = MyTree->Right->Right = NULL; 
			MyTree->Right->Info = inf;                    
		}
	}
}

bool Find(StructTree* R, int a, StructTree*& Tree){
	if (R == NULL) {
		Tree = NULL;
		return false;
	}
	Tree = R;
	for (;;) {
		if (Tree->Info == a) return true;
		if (a < Tree->Info) {
		if (Tree->Left == NULL) return false;
			Tree = Tree->Left;
		}
		else {
			if (Tree->Right == NULL) return false;
			Tree = Tree->Right;
	    }
	}
}StructTree* DeleteNode(StructTree*&Tree, int inf) {
	if (Tree == NULL)
		return Tree;
	if (inf == Tree->Info) 
	{
		StructTree* tmp;
		if (Tree->Right == NULL) 
			tmp = Tree->Left;
		else 
		{
			StructTree* ptr = Tree->Right;
			if (ptr->Left == NULL) 
			{
				ptr->Left = Tree->Left;
				tmp = ptr;
			}
			else 
			{
				StructTree* pmin = ptr->Left;
				while (pmin->Left != NULL)
				{
					ptr = pmin;
					pmin = ptr->Left;
				}
				ptr->Left = pmin->Right;
				pmin->Left = Tree->Left;
				pmin->Right = Tree->Right;
				tmp = pmin;
			}
		}
		delete[] Tree;
		return tmp;
	}
	else 
		if (inf < Tree->Info) 
			Tree->Left = DeleteNode(Tree->Left, inf);
	else 
			Tree->Right = DeleteNode(Tree->Right, inf);
	return Tree;
}
int main() {
	setlocale(0, "");
	try { 
		cout << "����� ���������� � ��������� ��� ������ � ��������� ���������!\n��� ������ ������ ������� ���������� ����� ������: ";
		StructTree* Tree = NULL;                  
		int n(0);
		cin >> n;
		bool k(false);
		for (int i = 0; i < n; i++)
		{
			int p(0);
			cin >> p;
			AddNew(p, Tree);
		}
		system("cls");
		int Choice(1);
		int p(0);
		while (Choice) {
			Menu(Choice);
			switch (Choice) {
			case 1:
				if (Tree == NULL)
					cout << "������ ������.\n";
				else 
					ShowTreeSim(Tree);
				cout << "\n1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 0) {
					system("cls");
					return 0;
				}
				break;
			case 2:
				cout << "������� �������� ��� ���������� � ������: \n";
				cin >> p;
				k = true;
				AddNew(p, *&Tree);
				cout << "\n1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 0) {
					system("cls");
					return 0;
				}
				break;
			case 3:
				if (Tree == NULL)
					cout << "������ ������.\n";
				else
				{
					cout << "������� �������� ��� ���������� �������� �� ��������: \n";
					cin >> p;
					StructTree* s;
					if (Find(*&Tree, p, s)) cout << "\n�������� �������� ������������ � ������.";
					else cout << "\n������ �������� � ������ ���.";
				}
				cout << "\n1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
		            system("cls");
				}
				if (Choice == 0) {
					system("cls");
					return 0;
				}
				break;
			case 4: 
				if (Tree == NULL)
					cout << "������ ������.\n";
				else
				{
					cout << "������� �������� ���� ��� ��������: ";
					cin >> p;
					DeleteNode(*&Tree, p);
				}
				cout << "\n1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 0) {
					system("cls");
					return 0;
				}
				break;
			case 5:
				if (Tree == NULL)
					cout << "������ ������.\n";
				else
					ShowTreePr(Tree);
				cout << "\n1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 2) {
					system("cls");
					return 0;
				}
				break;
			case 6:
				if (Tree == NULL)
					cout << "������ ������.\n";
				else
					ShowTreeObr(Tree);
				cout << "\n1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 2) {
					system("cls");
					return 0;
				}
				break;
			case 0:
				return 0;
				break;
			default:
				throw "������ �������������� �������. ";
				continue;
			}
		}
	}
	catch (const char* error) {
		cout << error << endl;
		return 0;
	}
}