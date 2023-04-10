/**
 * Jonathan Stoll
 * 4-22-23
 * CS 219.1001
 */
 
 /**
 TODO: add C and V flags, impliment CMP and TST, remove "<this is for extra credit>" from optional instructions
 update in README: main(), parseInput(), performOperation(), printOutput()
 
 test all instructions on linux
 **/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

void performOperation(std::string, const int, const int, const int, const int, const int32_t);
std::string parseInput(std::string);
uint32_t convertToInt(const std::string);
int convertToInt(const char);
std::string toUpper(const std::string);
void printOutput(const std::string, const int[2]);
uint32_t registers[8];

int main() {
	// open the input file
  	std::ifstream inputFile("Programming-Project-3.txt");
  	
  	// ensure the file is successfully opened
  	if (!inputFile.is_open()) {
  		std::cout << "Could not open file" << std::endl;
  		return 1;
	}
	
	// iterate through the instructions
  	std::string instr;
	while (getline(inputFile, instr)) {
		std::string op = "";			// OPCODE
		int RD = 0, RN = 0, RM = 0, N = 0;	// register indexes and shift amount
		int32_t IMM = 0;			// immediate
		int flags[2] = {0, 0};  		// [N, Z]
		
		// parse the instruction for its operation, then parse for the remaining arguments
		op = toUpper(parseInput(instr.substr(0, 4)));
		RD = convertToInt(parseInput(instr.substr(4, 4)).back());
		
		if (op == "MOV") {
			IMM  = convertToInt(parseInput(instr.substr(8)));
		}
		else {
			RN = convertToInt(parseInput(instr.substr(8, 3)).back());
			
			if (op.substr(0, 3) == "LSL" || op.substr(0, 3) == "LSR" || op.substr(0, 3) == "ASR") {
				N = convertToInt(parseInput(instr.substr(11)));
			}
			else if (op.substr(0, 3) != "CMP" && op.substr(0, 3) != "TST") {
				RM = convertToInt(parseInput(instr.substr(11)).back());
			}
		}
		
		// perform the operation and determine the values of the flags
		performOperation(op, RD, RN, RM, N, IMM);
		if (toupper(op.back()) == 'S') {
			flags[0] = (registers[RD] <  0) ? 1 : 0;
			flags[1] = (registers[RD] == 0) ? 1 : 0;
		}
		
		// print the findings
		printOutput(instr, flags);
	}
  	
  	// close the file
  	inputFile.close();
  	
  	return 0;
}

// Takes all arguemnts and performs the operation
void performOperation(std::string op, const int RD, const int RN, const int RM, const int N, const int32_t IMM) {	
	op = op.substr(0, 3); // remove the possible 's' from the instruction
	
	if (op == "MOV")
		registers[RD] = IMM;
	else if (op == "ADD")
		registers[RD] = (registers[RN] + registers[RM]);
	else if (op == "AND")
		registers[RD] = (registers[RN] & registers[RM]);
	else if (op == "ASR") // fill with sign bit
		registers[RD] = (static_cast<int>(registers[RN]) >> N);
	else if (op == "LSR") // fill with zeros
		registers[RD] = (registers[RN] >> N);
	else if (op == "LSL") // fill with zeros
		registers[RD] = (registers[RN] << N);
	else if (op == "NOT")
		registers[RD] = (~registers[RN]);
	else if (op == "ORR")
		registers[RD] = (registers[RN] | registers[RM]);
	else if (op == "SUB")
		registers[RD] = (registers[RN] - registers[RM]);
	else if (op == "XOR")
		registers[RD] = (registers[RN] ^ registers[RM]);
}

// Takes a std::string and removes unnecessary characters
std::string parseInput(std::string str) {
	// Remove ' ', ',', '#', and '\r' from the string
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	str.erase(remove(str.begin(), str.end(), ','), str.end());
	str.erase(remove(str.begin(), str.end(), '#'), str.end());
	str.erase(remove(str.begin(), str.end(), '\r'), str.end());

	return str;
}

// Takes a std::string and returns that string in all uppercase
std::string toUpper(const std::string str) {
	std::string str2 = "";
	for (char c : str) {
		str2 += toupper(c);
	}
	return str2;
}

// Takes a std::string containing a 32-bit number in hex format and converts it to an integer
uint32_t convertToInt(const std::string str) {
	uint32_t num;   
	std::stringstream ss;
	
	ss << std::hex << str;
	ss >> num;
	
	return num;
}

// Takes a char and converts it to an int
int convertToInt(const char c) {
	return (int(c) - 48);
}

// Takes the details of an operation and output the results (including overflow detection) in the proper format
void printOutput(const std::string instr, const int flags[2]) {
	std::cout << instr << std::endl;
	std::cout << "R0:0x" << std::hex << std::uppercase << registers[0] << "  ";
	std::cout << "R1:0x" << std::hex << std::uppercase << registers[1] << "  ";
	std::cout << "R2:0x" << std::hex << std::uppercase << registers[2] << "  ";
	std::cout << "R3:0x" << std::hex << std::uppercase << registers[3] << "  " << std::endl;
	std::cout << "R4:0x" << std::hex << std::uppercase << registers[4] << "  ";
	std::cout << "R5:0x" << std::hex << std::uppercase << registers[5] << "  ";
	std::cout << "R6:0x" << std::hex << std::uppercase << registers[6] << "  ";
	std::cout << "R7:0x" << std::hex << std::uppercase << registers[7] << "  " << std::endl;
	std::cout << "N: " << flags[0] << "  Z: " << flags[1] << std::endl;
	std::cout << std::endl;
}
