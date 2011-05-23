#include <stdio.h>

/*
 Длинна используемых массивов
*/
#define ARR_LEN 10
typedef int arrType;
#define EXIT_SIGNAL '0'

#define TEXT_FILE_NAME "tests.txt"
#define BIN_FILE_NAME "tests.dat"
/*
 Функция для отображения массива на экране
*/
void printArray(arrType * arr){
	int i;
	for(i = 0; i < ARR_LEN; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int writeSingleArrayToBinaryFIle(const char * filename, arrType * arr, int writeAppend){
	FILE * outFile;
	
	outFile = writeAppend?fopen(filename, "ab"):fopen(filename, "wb");
	if(!outFile){
		fprintf(stderr, "Failed to open '%s' file\n", filename);
		return 1;
	}
	fwrite(arr, sizeof(arrType), ARR_LEN, outFile);
	fclose(outFile);
	return 0;
}


int readSingleArrayFromBinary(const char * filename, arrType * arr){
	FILE * inFile;
	inFile = fopen(filename, "rb");
	if(!inFile){
		fprintf(stderr, "Failed to open '%s' file\n", filename);
		return -1;
	}
	fread(arr, sizeof(arrType), ARR_LEN, inFile);
	fclose(inFile);
	return 0;
}

int readFromTextFile(const char * filename){
	FILE * inputFile;
	arrType arr[ARR_LEN];
	int i;
	inputFile = fopen(filename, "r");//Открываем файл только для чтения
	if(!inputFile){
		fprintf(stderr, "Failed to open '%s' file\n", inputFile);
		return 1;
	}
	while(!feof(inputFile)){//Читаем файл, пока в нём есть содержимое
			for(i = 0; i < ARR_LEN; i++){
				fscanf(inputFile, "%d", &arr[i]);//Используем форматный ввод для записи элемента массива
			}
	}
	fclose(inputFile);
	return 0;
}

int convertTextToBinaryFiles(const char* textFileName, const char* binaryFileName){
	FILE * inFile = fopen(textFileName, "r");
	FILE * outFile = fopen(binaryFileName, "w");
	int dbgcnt= 0;
	arrType buf[ARR_LEN] = {0};
	int i;
	if(!inFile || !outFile){
		fprintf(stderr, "Failed to open %s or/and %s file(s)", textFileName, binaryFileName);
		return 1;
	}
	fclose(outFile);

	while(!feof(inFile)){//Читаем файл, пока в нём есть содержимое
			for(i = 0; i < ARR_LEN; i++){
				fscanf(inFile, "%d", &buf[i]);//Используем форматный ввод для записи элемента массива
			}
			writeSingleArrayToBinaryFIle(binaryFileName,buf, 1);
	}
	return 0;
}

int readArrayFromBinary(FILE * inFile, int n, arrType * arr){
	int elementsRead; 
	fseek(inFile, n * sizeof(arrType[ARR_LEN]), SEEK_SET);
	if(feof(inFile)){
		return 1;
	}
	elementsRead = fread(arr, sizeof(arrType), ARR_LEN, inFile);
	if(elementsRead != ARR_LEN){
		return 1;
	} else {
		return 0;
	}
}

int printAllFromBinary(const char * filename){
	FILE * inFile;
	arrType tmp[ARR_LEN];
	int i = 0;

	inFile = fopen(filename, "rb+");
	if(!inFile){
		fprintf(stderr, "Failed to open %s file\n", filename);
		return 1;
	}
	while(readArrayFromBinary(inFile, i++, tmp) == 0){
		printArray(tmp);
		if(feof(inFile)){
			break;
		}
	}
	return 0;
}

int writeSingleArrayToTextFile(FILE * outFile, arrType * arr){
	int i;
	for(i = 0; i < ARR_LEN; i++){
		fprintf(outFile, "%d ", arr[i]);
	}
	fprintf(outFile, "\n");
	return 0;
}

int removeItemFromTextFile(const char * filename, int indexToRemove){
	char tmpFilename[] = "tmp.bin";
	FILE * inFile = fopen(filename, "r");
	FILE * outFile;
	FILE * tmpFile;
	int itemsRead = 0;
	arrType buf[ARR_LEN];
	int r = 0;
	int i;
	
	while(!feof(inFile)){
			for(i = 0; i < ARR_LEN; i++){
				fscanf(inFile, "%d", &buf[i]);//Используем форматный ввод для записи элемента массива
			}
			if(++itemsRead != indexToRemove){
				writeSingleArrayToBinaryFIle(tmpFilename, buf, 1);
			}
	}
	if(itemsRead < indexToRemove){//Элементов меньше, чем индекс элемента, который надо удалить
		printf("Index %d out of current text file records bounds\n", indexToRemove);
		remove(tmpFilename);
		return 1;
	}
	fclose(inFile);
	tmpFile = fopen(tmpFilename, "rb");
	outFile = fopen(filename, "w+");
	while(readArrayFromBinary(tmpFile, r++, buf) == 0){//Читаем из временного бинарного файла
		writeSingleArrayToTextFile(outFile, buf);//И записываем в тестовый
	}
	fclose(outFile);
	remove(tmpFilename);
	return 0;
}

arrType * inputArray(arrType * arr){
	arrType tmp;
	int result;
	int i;
	for(i = 0; i < ARR_LEN; i++){
		result = 0;
		do {
			fflush(stdin);
			printf("Please input %d element : ",i);
			result = scanf("%d", &tmp);	
		} while(result == 0);
		arr[i] = tmp;
	}
	return arr;
}

void drawMenu(){
	printf("Please, select action number and press enter : \n");
	printf("1 - convert text file to binary\n");
	printf("2 - display all values from binary file\n");
	printf("3 - remove element by index from the text file\n");
	printf("4 - replace value by index\n");
	printf("5 - perform a magic search\n");
	printf("0 - Exit programm\n");
}

void menuTextToBinary(){
	printf("Converting tests from text to binary format...\n");
	convertTextToBinaryFiles(TEXT_FILE_NAME, BIN_FILE_NAME);
	printf("Done.\n");
}

void menuDiplayBinaryFileValues(){
	printAllFromBinary(BIN_FILE_NAME);
}

void menuRemoveArrayFromFile(){
	int index;
	do {
		printf("Please input array index to remove:");
	} while(scanf("%d", &index) == 0 && printf("\n"));
	removeItemFromTextFile(TEXT_FILE_NAME, index);
}

int replaceArrayInBinaryFile(char * filename, int index, arrType * arr){
	FILE * outFile;
	arrType tmp[ARR_LEN];
	outFile = fopen(filename, "rb+");
	printf("Replacing %d index ...\n", index);
	if(!outFile){
		fprintf(stderr, "Failed to open %s file\n", filename);
		return 1;
	}

	if(readArrayFromBinary(outFile, index, tmp) == 1){
		fprintf(stderr, "Index not found \n");
		return 1;
	}
	fseek(outFile, index * sizeof(arrType[ARR_LEN]), SEEK_SET);
	fwrite(arr, sizeof(arrType), ARR_LEN, outFile);
	fclose(outFile);
	return 0;
}

void menuReplaceArray(){
	int index;
	arrType arr[ARR_LEN];
	do {
		printf("Please input array index to replace:");
	} while(scanf("%d", &index) == 0 && printf("\n"));
	inputArray(arr);
	replaceArrayInBinaryFile(BIN_FILE_NAME, index, arr);
}


int isConditionApplied(arrType item){
	return (item > 50 && item < 89);	
}

void displayLongestSequence(arrType * arr, int (*condition)(arrType el)){
	int seqStart = 0, seqEnd = 0;
	int i,j;
	for(i = 0; i < ARR_LEN; i++){
		for(j = i; j < ARR_LEN; j++){
			if(condition(arr[j])){
				if((j-i) > (seqEnd - seqStart)){
					seqStart = i;
					seqEnd = j;
				}
			} else {
				break;
			}

		}
	}
	printf("Longest sequence: ");
	for(i = seqStart; i < seqEnd + 1; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int menuSearchForLongestSequence(){
	FILE * inFile = fopen(BIN_FILE_NAME, "rb");
	arrType arr[ARR_LEN];
	int (*f)(arrType el);
	f = isConditionApplied;

	if(!inFile){
		fprintf(stderr, "Failed to open binary file\n");
		return 1;
	}
	fseek(inFile,-sizeof(arrType[ARR_LEN]), SEEK_END);
	fread(arr, sizeof(arrType),ARR_LEN, inFile);
	displayLongestSequence(arr, f);
	return 0;
}

char handleMenuSelect(){

	char key = 0;
	fflush(stdin);
	while(!scanf("%c", &key) && key < '0' && key > '9'){
		fflush(stdin);
		printf("Please select a valid menu item\n");
	}
	switch(key){
	case '1':
		menuTextToBinary();
		break;
	case '2':
		menuDiplayBinaryFileValues();
		break;
	case '3':
		menuRemoveArrayFromFile();
		break;
	case '4':
		menuReplaceArray();
		break;
	case '5':
		menuSearchForLongestSequence();
		break;
	default:
		break;
	}
	return key;
}

int main(){
	char key;
	do {
		drawMenu();
		key = handleMenuSelect();
	} while(key != EXIT_SIGNAL);
	return 0;
}
