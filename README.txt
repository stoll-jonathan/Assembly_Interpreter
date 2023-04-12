HOW TO RUN
To compile the main cpp file, use "g++ proj3.cpp -o proj3" in the terminal. You can then run the executable with "./proj3".

WORKING PROCESS
Registers and flags are stored as global arrays of size 8 and 4, respectively. "registers" stores registers numbered 0-7, in order. "flags" stores the N, Z, C, and V flags in that order.

The main function opens and reads the input file. Assuming the file is opened successfully, the text will be parsed line by line, treating each 
as a separate instruction. Each instruction will be stored in a string and that string will then be split to parse the operation and operands. 
The first four characters are stored in the "op" variable, which is used to determine the locations of the remaining operands. If the operation is "MOV", the remainder of the string is converted to and integer and assigned to "IMM". Otherwise, the next 4 characters are parsed for an integer, which is assigned to "RN". For shifts, the remainder will be assigned to "N". For CMP and TST, the remainder is converted to and integer and saved in RM. Because the register array is stored as uint_32t, the "0x" prefixes are automatically ignored during arithmetic and bitwise operations. 

Once the input is processed, the performOperation function is called, which updates both the registers and flags. The function consists of an if statement which will perform the appropriate operation according to the opcode. The details of this process are explained in the RESULTS section of this readme. Finally, a last function is called to format and output the data.


RESULTS
* The ADD and SUB commands simply add and subtract the operands using the '+' and '-' operators. C++ performs the binary arithmetic automatically.
* For AND, NOT, ORR, and XOR, the built-in bitwise operators are used. C++ converts the numbers to binary and performs the operations on each bit individually. That result is then converted back into hex format during output.
* The shift commands are performed using the stream operators (<< and >>). When given two integers as arguments, C++ knows to perform a left or right shift respectively. For the arithmetic shift, the shifting operand is converted to a signed integer. When passed a signed integer, the >> operator will shift in the sign bit.
* The CMP and TST commands will perform a SUB and AND operation, respectively. The flags are affected and the results are discarded.

The flags are stored in an array which defaults to [0, 0, 0, 0]. When an operation is performed, the the program will check if there was an S on the end of the opcode. If there was, the flags will be changed according to the value of the result. The flags will also be affected if the operation was CMP or TST.
