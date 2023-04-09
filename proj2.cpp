/**
 * Jonathan Stoll
 * 3-31-23
 * CS 219.1001
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

int32_t performOperation(std::string, const uint32_t, const uint32_t);
std::string removeSpaces(const std::string);
uint32_t convertToInt(const std::string);
void printOutput(const std::string, const uint32_t, const uint32_t, const uint32_t, const int[2]);

int main() {
	// open the input file
  	std::ifstream inputFile("Programming-Project-2.txt");
  	
  	// ensure the file is successfully opened
  	if (!inputFile.is_open()) {
  		std::cout << "Could not open file" << std::endl;
  		return 1;
	}
	
	// iterate through the instructions
  	std::string instr;
	while (getline(inputFile, instr)) {
		// parse the instruction for its operation and arguments
		std::string op = removeSpaces(instr.substr(0, 4));
		uint32_t arg1  = convertToInt(removeSpaces(instr.substr(5, 11)));
		uint32_t arg2  = convertToInt(removeSpaces(instr.substr(16)));

		// find the result and determine the values of the flags
		int32_t result = performOperation(op, arg1, arg2);
		int flags[2] = {0, 0}; // [N, Z]
		
		if (toupper(op.back()) == 'S') {
			flags[0] = (result <  0) ? 1 : 0;
			flags[1] = (result == 0) ? 1 : 0;
		}
		
		// print the findings
		printOutput(op, arg1, arg2, result, flags);
	}
  	
  	// close the file
  	inputFile.close();
  	
  	return 0;
}

// Takes two arguemnts and an operation to be performed. Performs the operation and returns the result
int32_t performOperation(std::string op, const uint32_t a, const uint32_t b) {	
	op = op.substr(0, 3); // remove the possible "s" from the instruction
	
	if (op == "ADD")
		return (a + b);
	else if (op == "AND")
		return (a & b);
	else if (op == "ASR") // fill with sign bit
		return (static_cast<int>(a) >> b);
	else if (op == "LSR") // fill with zeros
		return (a >> b);
	else if (op == "LSL") // fill with zeros
		return (a << b);
	else if (op == "NOT")
		return (~a);
	else if (op == "ORR")
		return (a | b);
	else if (op == "SUB")
		return (a - b);
	else if (op == "XOR")
		return (a ^ b);
}

// Takes a std::string possibly containing spaces and returns a version of that string with the spaces removed
std::string removeSpaces(const std::string str) {
	std::string str2 = "";
	
	// Iterate over the characters in str and add them to str2 if they are not spaces
	for (char x : str) {
		if (x != ' ')
			str2.push_back(x);
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

// Takes the details of an operation and output the results (including overflow detection) in the proper format
void printOutput(const std::string op, const uint32_t arg1, const uint32_t arg2, const uint32_t result, const int flags[2]) {
	std::cout << std::left << std::setw(6) << op << "0x" << std::uppercase << std::left << std::setw(8) << std::hex << arg1;
	
	if (op.substr(0, 3) != "NOT") // Don't print the second argument (0x0) if the operation only has one operand
		std::cout << "  0x"  << std::uppercase << std::left << std::setw(8) << std::hex << arg2;
					   
	std::cout << ": 0x" << std::uppercase << std::left << std::setw(8) << result << std::endl;
	std::cout << "N: " << flags[0] << "  Z: " << flags[1] << std::endl;
	std::cout << std::endl;
}
