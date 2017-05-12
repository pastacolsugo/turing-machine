#include <regex>
#include <stdio.h>
	
std::regex line("^(line )([0-9]+)$");

int main (){

	char stringa[1000];
	scanf("%s", stringa);

	printf ("%i\n", std::regex_match(stringa, line));
}
