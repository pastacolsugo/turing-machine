/*
	
*/

#include "define.h"
#include <iostream>
#include <map>
#include <regex>
#include <stdlib.h>
#include <string>
#include <vector>

#define DEBUG false

struct DO {
	char newSymbol;
	int moveCursor;
	unsigned int jumpLine;
};

std::regex line("^line [0-9]+$");

std::map <char, DO> code[100];

std::string input;
std::string alfabeto;
std::string tape;

bool isValid (char c);
bool isAlphabet (char c);
void inputMalformato (char* info);
void printalphabet ();
void printTape ();
int commentRemover ();
void printInput ();
int codeFinder (int start);
int lineReader (int index);
int codeSpaceRemover (int index);

int main (){
	printf ("Apro il file di input... ");
	FILE* inputFilePointer = fopen ("input.txt", "r");	//apertura file
	if (inputFilePointer == NULL){						//controllo puntatore
		printf("Errore nell'apertura del file\n");
		return 0;
	}
	printf ("fatto\n");

	/*
		lettura del file di input
	*/
	{
		printf ("Leggo il file di input... ");
		char c;
		do {		//leggo tutto il file di input nel vector input
			c = fgetc(inputFilePointer);
			input.pb(c);
		} while (c != EOF);
		//free(&c);

		if (input.size() == 0){		//controllo che ci sia effettivamente qualcosa
			printf("The input file is Empty!\n");
			return 0;
		}

		if (input[input.size()-2] != '\n'){		//controllo a capo alla fine del FILE //-2 perche' -1 e' EOF
			printf("Missing newline at the end of file\n");
			//printf("%i\n", input[input.size()-1]);
			return 0;
		}
	}
	printf("fatto\n");

	//debug stuff
	{
		if (DEBUG){
			printf ("Stampare il file di input? (y/n) ");
			char stampa = 'n';
			scanf ("%c", &stampa);
			if (stampa == 'y' || stampa == 'Y'){
				printf ("File di input:\n");
				printInput();
			}
		}
	}

	printInput();
	commentRemover();
	printInput();

	//debug stuff
	{
		if (DEBUG){
			printf ("Stampare dopo la rimozione dei commenti? (y/n) ");
			char stampa1 = 'n';
			scanf ("%c", &stampa1);
			scanf ("%c", &stampa1);
			if (stampa1 == 'y' || stampa1 == 'Y'){
				printInput();
			}
		}
	}

	int input_index = 0;
	/*
			PARSING ALFABETO
	*/
	{
		bool leggo_alfa = true;
		if (input[0] == '[') {		//controllo la prima parentesi
			for (input_index=1; true; input_index++){	
				char a = input[input_index];
				//printf ("%c\n", a);
				if (a == ']'){
					break;				//finito l'alfabeto
				}
				if (a == ' ' || a == ',')	{		//ignoro gli spazi e le virgole
					continue;
				}
				if ( isValid(a) ){			//se e' valido lo aggiungo all'alfabeto
					alfabeto.push_back(a);
				} else {
					inputMalformato("alfabeto");	//negli altri casi mi fermo e stampo l'errore
					return 0;
				}
			}
		} else {
			inputMalformato("inizio alfabeto");
			return 0;
		}
		//free(&leggo_alfa); //non si puo' fare

		if (alfabeto.size() < 1){		//se l'alfabeto non contiene niente
			inputMalformato("size alfabeto");
			return 0;
		}
	}

	/*
		PARSING TAPE
	*/
	{
		/*//printf ("%c\n", input[input_index]);
		input_index	+= 3;		//mi sposto sulla prima parentesi quadra
		//printf ("%c\n", input[input_index]);
		*/

		//cerco la parentesi
		for (input_index = input_index; input[input_index] != '[' && input[input_index] != EOF; input_index++) {	}

		//printf ("%c\n", input[input_index]);
		if (input[input_index] == '['){		//se e' una parentesi quadra (double check)
			for (input_index = input_index+1; true; input_index++){		//scorro il tape nell'input
				char t = input[input_index];
				//printf ("%c\n", t);
				if (t == ']' || t == EOF){	//se e' una parentesi quadra chiusa (fine tape) o EOF
					break;		//esco
				}
				if (isValid(t) && isAlphabet(t)){	//se e' un carattere valido ed e' stato dichiarato nell'alfabeto
					tape.push_back(t);		//lo aggiungo in coda al tape
				} else {							//se non e' valido o non e' stato dichiarato
					inputMalformato("tape");		//errore
					return 0;						//esco
				}
			}
		} else {
			inputMalformato("inizio tape");
			return 0;
		}

		if (tape.size() < 1){	//se il tape non contiene niente
			inputMalformato("tape size");
			return 0;
		}
	}

	// printInput();
	// trovo l'inizio del 
	// printInput();
	// printf ("\n%c%c%c\n", input[input_index-1], input[input_index], input[input_index+1]);
	// printf ("%lu\n", input.size());
	int codeStart = codeFinder(input_index);
	// printf ("%c %i\n", input[codeStart], codeStart);
	
	// input[codeStart] = '#';	//check primo carattere del codice
	// printInput();	

	if (codeStart == -1 || codeStart >= input.size()){	// controllo che sia stato trovato l'inizio del codice
		printf("Errore Inizio Codice\n");
		return 0;
	}
	// now the codeStart is pointing on the 'l' of the first "line x"

	// codeSpaceRemover(codeStart);		//tolgo gli spazi
	// printInput();

	// for (int i = codeStart; i<codeStart+5; i++){
	// 	printf("%c", input[i]);
	// }
	lineReader(codeStart);


}

