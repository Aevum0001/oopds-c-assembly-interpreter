// ============================================================
// CCP6124 Object-oriented Programming and Data Structures
// Trimester 2610 - Virtual Machine Project
// FILE: TT01_G01.cpp
// DESCRIPTION: Complete VM Core (Member 1 + Member 2 Integrated)
// ============================================================

#include <iostream>
#include <string>   // Required for string tests to compile
#include <cstdlib>  // Required for exit(1) on stack crash / atoi

using namespace std;

// ============================================================
//  SECTION 1: MyVector (Dynamic Array - replaces std::vector)
// ============================================================

// Author: Muhammad Muhyideen
template <typename T>
class MyVector {
private:
    T* data;          // raw pointer to heap array
    int capacity;     // how many slots are allocated
    int count;        // how many slots are used

    // Author: Muhammad Muhyideen
    // Doubles the internal array capacity when full.
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Author: Muhammad Muhyideen
    // Constructor: initialises with capacity of 4.
    MyVector() {
        capacity = 4;
        count = 0;
        data = new T[capacity];
    }

    // Author: Muhammad Muhyideen
    // Copy constructor: performs deep copy to avoid shared pointers.
    MyVector(const MyVector<T>& other) {
        capacity = other.capacity;
        count = other.count;
        data = new T[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }

    // Author: Muhammad Muhyideen
    // Destructor: frees heap memory to prevent leaks.
    ~MyVector() {
        delete[] data;
    }

    // Author: Muhammad Muhyideen
    // Assignment operator: deep copy, guards against self-assignment.
    MyVector<T>& operator=(const MyVector<T>& other) {
        if (this == &other) return *this;
        delete[] data;
        capacity = other.capacity;
        count = other.count;
        data = new T[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    // Author: Muhammad Muhyideen
    // Adds an element to the end; resizes automatically if full.
    void push_back(const T& value) {
        if (count == capacity) {
            resize();
        }
        data[count] = value;
        count++;
    }

    // Author: Muhammad Muhyideen
    // Removes the last element if the vector is not empty.
    void pop_back() {
        if (count > 0) count--;
    }

    // Author: Muhammad Muhyideen
    // Returns element at index; prints error on out-of-bounds access.
    T get(int index) const {
        if (index < 0 || index >= count) {
            cout << "[MyVector ERROR] Index out of bounds." << endl;
            return data[0];
        }
        return data[index];
    }

    // Author: Muhammad Muhyideen
    // Sets element at index if index is valid.
    void set(int index, const T& value) {
        if (index >= 0 && index < count) {
            data[index] = value;
        }
    }

    // Author: Muhammad Muhyideen
    // Returns the number of elements currently stored.
    int size() const { return count; }

    // Author: Muhammad Muhyideen
    // Returns true if no elements are stored.
    bool isEmpty() const { return count == 0; }

    // Author: Muhammad Muhyideen
    // Resets element count to 0 (keeps allocated memory).
    void clear() { count = 0; }

    // Author: Muhammad Muhyideen
    // Returns current allocated capacity.
    int getCapacity() const { return capacity; }
};


// ============================================================
//  SECTION 2: MyStack (Fixed 8-slot Stack - replaces std::stack)
// ============================================================

// Author: Muhammad Muhyideen
class MyStack {
private:
    static const int MAX_SIZE = 8;  // VM spec: stack is exactly 8 bytes
    signed char data[MAX_SIZE];
    int topIndex;

public:
    // Author: Muhammad Muhyideen
    // Constructor: initialises empty stack with all slots zeroed.
    MyStack() {
        topIndex = -1;
        for (int i = 0; i < MAX_SIZE; i++) data[i] = 0;
    }

    // Author: Muhammad Muhyideen
    // Pushes value onto stack. Prints error if stack is full.
    void push(signed char value) {
        if (isFull()) {
            cout << "[MyStack ERROR] Stack overflow." << endl;
            return;
        }
        topIndex++;
        data[topIndex] = value;
    }

    // Author: Muhammad Muhyideen
    // Pops and returns top value. Crashes program if stack is empty
    // (required behaviour per assignment specification).
    signed char pop() {
        if (isEmpty()) {
            cout << "[MyStack CRASH] Stack underflow. Program terminated." << endl;
            exit(1);
        }
        signed char value = data[topIndex];
        topIndex--;
        return value;
    }

    // Author: Muhammad Muhyideen
    // Returns top value without removing it. Returns 0 if empty.
    signed char peek() const {
        if (isEmpty()) return 0;
        return data[topIndex];
    }

    // Author: Muhammad Muhyideen
    // Returns true if stack has no elements.
    bool isEmpty() const { return topIndex == -1; }

    // Author: Muhammad Muhyideen
    // Returns true if stack has reached maximum capacity (8 slots).
    bool isFull() const { return topIndex == MAX_SIZE - 1; }

    // Author: Muhammad Muhyideen
    // Returns number of items currently on the stack.
    int size() const { return topIndex + 1; }

    // Author: Muhammad Muhyideen
    // Returns SI register value (number of items on stack).
    int getStackIndex() const { return topIndex + 1; }

    // Author: Muhammad Muhyideen
    // Returns value at a specific slot index (used for memory dump).
    signed char getAt(int index) const {
        if (index < 0 || index >= MAX_SIZE) return 0;
        return data[index];
    }

    // Author: Muhammad Muhyideen
    // Resets stack to empty state, zeroes all slots.
    void reset() {
        topIndex = -1;
        for (int i = 0; i < MAX_SIZE; i++) data[i] = 0;
    }
};


// ============================================================
//  SECTION 3: MyQueue (Dynamic Queue - replaces std::queue)
// ============================================================

// Author: Muhammad Muhyideen
template <typename T>
class MyQueue {
private:
    T* data;
    int capacity;
    int frontIdx;
    int backIdx;
    int count;

    // Author: Muhammad Muhyideen
    // Doubles capacity and reorders elements to be contiguous.
    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[(frontIdx + i) % capacity];
        }
        delete[] data;
        data = newData;
        frontIdx = 0;
        backIdx = count;
        capacity = newCapacity;
    }

public:
    // Author: Muhammad Muhyideen
    // Constructor: initialises circular queue with capacity of 8.
    MyQueue() {
        capacity = 8;
        frontIdx = 0;
        backIdx = 0;
        count = 0;
        data = new T[capacity];
    }

    // Author: Muhammad Muhyideen
    // Copy constructor: deep copy of all elements.
    MyQueue(const MyQueue<T>& other) {
        capacity = other.capacity;
        frontIdx = other.frontIdx;
        backIdx = other.backIdx;
        count = other.count;
        data = new T[capacity];
        for (int i = 0; i < capacity; i++) data[i] = other.data[i];
    }

    // Author: Muhammad Muhyideen
    // Destructor: frees heap memory.
    ~MyQueue() { delete[] data; }

    // Author: Muhammad Muhyideen
    // Adds element to back of queue; resizes if full.
    void enqueue(const T& value) {
        if (count == capacity) resize();
        data[backIdx] = value;
        backIdx = (backIdx + 1) % capacity;
        count++;
    }

    // Author: Muhammad Muhyideen
    // Removes and returns front element. Returns default T if empty.
    T dequeue() {
        if (isEmpty()) return T();
        T value = data[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        count--;
        return value;
    }

    // Author: Muhammad Muhyideen
    // Returns front element without removing it.
    T front() const {
        if (isEmpty()) return T();
        return data[frontIdx];
    }

    // Author: Muhammad Muhyideen
    // Returns true if queue has no elements.
    bool isEmpty() const { return count == 0; }

    // Author: Muhammad Muhyideen
    // Returns number of elements in the queue.
    int size() const { return count; }

    // Author: Muhammad Muhyideen
    // Resets queue to empty (keeps allocated memory).
    void clear() {
        frontIdx = 0;
        backIdx = 0;
        count = 0;
    }
};


// ============================================================
//  SECTION 4: Register Hierarchy (Base + Derived Classes)
// ============================================================

// Author: Muhammad Muhyideen
// Abstract base class for all VM registers.
// Stores a signed byte (-128 to 127) and enforces clamping.
class Register {
private:
    signed char value;  // strictly private: access via getValue/setValue only

public:
    // Author: Muhammad Muhyideen
    // Constructor: initialises register value to 0.
    Register() { value = 0; }

    // Author: Muhammad Muhyideen
    // Virtual destructor for safe polymorphic deletion.
    virtual ~Register() {}

    // Author: Muhammad Muhyideen
    // Returns the current byte value stored in this register.
    signed char getValue() const { return value; }

    // Author: Muhammad Muhyideen
    // Sets register value; clamps to signed byte range (-128 to 127).
    virtual void setValue(int v) {
        if (v > 127)  v = 127;
        if (v < -128) v = -128;
        value = (signed char)v;
    }

    // Author: Muhammad Muhyideen
    // Resets register value to 0.
    virtual void reset() { value = 0; }

    // Author: Muhammad Muhyideen
    // Pure virtual: forces subclasses to provide a register name.
    virtual const char* getName() const = 0;
};


// Author: Muhammad Muhyideen
// Represents general-purpose registers R0 through R7.
// Inherits signed byte storage and clamping from Register.
class GeneralRegister : public Register {
private:
    char name[3];  // e.g. "R0" + null terminator = 3 chars

public:
    // Author: Muhammad Muhyideen
    // Constructor: takes register name string (e.g. "R0").
    GeneralRegister(const char* regName) {
        int i = 0;
        while (regName[i] != '\0' && i < 2) {
            name[i] = regName[i];
            i++;
        }
        name[i] = '\0';
    }

    // Author: Muhammad Muhyideen
    // Default constructor: sets name to "R?".
    GeneralRegister() {
        name[0] = 'R'; name[1] = '?'; name[2] = '\0';
    }

    // Author: Muhammad Muhyideen
    // Sets value using inherited clamping logic (-128 to 127).
    void setValue(int v) override {
        Register::setValue(v);
    }

    // Author: Muhammad Muhyideen
    // Resets register to 0 using base class logic.
    void reset() override {
        Register::reset();
    }

    // Author: Muhammad Muhyideen
    // Returns register name (e.g. "R0", "R7").
    const char* getName() const override {
        return name;
    }
};


// Author: Muhammad Muhyideen
// Represents a single flag bit: CF, OF, UF, or ZF.
// Overrides setValue to enforce only 0 or 1.
class FlagRegister : public Register {
private:
    char name[3];  // e.g. "CF" + null terminator = 3 chars

public:
    // Author: Muhammad Muhyideen
    // Constructor: takes flag name string (e.g. "CF").
    FlagRegister(const char* flagName) {
        int i = 0;
        while (flagName[i] != '\0' && i < 2) {
            name[i] = flagName[i];
            i++;
        }
        name[i] = '\0';
    }

    // Author: Muhammad Muhyideen
    // Default constructor: sets name to "F".
    FlagRegister() {
        name[0] = 'F'; name[1] = '\0';
    }

    // Author: Muhammad Muhyideen
    // Overrides setValue: flags only store 0 or 1, never other values.
    void setValue(int v) override {
        if (v != 0) {
            Register::setValue(1);
        } else {
            Register::setValue(0);
        }
    }

    // Author: Muhammad Muhyideen
    // Convenience setter using bool (true = 1, false = 0).
    void setFlag(bool state) {
        setValue(state ? 1 : 0);
    }

    // Author: Muhammad Muhyideen
    // Returns flag state as bool (true if 1, false if 0).
    bool getFlag() const {
        return getValue() != 0;
    }

    // Author: Muhammad Muhyideen
    // Resets flag to 0.
    void reset() override {
        setValue(0);
    }

    // Author: Muhammad Muhyideen
    // Returns flag name (e.g. "CF", "ZF").
    const char* getName() const override {
        return name;
    }
};


// ============================================================
//  SECTION 5: Memory Class (Member 2 Implementation)
// ============================================================

// Author: Shaarvin
// Represents a 256-byte RAM system for the 8-bit Virtual Machine.
class Memory {
private:
    static const int RAM_SIZE = 256;
    signed char ram[RAM_SIZE];

public:
    // Author: Shaarvin
    // Constructor: Zeroes out all RAM addresses.
    Memory() {
        for (int i = 0; i < RAM_SIZE; i++) {
            ram[i] = 0;
        }
    }

    // Author: Shaarvin
    // Reads from memory address with boundary safety.
    signed char read(int address) const {
        if (address < 0 || address >= RAM_SIZE) {
            cout << "[Memory ERROR] Read access violation at address " << address << "." << endl;
            return 0;
        }
        return ram[address];
    }

    // Author: Shaarvin
    // Writes to memory address with boundary safety.
    void write(int address, signed char value) {
        if (address < 0 || address >= RAM_SIZE) {
            cout << "[Memory ERROR] Write access violation at address " << address << "." << endl;
            return;
        }
        ram[address] = value;
    }

    // Author: Shaarvin
    // Resets entire memory space.
    void reset() {
        for (int i = 0; i < RAM_SIZE; i++) ram[i] = 0;
    }
};


// ============================================================
//  SECTION 6: CPU Class (Member 2 Implementation)
// ============================================================

// Author: Shaarvin
// Core Central Processing Unit that manages registers, stack, memory, and pointers.
class CPU {
public:
    GeneralRegister R[8];         // Hardware collection of R0 - R7
    FlagRegister CF, OF, UF, ZF;   // Status flags
    MyStack stack;                // Hardware call/data stack
    Memory memory;                // Integrated execution memory
    int PC;                       // Program Counter tracking code lines

    // Author: Shaarvin
    // Constructor: Explicitly names and initializes registers and system states.
    CPU() : R{{"R0"}, {"R1"}, {"R2"}, {"R3"}, {"R4"}, {"R5"}, {"R6"}, {"R7"}},
            CF("CF"), OF("OF"), UF("UF"), ZF("ZF") {
        PC = 0;
    }

    // Author: Shaarvin
    // Performs a full system hardware state reset.
    void resetHardware() {
        PC = 0;
        for (int i = 0; i < 8; i++) R[i].reset();
        CF.reset();
        OF.reset();
        UF.reset();
        ZF.reset();
        stack.reset();
        memory.reset();
    }

    // Author: Shaarvin
    // Output Formatting: Generates a complete status block snapshot of the machine state.
    void printStateDump(const string& currentInstruction) const {
        cout << "\n========================================================================\n";
        cout << " STEP EXECUTED: " << (currentInstruction.empty() ? "[HALT/START]" : currentInstruction) << "\n";
        cout << "========================================================================\n";
        
        // Pointers
        cout << " System Pointers ->  PC: " << PC 
             << " | SI (Stack Index): " << stack.getStackIndex() << "\n\n";

        // Registers
        cout << " Registers       ->  ";
        for (int i = 0; i < 8; i++) {
            cout << R[i].getName() << ": " << (int)R[i].getValue() << "    ";
            if (i == 3) cout << "\n                     ";
        }
        cout << "\n\n";

        // Flags
        cout << " Status Flags    ->  CF: " << CF.getFlag() 
             << " | OF: " << OF.getFlag() 
             << " | UF: " << UF.getFlag() 
             << " | ZF: " << ZF.getFlag() << "\n\n";

        // Stack Dump Matrix
        cout << " Stack Matrix    ->  [Slot]  ";
        for (int i = 0; i < 8; i++) cout << "[" << i << "]  ";
        cout << "\n                     [Val]   ";
        for (int i = 0; i < 8; i++) cout << " " << (int)stack.getAt(i) << "   ";
        cout << "\n========================================================================\n";
    }
};


// ============================================================
//  SECTION 7: Runner Engine Class (Member 2 Implementation)
// ============================================================

// Author: Shaarvin
// Component handling lexical isolation of instructions and runtime orchestration.
class Runner {
private:
    MyVector<string> instructionRegistry; // Holds lines of read code

    // Author: Shaarvin
    // Helper processing tool to strip spaces and commas, isolating words.
    string cleanToken(const string& s) {
        string clean = "";
        for (char c : s) {
            if (c != ',' && c != ' ' && c != '\t' && c != '\r' && c != '\n') {
                clean += c;
            }
        }
        return clean;
    }

public:
    // Author: Shaarvin
    // Manually loads an assembly code block string collection into execution vectors.
    void loadProgramLine(const string& asmLine) {
        if (!asmLine.empty()) {
            instructionRegistry.push_back(asmLine);
        }
    }

    // Author: Shaarvin
    // Lexical analysis loop parsing strings into manageable Opcode and Operand tokens.
    void parseInstruction(const string& rawLine, string& opcode, string& op1, string& op2) {
        opcode = op1 = op2 = "";
        int i = 0;
        int n = rawLine.length();

        // Skip leading whitespace
        while (i < n && (rawLine[i] == ' ' || rawLine[i] == '\t')) i++;

        // Read Opcode
        while (i < n && rawLine[i] != ' ' && rawLine[i] != '\t' && rawLine[i] != ',') {
            opcode += rawLine[i];
            i++;
        }

        // Find Operand 1
        while (i < n && (rawLine[i] == ' ' || rawLine[i] == '\t' || rawLine[i] == ',')) i++;
        while (i < n && rawLine[i] != ' ' && rawLine[i] != '\t' && rawLine[i] != ',') {
            op1 += rawLine[i];
            i++;
        }

        // Find Operand 2
        while (i < n && (rawLine[i] == ' ' || rawLine[i] == '\t' || rawLine[i] == ',')) i++;
        while (i < n && rawLine[i] != ' ' && rawLine[i] != '\t' && rawLine[i] != ',') {
            op2 += rawLine[i];
            i++;
        }

        opcode = cleanToken(opcode);
        op1 = cleanToken(op1);
        op2 = cleanToken(op2);
    }

    // Author: Shaarvin
    // Central Runtime Fetch-Decode Loop orchestrating with underlying project logic blocks.
    void runSimulation(CPU& cpu) {
        cout << "\n>>> CRANKING VIRTUAL MACHINE ENGINE CORRIDORS... <<<\n";
        cpu.printStateDump("SYSTEM BOOT INITIALIZED");

        while (cpu.PC < instructionRegistry.size()) {
            string currentLine = instructionRegistry.get(cpu.PC);
            string opcode, op1, op2;
            
            parseInstruction(currentLine, opcode, op1, op2);

            // Increment program counter ahead of code execution
            cpu.PC++;

            // Mock Execution hooks - these will connect directly to Member 3 and Member 4's classes
            if (opcode == "MOV" || opcode == "mov") {
                // Member 3 will complete the calculation logic here.
                // Simulating execution effect on hardware for proof of architecture:
                if (!op1.empty() && op1[0] == 'R') {
                    int regIdx = op1[1] - '0';
                    if (regIdx >= 0 && regIdx < 8) {
                        cpu.R[regIdx].setValue(atoi(op2.c_str()));
                    }
                }
            } 
            else if (opcode == "PUSH" || opcode == "push") {
                // Member 4 execution link simulation:
                cpu.stack.push(atoi(op1.c_str()));
            }

            // Print the resulting hardware profile dump
            cpu.printStateDump(currentLine);
        }
        cout << "\n>>> SIMULATION END REACHED SAFELY <<<\n";
    }

    // Author: Shaarvin
    void clearProgram() {
        instructionRegistry.clear();
    }
};


// ============================================================
//  SECTION 8: Main Driver Verification Loop
// ============================================================

int main() {
    cout << "====================================================" << endl;
    cout << "   Combined Architecture Verification Driver"        << endl;
    cout << "====================================================" << endl;

    // 1. Initialize CPU and Runner units (Member 2 instances)
    CPU virtualCPU;
    Runner structuralRunner;

    // 2. Load basic validation script to test architecture parsing & structural logic
    structuralRunner.loadProgramLine("MOV R0, 45");
    structuralRunner.loadProgramLine("MOV R4, -120");
    structuralRunner.loadProgramLine("PUSH 77");
    structuralRunner.loadProgramLine("MOV R7, 127");

    // 3. Kick off runtime cycle process
    structuralRunner.runSimulation(virtualCPU);

    return 0;
}
