/*
	Code file structure:
	N M 	//N are the lines of code, M are the number of states used in this program
	AB		//in case of two states. AB are two boolean numbers, if it's true (1) there is some code for the state, if it's false (0) there is not
	A A A	//A A A is the code for the first if statement. First A is value change, second A is direction, third A line jump number (not needed if its just 1 line)
	B B B	//B B B is the code for the second if statement. Same as above.
	.
	.	N times
	.

	Example (makerfaire demo):
	1 3		//1 line of code, 3 states used	
	111		//do something either if you find 0, 1 and 2
	1 1 	//if it's 0, switch to 1, move right
	2 1 	//if it's 1, switch to 2, move right
	1 1 	//if it's 2, switch to 1, move right

*/

#include <iostream>
#include <regex>
#include <stdio.h>
#include <string>
#define memSize 5 //the size of machine's memory

std::regex validChar ("[0-4]*");
std::string memory;	//the array represent the "string" of turing machine
/*	
 *	0 = off
 *	1 = white
 *	2 = red
 *	3 = green
 *	4 = blue
 */

int cursorIndex,	//the cell index of the cursor
	N,
	M;

class lineOfCode(int S) {
	int lineIndex,
		states = S;
	char flags[states+1];
	int commands[states][3];
};

bool inputData (){	//function that allows the user to input data into the machine memory
	printf ("This Turing Machine has %d cells of memory\nInput the content of each one :\n", memSize);
	std::cin >> memory;
	if (memory.size() > memSize){
		printf ("Too many data\n");
		return false;
	}
	if (!std::regex_match(memory, validChar)){
		printf("Invalid character\n");
		return false;
	}
	if (memory.size() != memSize){
		memory.resize(memSize);
		//std::cout << memory.size();
	}
	return true;
}

int main() {
	FILE *fin;
	fopen ("code.txt", "r");
	if (fin == NULL){
		printf ("File opening error\n");
		return 0;
	}
	if (!inputData()){
		return -1;
	}
	fscanf (fin, "%d %d", &N, &M);
	for ()
}