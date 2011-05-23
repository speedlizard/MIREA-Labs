#include <iostream>
#include <algorithm>
#include <string>

struct Data {
	short x;
	int y;
};

int selectSort(int arr[], int size){
	int tmp;
	for(int i=1; i < size; i++){
		for(int j=size-1; j >= i; j--) // Перебор элементов
			if (arr[j-1] > arr[j]){ 
				tmp = arr[j-1]; // Перестановка элементов
				arr[j-1] = arr[j];
				arr[j] = tmp;
			}
	}
	return 0;
}


using namespace std;

int operator<(Data d1,Data d2){
	return (d1.x < d2.x);
}

template<class T>
void selectSort(T a[], int size) {
	int i, j, k; 
	T x;

	for( i=0; i < size; i++) {   	// i - номер текущего шага
		k=i; x=a[i];

		for( j=i+1; j < size; j++){	// цикл выбора наименьшего элемента
			if ( a[j] < x ) {
				k=j; x=a[j];	        // k - индекс наименьшего элемента
			}
		}

		a[k] = a[i]; 
		a[i] = x;   	// меняем местами наименьший с a[i]
	}
}

int isDivisibleR(int n, int b = 1){
	if((b%10) == 0){
		return 1;
	} else {
		if((n % (b %10)) > 0){
			return 0;
		} else {
			return isDivisibleR(n, b / 10);
		}
	}
}

int isDivisible(int n){
	return isDivisibleR(n, n);
}

void drawMenu(){
	cout<<
		"Please select one of menu items: "<<endl <<
		"1 - Check if the number is divisible on each one of it's digits" <<	endl<<
		"2 - Check if the balance brace is correct" << endl<<
		"0 - Exit" << endl;
}


void menuIsDivisible(){
	int n;
	cout << "Please input number : " << endl;
	cin >> n;

	cout << "The number is ";
	if(!isDivisible(n)){
		cout << " not ";
	}
	cout << "divisible on each of it's digits" << endl;
}


int checkBalanceRecursive(int pos, const char *s, size_t len){
	int i;
	int balanced = 0;
	int status = 0;

	if(pos == len)
		return -len;

	for(i = pos + 1; i < len; i++){
		if(s[i] == ')') { 
			return i;
		} 
		if(s[i] == '('){
			status = checkBalanceRecursive( i , s, len) ;
			if(status < 0){
				return status;
			} else {
				i = status;
			}
		} 

	}
	return -1;
}



bool checkBalance(int pos, const char *s, size_t len){
	int i = 0;
	int status = 0;
	bool balanced = false;
	int position = -1;


	for(i = 0; i < len; i++){
		if(s[i] == ')'){
			return false;
		}
		
		if(s[i] == '(')	{
			status = checkBalanceRecursive(i, s, len);
			if(status < 0){
				balanced = false;
				cout << "Unable to find closing for " << -1 * status << " brace" << endl;
				break;
			}
			i = status;

		}
	}

	if(status > 0){
		cout << "Status" << status<<endl;
		balanced = true;
	}


	return balanced;
}


void menuBraceBalance(){
	string s;

	cout << "Pease input string for balance brace check: " << endl;
	cin >> s;
	if(checkBalance(0, s.c_str(), s.length())){
		cout << "Balance is correct" << endl;
	} else {
		cout << "Balance is not correct"<<endl;
	}
}


char handleMenu(){
	char d;
	cin >> d;
	switch(d){
	case '1':
		menuIsDivisible();
		break;
	case '2':
		menuBraceBalance();
		break;
	default:
		break;
	}
	return d;
}

int main(){
	int arr[500];
	char key;
	for(int i = 0; i < 500; i++){
		arr[i] = rand();
	} 
	selectSort(arr, 500);
	for(int i = 0; i < 500; i++){
		cout << arr[i] << endl;
	}

	do {
		drawMenu();
		key = handleMenu();
	} while (key != '0');
}