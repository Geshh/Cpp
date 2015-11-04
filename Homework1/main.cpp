#include<iostream>
#include<stack>

const int multiplyer = 10;

char* multiply(int times, char* inputText) {
	int inputTextLength = strlen(inputText);
	char* newChar = new char[inputTextLength*times + 1];
	strcpy(newChar, "");
	for (size_t i = 0; i < times; i++) {
		strcat(newChar, inputText);
	}
	return newChar;
}


int main() {
	char* input = "4(AB2(Q)3(T))";
	std::stack<int> numberStack;
	std::stack<char*> charsStack;
	unsigned int charsCount = 1;

	for (int i = 0; i < strlen(input); i++) {

		if (input[i] >= 'A' && input[i] <= 'Z') {
			if (charsStack.empty()) {
				char* tmp = new char[2];
				strcpy(tmp, "");
				char inputTmp = input[i];
				tmp[0] = inputTmp;
				tmp[1] = '\0';
				charsStack.push(tmp);
			} else if (!charsStack.empty() && input[i - 1] >= 'A' && input[i - 1] <= 'Z') {
				char* tmp = new char[charsCount + 1 + 1];
				strcpy(tmp, charsStack.top());
				char inputTmp = input[i];
				tmp[strlen(charsStack.top())] = inputTmp;
				tmp[strlen(charsStack.top()) + 1] = '\0';
				charsStack.pop();
				charsStack.push(tmp);
				charsCount++;
			}
			else {
				char* tmp = new char[2];
				strcpy(tmp, "");
				char inputTmp = input[i];
				tmp[0] = inputTmp;
				tmp[1] = '\0';
				charsStack.push(tmp);
			}
		}
		else if (input[i] == ')'){
			if (charsStack.empty()){
				char* StringToMultiply = new char[strlen(charsStack.top()) + charsCount];
				strcpy(StringToMultiply, charsStack.top());
				charsStack.pop();
				char* multipliedString = new char[(numberStack.top()*strlen(StringToMultiply)) + 1];
				strcpy(multipliedString, multiply(numberStack.top(), StringToMultiply));
				numberStack.pop();
				charsCount = 1;
				charsStack.push(multipliedString);
			}
			else {
				char* StringToMultiply = new char[strlen(charsStack.top()) + charsCount];
				strcpy(StringToMultiply, charsStack.top());
				charsStack.pop();
				char* multipliedString = new char[(numberStack.top()*strlen(StringToMultiply)) + 1];
				strcpy(multipliedString, multiply(numberStack.top(), StringToMultiply));
				if (!charsStack.empty()) {
					char* combinedString = new char[strlen(multipliedString) + strlen(charsStack.top()) + 1];
					strcpy(combinedString, "");
					strcpy(combinedString, charsStack.top());
					strcat(combinedString, multipliedString);
					combinedString[strlen(multipliedString) + strlen(charsStack.top())] = '\0';
					charsStack.pop();
					charsCount *= numberStack.top();
					charsStack.push(combinedString);
				}
				else {
					charsStack.push(multipliedString);
				}
				numberStack.pop();
			}
		}
		else if (input[i] <= '9' && input[i] >= '1'){
			if (numberStack.empty()) {
				int inputTmp = input[i] - '0';
				numberStack.push(inputTmp);
			}
			else if (!numberStack.empty() && input[i - 1] <= '9' && input[i - 1] >= '1') {
				int tmpNum = numberStack.top();
				int inputTmp = input[i] - '0';
				numberStack.pop();
				numberStack.push(tmpNum*multiplyer + inputTmp);
			}
			else {
				int inputTmp = input[i] - '0';
				numberStack.push(inputTmp);
			}
		}
	}

	std::cout << charsStack.top();
	return 0;
}