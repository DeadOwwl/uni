ifstream in("input.txt");
if (!in) {
	cout << "���� �� ��������.";
	return 1;
}
string temp;
int k;
while (getline(in, temp)) {
	if (temp[0] == ' ') k++;
}
in.close