// struct if_stat {
// 	char symbol;
// 	char newSymbol;
// 	int cursorMove;
// 	int jumpToLine;
// };

struct IF_STAT {
	char symbol;
	char newSymbol;
	unsigned int cursor;
	unsigned int jump;
}

class CODE_LINE {
private:
	std::vector <IF_STAT> cas;
public:
}

/*
	funzione che cerca il symbol e ritorna l'indice
*/

// class linea_codice {
// private:
// 	int alpha_len;
// public:
// 	int lineNumber;
// 	if_stat entry[alpha_len];

// };

// linea_codice::linea_codice (int alphabetLenght){
// 	alpha_len = alphabetLenght;
// };