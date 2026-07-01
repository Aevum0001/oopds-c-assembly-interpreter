// ============================================================
// CCP6124 Object-oriented Programming and Data Structures
// Trimester 2610 - Virtual Machine Project
// FILE: TT01_G01.cpp
// DESCRIPTION: Custom Data Structures + Register Class Hierarchy
// ============================================================

#include <iostream>
#include <string>   // Required for string tests to compile
#include <cstdlib>  // Required for exit(1) on stack crash

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
//  SECTION 5: Quick Test / Demo
// ============================================================

// Author: Muhammad Muhyideen
// Prints a separator line for test output readability.
void printSeparator(const char* title) {
    cout << "\n==============================" << endl;
    cout << "  TEST: " << title << endl;
    cout << "==============================" << endl;
}

// Author: Roshan
// Tests MyVector with ASM instruction strings.
void testMyVectorStrings() {
    printSeparator("MyVector<string> (ASM lines)");
    MyVector<string> lines;
    lines.push_back("MOV R1, 5");
    lines.push_back("ADD R1, R2");
    cout << "Stored " << lines.size() << " instructions:" << endl;
    for (int i = 0; i < lines.size(); i++) {
        cout << "  [" << i << "] " << lines.get(i) << endl;
    }
}

// Author: Muhammad Muhyideen
// Tests MyStack push, pop, and peek operations.
void testMyStack() {
    printSeparator("MyStack");
    MyStack s;
    s.push(10);
    s.push(20);
    cout << "Peek: " << (int)s.peek() << endl;
    cout << "Pop: "  << (int)s.pop()  << endl;
    cout << "Size after pop: " << s.size() << endl;
}

// Author: Muhammad Muhyideen
// Tests Register hierarchy: clamping and flag enforcement.
void testRegisters() {
    printSeparator("Register Hierarchy");
    GeneralRegister r0("R0");
    r0.setValue(200);  // should clamp to 127
    cout << r0.getName() << " after setValue(200) [clamped]: "
         << (int)r0.getValue() << endl;

    FlagRegister cf("CF");
    cf.setValue(99);   // should set to 1
    cout << cf.getName() << " after setValue(99): "
         << (int)cf.getValue() << endl;
}

// Author: Muhammad Muhyideen
// Entry point: runs all unit tests.
int main() {
    cout << "========================================" << endl;
    cout << " Member 1 Foundation - Unit Tests"       << endl;
    cout << "========================================" << endl;

    testMyVectorStrings();
    testMyStack();
    testRegisters();

    cout << "\n[All tests complete]" << endl;
    return 0;
}
