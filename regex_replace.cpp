#include <iostream>
#include <cstring>
#include <regex>
#include <string>
#include <cstdio>

std::string input;
char r[] = "\\/\\*(\\*(?!\\/)|[^*])*\\*\\/";
std::regex multi_comm("\\/\\*(\\*(?!\\/)|[^*])*\\*\\/");
std::regex single_comm("//	.*$");

int main (){
	FILE *in = fopen ("input.txt", "r");
	if (in == NULL){
		printf ("errore file\n");
	}

	// printf ("%s\n", r);
	// return 0;

	char c;
	do {
		c = fgetc (in);
		input.push_back(c);
	} while (c != EOF);

	// std::cout << input << std::endl;

	input = std::regex_replace (input, multi_comm, "!");
	input = std::regex_replace (input, single_comm, "?");

	std::cout << input << std::endl;
	return 0;
}