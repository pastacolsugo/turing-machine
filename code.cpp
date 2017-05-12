#include <stdio.h>
#define MEMORY_SIZE 24		//how big is the memory
#define STATES 2 			//how many states each cell can have.

const char	prompt[] = "> ",
			welcomeMessage[] = "Turing Machine Simulator\nType 'help' to get help:\n";


void ERROR (char E[]){
	printf("Error: %s\n", E);
};

class Cursor {
 private:
 	int cursorPos;

 public:
 	Cursor (){		//overloaded constructor
 		cursorPos = 0;
 	};

 	Cursor (int pos){
 		cursorPos = pos;
 	};
 	
 	int move (int D){
 		if (D > -2 && D < 2){ // -1 <= D <= 1
 			cursorPos += D;
 			return cursorPos;
 		} else {
 			ERROR ("Cursor movement value is wrong");
 			return cursorPos;
 		}
 	}

 	int pos (){
 		return cursorPos;
 	}

};

struct instructionSet {		//what to do if state is [i]
	int switchState,	//switch state to
		moveCursor,		//move cursor -1 0 1 (left, still, right)
		jumpToLine;		//line to jump to
	bool Error;
};

class LineOfCode {	// single line of code, containing STATES if-statements
//########################
	public:
	 	LineOfCode (void){		//constructor
	 		lineIndex = -1;		//line index still unset, control value -1
	 		for (int i=0; i<STATES; i++){			//for each STATE
	 			inst[i].switchState = -1;			//change to state <CONTROL>
	 			inst[i].moveCursor = 2;			//move cursor to <CONTROL>
	 			inst[i].jumpToLine = -1;			//jump to line <CONTROL>
	 			inst[i].Error = true;
	 		}
	 	};

	 	bool indexSet (int ind){		//line index setter
	 		if (ind == lineIndex) return true;
	 		int oldVal = lineIndex;
	 		lineIndex = (ind >= 0 && ind <= MEMORY_SIZE)? ind : lineIndex;		
	 		return (lineIndex != oldVal)? true : false;
	 	}

	 	int indexGet (){
	 		return lineIndex;
	 	}

	 	bool write (int state, int nextState, int cursorMove, int jumpTo){
	 		inst[state].switchState = nextState;
	 		inst[state].moveCursor = cursorMove;
	 		inst[state].jumpToLine = jumpTo;
	 		inst[state].Error = true;
	 		if (inst[state].switchState == nextState &&
	 				inst[state].moveCursor == cursorMove &&
	 				inst[state].jumpToLine == jumpTo){
	 			inst[state].Error = false;
	 			return true;
	 		}
	 		return false;
	 	}

	 	instructionSet instGet (int state){
	 		if (state >= 0 && state < STATES){
	 			return inst[state];
	 		} else {
	 			ERROR("While retrieving instruction set: state do not exist");
	 			instructionSet a;
	 			a.Error = true;
	 			return a;
	 		}
	 	}

//############################
	private:
		int lineIndex;		// the index of the single line
		instructionSet inst[STATES];
};


LineOfCode sourceCode[MEMORY_SIZE];
Cursor cursor;
bool	memory[MEMORY_SIZE];


int execute (int *L)	{	
	int POS = cursor.pos();
	int S = memory[POS];	//get the state of the pointed cell
	instructionSet INST = sourceCode[*L].instGet(S);	//declare an instruction set with the instruction for this state
	memory[POS] = INST.switchState;		//change the state of the memory cell
	cursor.move(INST.moveCursor);	//move the cursor
	*L = INST.jumpToLine;


};

void Prompt (){
	printf (prompt);
}

int menu (){

}

int main(int argC, char *argV[]){
	

}