int lineReader (int index){
	// if (input[index] == 'l' && input[index+1] == 'i' && input[index+2] == 'n' && input[index+3] == 'e'){
	// 	index += 4;
	// 	printf("%c%c%c\n", input[index], input[index+1], input[index+2]);
	// }	

	// printf("%c/n", input[index+5]);
	

	return 1;
}	// da finire

int codeSpaceRemover (int index){ // supposed to be the codeStart ('l' of the first "line")
	int b;	// primo carattere da eliminare (spazio o tab)
	for (b=6; true; b++){
		if (input[index+b] == '\n'){	// se trovo subito il newline e' gia a posto
			return 0;	
		}
		if (input[index+b] != ' ' || input[index+b] != '\t'){		// se trovo un carattere diverso da uno spazio o tab il numero della linea e' multicifra
			continue;	// quindi proseguo
		} else {		// se e' spazio o tab
			break;		// esco dal for
		}	
	}

	int e;
	for (e = b; input[index+e] != '\n'; e++){	}	// trovo la fine dell'intervallo
	

}	// da finire

int codeFinder (int start){
	for (int i=start; i<input.size()-7; i++){
		if (input[i] == 'C' && input[i+1] == 'O' && input[i+2] == 'D' && input[i+3] == 'E' && input[i+4] == '\n'){
			return i+5;
		}
	}
	return -1;
}	// finito

int commentRemover (){
	for (int i=0; i<input.size()-2; i++){
		if (input[i] == '/' && input[i+1] == '/'){
			int j;
			for (j=i; input[j] != '\n' && input[j] != EOF; j++)	{	};
			if (input[j] != EOF){
				input.erase(input.begin()+i, input.begin()+j);
			}
		}
		if (input[i] == '/' && input[i+1] == '*'){
			// printf ("MULTI COMMENT : %i\n", i);
			int j=i+3;
			// printf ("Boolean expression evaluate as: %d\n", (int) input[j-1] != '*' && input[j] != '/' && input[j] != EOF);
			// printf ("Single expressions evaluate as: %d %d %d\n", (int) input[j-1] != '*', (int) input[j] != '/', (int) input[j] != EOF);
			// printf ("input[j] w/ j=%d --> %c%c%c\n", j, input[j-1], input[j], input[j+1]);
			for (j=i+3; input[j-1] != '*' && input[j] != '/' && input[j] != EOF; j++){
				// printf ("Char: %c\n", input[j-1]);
			};
			if (input[j] != EOF){
				input.erase(input.begin()+i, input.begin()+j+1);
			}
		}
	}
	return 1;
}	// finito

void printTape (){
	std::cout << std::endl << "il tape e' : ";
	for (int i=0; i<tape.size(); i++){
		std::cout << tape[i] << " ";
	}
	std::cout << std::endl;
}	// finito

void printalphabet (){
	printf ("l'alfabeto e': ");
	for (int i=0; i<alfabeto.size(); i++){
		std::cout << alfabeto[i] << " ";
		std::cout << std::endl;
	}
}	// finito

bool isAlphabet (char c){
	for (int i=0; i<alfabeto.size(); i++){
		if (alfabeto[i] == c){
			return true;
		}
	}
	return false;
}	// finito

bool isValid (char c){
	if (c <= '9' && c >= '0'){
		return true;
	}
	if (c <= 'Z' && c >= 'A'){
		return true;
	}
	if (c <= 'z' && c >= 'a'){
		return true;
	}
	return false;
}	//finito

void printInput (){
	for (int i=0; i<input.size()-1; i++){ //-1 per non stampare EOF
		std::cout << input[i];
	}
	printf ("END\n");
}	//finito

void inputMalformato (char* info){
	printf ("Input malformato\n%s\n", info);
}	//finito