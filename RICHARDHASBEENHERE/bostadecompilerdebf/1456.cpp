#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

#define MACHINE_SIZE 30000

using namespace std;

/* É nisso que dá quando o código é feito por noobs.  ¯\_(ツ)_/¯
   Sem suporte a nested loops e nada eficiente.
*/

typedef struct loop_t {

    int limiter, end;
	string instructions;

} loop;

class Machine {

	char machine[MACHINE_SIZE];                 // This is the array that'll represent the machine
	int idx;                                    // This is the index that'll be used to manipulate machine bytes
	string target;                              // This is the string the machine will use to search for input when needed
    int str_idx;                                // This is the index that will pretend the string is being read byte per byte

	public:

		/* O(n + 2) or O (log n + 2) */
		Machine(){                              // Creates machine with MACHINE_SIZE bytes equal to 0 and index at start

			memset(machine, 0, MACHINE_SIZE);
			idx = 0;
			str_idx = 0;

		}

		/* O(1) */
		void input(string str){                 // Defines target, where the code will search for info if there's any calls for input (commas).

			target = str;

		}

		/* O(n + 1) or O(2) */
		void read_byte(){             // Reads a character at idx from str.

            if(str_idx >= target.length())
                machine[idx] = 0;

			machine[idx] = target[str_idx++];

		}

		/* O(1) */
		void print_byte(){       // Prints a byte.

			cout << machine[idx];

		}

		/* O(10) */
		void print_first_ten(){

			for(int i = 0; i < 10; i++)
				cout << machine[i];

		}

		/* (min, max) = (O(1 + O(function/command)), O(7 + O(function/command)) */
		void byte_op(char sign){                // Define the behavior of the machine. Receives a sign and make an action from it. (It compiles everything.)

			switch(sign){
				case '<': idx--; break;
				case '>': idx++; break;
				case '.': print_byte();	break;
				case '#': print_first_ten(); break;
				case ',': read_byte(); break;
				case '+': machine[idx]++; break;
				case '-': machine[idx]--; break;
				default:
					cout << "wtf?! [sign= '" << sign << "']" << endl;
			}

		}

		/* O(3 + 3n) */
		vector<loop> precompile(string code){          // Precompile the code because of the loops

			vector<loop> loops;
			bool control = false;
			loop temp;

			for(int i = 0; i < code.length(); i++){

				if (control && code[i] != ']')
					temp.instructions += code[i];

				if (code[i] == '[')
					control = true;

				else if (code[i] == ']'){

					temp.end = i;
					control = false;
					loops.push_back(temp);

					temp.instructions = "";     // There is no need to reset end, as it'll be overwritten anyway, different than instructions

				}


			}

			return loops;

		}

		/* min = O(1), max ~= O(n^3) */
		void compile(string code){                  // When that method is called, it's necessarily a loop

            while((int)machine[idx] != 0)
    			for(int i = 0; i < code.length(); i++)
    				byte_op(code[i]);

		}

		/* O(n^3) */
		void compile(string code, vector<loop> loops){

			int actual_loop = 0;

			for(int i = 0; i < code.length(); i++){

				if (code[i] == '['){

					compile(loops[actual_loop].instructions);

					i = loops[actual_loop++].end + 1;	// This will move the i to the closing bracket

					if(i >= code.length())
						break;

				}

			    byte_op(code[i]);

			}


		}

		/* O(log n + 2) or O(n + 2) */
		void reset(){

			memset(machine, 0, MACHINE_SIZE);
			idx = 0;
			str_idx = 0;

		}

		/* O(1) */
		char* get_array(){
			return machine;
		}

};

int main(){

	int t;
	string str, code;

	Machine bf_comp;    // bf_comp stands for Brainfuck compiler
	vector<loop> aux;   // An auxiliar array that represents the loops

	cin >> t;

	/* Total time is probably around O(t * n^4). Fast! KKKK */
	for(int i = 0; i < t; i++){

		if(i > 0)
			cout << endl;

		getchar();

		cin >> str >> code;

		bf_comp.input(str);

		aux = bf_comp.precompile(code);

		cout << "Instancia " << i + 1 << endl;
		bf_comp.compile(code, aux);
		cout << endl;

		bf_comp.reset();

	}

	return 0;

}