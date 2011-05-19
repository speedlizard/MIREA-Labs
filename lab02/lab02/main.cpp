#include <iostream>
#include <algorithm>

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

int selectSort(char arr[], int size){
	char tmp;
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
"2 - Sort" << endl<<
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

char handleMenu(){
	char d;
	cin >> d;
	switch(d){
	case '1':
		menuIsDivisible();
		break;
	case '2':
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

	if(isDivisible(33)){
		cout << "Divisible";
	}

	do {
		drawMenu();
		key = handleMenu();
	} while (key != '0');
}