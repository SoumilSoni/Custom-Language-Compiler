# Custom Language Compiler

A compiler front end and AST-based interpreter for a custom statically typed programming language implemented in **C++**.

The project implements the major stages of a language-processing pipeline:

* Lexical analysis
* Recursive-descent parsing
* Abstract Syntax Tree (AST) construction
* Semantic analysis
* Static type checking
* AST-based interpretation
* Function execution and recursion

---

## Features

### Lexical Analysis

The lexer converts source code into a stream of tokens.

Supports:

* Identifiers
* Integer literals
* Keywords
* Arithmetic operators
* Relational operators
* Equality operators
* Logical operators
* Unary operators
* Parentheses and braces
* Commas and semicolons

Supported keywords include:

```text
int
bool
if
else
while
return
```

---

### Parsing

The parser is implemented using **recursive descent parsing** and constructs an Abstract Syntax Tree (AST).

The parser supports:

* Variable declarations
* Variable assignments
* Arithmetic expressions
* Relational expressions
* Equality expressions
* Logical expressions
* Unary operators
* Operator precedence and associativity
* Nested block statements
* `if-else`
* `while`
* Function declarations
* Function parameters
* Function calls
* Multiple function arguments
* Return statements

---

### Semantic Analysis

The semantic analyzer performs static checks on the AST before interpretation.

It implements:

* Symbol table management
* Function table management
* Lexical scope management
* Variable shadowing
* Redeclaration detection
* Undefined variable detection
* Uninitialized variable detection
* Static type checking
* Function declaration validation
* Function parameter type checking
* Function return type checking
* Function-call argument count checking
* Function-call argument type checking
* `main()` function validation

Type checking is performed for:

* Variable declarations
* Assignments
* Unary operators
* Binary operators
* Arithmetic expressions
* Comparison expressions
* Logical expressions
* `if` conditions
* `while` conditions
* Function parameters
* Return statements
* Function calls

---

### Interpreter

The interpreter executes the generated AST directly.

It supports:

* Variable declaration and assignment
* Runtime variable management
* Expression evaluation
* Conditional execution
* Loop execution
* Function execution
* Parameter binding
* Return-value propagation
* Nested function calls
* Recursive function calls

---

## Function Execution

Functions are handled using a runtime function table that maps function names to their corresponding `FunctionNode`.

```text
Function Name → FunctionNode*
```

Each function invocation creates a separate **CallFrame** containing the runtime variables belonging to that invocation.

For example, recursive execution creates independent frames:

```text
factorial(5)
    │
    ├── CallFrame: n = 5
    │
    └── factorial(4)
            │
            ├── CallFrame: n = 4
            │
            └── factorial(3)
                    │
                    └── ...
```

The interpreter maintains a pointer to the current frame. When a function is called:

1. The arguments are evaluated in the caller's frame.
2. A new `CallFrame` is created.
3. Arguments are bound to the function parameters.
4. The new frame becomes the current frame.
5. The function body is executed.
6. A `return` statement propagates its value through nested blocks and control-flow statements.
7. The previous frame is restored.
8. The function's return value is passed back to the caller.

This provides isolated local variables and naturally supports nested and recursive function calls.

---

## Compiler Architecture

```text
                    Source Code
                        │
                        ▼
                 +--------------+
                 |    Lexer     |
                 +--------------+
                        │
                        ▼
                 +--------------+
                 |    Parser    |
                 +--------------+
                        │
                        ▼
                 +--------------+
                 |     AST      |
                 +--------------+
                        │
                        ▼
             +----------------------+
             | Semantic Analyzer    |
             +----------------------+
                        │
                  Valid AST
                        │
                        ▼
             +----------------------+
             |     Interpreter      |
             +----------------------+
                        │
                        ▼
                   Execution
```

The semantic analyzer validates the AST before it reaches the interpreter, preventing semantically invalid programs from being executed.

---

## Project Structure

```text
Custom-Language-Compiler
│
├── Ast/              # AST node definitions
│
├── Interpreter/      # AST interpreter and runtime
│   ├── CallFrame
│   ├── RuntimeValue
│   └── RuntimeFunctionTable
│
├── Lexer/            # Lexical analyzer
│
├── Parser/           # Recursive descent parser
│
├── Semantic/         # Semantic analyzer
│   ├── Symbol Table
│   ├── Function Table
│   └── Scope Management
│
├── Utils/            # Common utilities
│
└── main.cpp          # Driver program
```

---

## Sample Program

The language supports functions, control flow, and recursion.

```text
int add(int a, int b) {
    return a + b;
}

int sum(int n) {
    if (n == 0) {
        return 0;
    }

    return n + sum(n - 1);
}

int main() {
    int result = add(10, 20);

    return sum(10);
}
```

The example demonstrates:

* Function declarations
* Parameters
* Function calls
* Return statements
* Conditional execution
* Recursive function calls
* Local function frames

---

## Semantic Checks Performed

The semantic analyzer detects:

* Redeclaration of variables
* Redeclaration of functions
* Use of undefined variables
* Use of uninitialized variables
* Undefined function calls
* Invalid variable shadowing/redeclarations within a scope
* Scope resolution using lexical scoping
* Type mismatches in declarations
* Type mismatches in assignments
* Invalid unary operations
* Invalid binary operations
* Invalid control-flow conditions
* Function return-type mismatches
* Incorrect number of function arguments
* Incorrect function argument types
* Invalid `main()` declaration

---

## Technologies Used

* **C++**
* Object-Oriented Programming
* Recursive Descent Parsing
* Abstract Syntax Trees (AST)
* Symbol Tables
* Function Tables
* Lexical Scoping
* Semantic Analysis
* Static Type Checking
* Interpreter Design
* Runtime Call Frames

---

## Current Status

The compiler currently supports the complete pipeline:

```text
Source Code
    ↓
Lexical Analysis
    ↓
Parsing
    ↓
AST Construction
    ↓
Semantic Analysis
    ↓
AST Interpretation
```

The interpreter has been tested with:

* Arithmetic and logical expressions
* Conditional statements
* Loops
* Function calls
* Multiple function arguments
* Nested function calls
* Return statements inside control-flow blocks
* Recursive function calls
* Independent call frames for function invocations

---

## Future Improvements

Potential future extensions include:

* Arrays
* String data type
* `for` loops
* More built-in types
* Improved error reporting with source locations
* Intermediate Representation (IR)
* Code generation
* Compiler optimizations
* Additional runtime features
* Standard library support

---

## Author

**Soumil Soni**

If you find this project interesting, feel free to ⭐ the repository.
