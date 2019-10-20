# 8085Simulator
A 3 layer 8085 simulator with 
	1. One Pass Macro Processor
	2. Two Pass Assembler
	3. Simulator

Commands to create object file:
	./assemble <filename>

Commands to simulate object file:
	./simulate <objectFileName>

Followig intermediate files are created:
1. Code_after_macroprocessor_pass.txt - 
	processed file after macroprocessor required as an input for 		pass1 of the assembler.
2. inter.txt -
	File created after Pass1 of the assembler is completed.
3. symTab.txt - 
	File to show the symbol table created by the Pass1 of the 		assembler.
4. memory.txt - 
	To show the values stored in the memory after simulation.

File Name is "CODE.txt"
Object File name: *.obj (created by the assembler)
