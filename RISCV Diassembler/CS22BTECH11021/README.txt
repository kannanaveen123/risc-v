                                                                                    COMPUTER ARCHITECTURE
                                                                                     LAB ASSIGNMENT - 3
                                                                                       CS22BTECH11019
                                                                                      ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------                                                                                                                                                                                                                         
 README FOR THIS CODE:
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
# README - RISC-V Disassembler

This is a C program designed to serve as a disassembler for RISC-V assembly instructions. It takes a sequence of hexadecimal values as input, converts them to binary representation, and then interprets the binary representation to print out the corresponding RISC-V assembly instructions.

## Features
- Supports a wide range of RISC-V instructions, including R-type, I-type, S-type, B-type, J-type, and U-type instructions.
- Converts hexadecimal input values to binary representation.
- Parses and disassembles binary instructions to provide human-readable RISC-V assembly instructions.

## How to Use
1. Compile the program using a C compiler (e.g., gcc).

2. Run the compiled program.

3. Input a sequence of hexadecimal values (one per line).

4. The program will output the corresponding RISC-V assembly instructions for each input value.

5. To Run the Input files You should change the array size corresponding to total no:of inputs.

## NOTE BY AUTHOR
    1. MY code takes the input in an array so every time change the array size in my code I Intialize the array size of input as 20.

    2. Implementation of jalr is done as follows
        jalr rd rs1 immediate.
    
    3. My code is not  capable of disassembling negative immediate
        values for B/J format.it give labels fo the positive immediates only.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



