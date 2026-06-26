CCP6124 - Virtual Machine and Assembly Language Interpreter

Project Overview

This project is a C++ implementation of a custom Virtual Machine (VM) and Assembly Language Interpreter for the CCP6124 Object-Oriented Programming and Data Structures module.

The interpreter reads a custom .asm assembly language file, parses the instructions using strict Object-Oriented Programming principles (Inheritance, Polymorphism, Composition), and executes them in a simulated hardware environment without the use of the C++ Standard Template Library (STL).

Team Members (Group TTXX_GXX)

Member 1: [Muhammad Muhyideen bin Barakath Ali] (ID: [253UC243K8]) - Data Structures & OOP Core

Member 2: [Shaarvin] (ID: [253UC243XH]) - CPU, Memory & Runner

Member 3: [Roshan A/L Sahadevan] (ID: [253UC243CY]) - Core Instructions & Flags

Member 4: [Nimalen A/L Ramakrishnan] (ID: [253UC242QD]) - Advanced Instructions & Demo Orchestration

Virtual Machine Architecture

Registers: 8 general-purpose registers (R0 to R7), 1 byte each (signed char, -128 to 127).

Memory: 64 bytes of main memory (addressed 0 to 63).

Special Registers: Program Counter (PC) and Stack Index (SI).

Flags: Overflow (OF), Underflow (UF), Carry (CF), and Zero (ZF).

Data Structures: Custom built Dynamic Array (MyVector), MyStack, and MyQueue (No STL).

🛠️ User Manual: How to Compile and Run

Prerequisites: You must have a C++ compiler installed (such as GCC/G++) and access to a command-line interface (Terminal on Mac/Linux, or Command Prompt/PowerShell/MinGW on Windows).

Step 1: Navigate to the project folder
Open your terminal and use the cd command to navigate to the directory containing the source code.

cd path/to/TT01_G01


Step 2: Compile the source code
Compile the single .cpp file using g++. We recommend compiling with at least the C++11 standard.

g++ TT01_G01.cpp -o vm


(This command tells the compiler to compile TT01_G01.cpp and output an executable named vm or vm.exe on Windows).

Step 3: Run the interpreter
Execute the compiled program. Ensure your assembly test files (e.g., program.asm) are in the same directory.

# On Mac/Linux:
./vm

# On Windows:
vm.exe


Follow the on-screen prompts if the program asks for an input .asm file, or if it pauses for the INPUT assembly instruction.

⚠️ Internal Team Rules & Constraints Reminders

Do not violate these rules as they carry heavy marking penalties:

Single File Submission: All final code must be merged into TTXX_GXX.cpp.

NO STL: <vector>, <stack>, <queue>, <list>, etc., are strictly forbidden.

35-Line Limit: NO function can exceed 35 lines of code. Break larger functions down into helpers!

Mandatory Comments: Every class and function MUST have // Author: [Name] above it.

Encapsulation: ALL class variables must be private.