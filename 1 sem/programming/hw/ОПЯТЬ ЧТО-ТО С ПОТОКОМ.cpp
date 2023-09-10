ifstream in("input.txt");
if (!in) {
	cout << "Файл не открылся.";
	return 1;
}
if (!getline(in, temp)) {
	cout << "Файл пустой";
	return 0;
}
int begin = 0, end = 0;
do {
	
} while 
in.close