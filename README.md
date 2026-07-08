# Custom Language Compiler

A compiler front end for a custom statically typed programming language implemented in **C++**. The project includes lexical analysis, parsing, semantic analysis, and an AST-based interpreter.

## Features

### Lexical Analysis

* Tokenizes identifiers, keywords, integer literals, operators, and delimiters.
* Supports keywords such as `int`, `bool`, `if`, `else`, and `while`.

### Parsing

* Recursive Descent Parser
* Constructs an Abstract Syntax Tree (AST)
* Supports:

  * Variable declarations
  * Variable assignments
  * Arithmetic expressions
  * Relational expressions
  * Equality expressions
  * Logical expressions
  * Unary operators
  * Block statements
  * `if-else`
  * `while`

### Semantic Analysis

* Symbol table construction
* Lexical scope management
* Variable shadowing
* Redeclaration detection
* Undefined variable detection
* Uninitialized variable detection
* Static type checking
* Type checking for:

  * Declarations
  * Assignments
  * Unary operators
  * Binary operators
  * Control-flow conditions (`if` and `while`)

### Interpreter

* AST-based execution
* Variable declaration and assignment
* Expression evaluation
* Conditional execution
* Loop execution
* Runtime variable management

---

## Compiler Architecture

```
Source Code
     │
     ▼
+------------+
|   Lexer    |
+------------+
      │
      ▼
+------------+
|   Parser   |
+------------+
      │
      ▼
+------------+
|    AST     |
+------------+
      │
      ├─────────────────────┐
      ▼                     ▼
+------------+      +------------------+
| Interpreter|      | Semantic Analyzer|
+------------+      +------------------+
```

---

## Project Structure

```
Custom-Language-Compiler
│
├── Ast/              # AST node definitions
├── Interpreter/      # AST interpreter
├── Lexer/            # Lexical analyzer
├── Parser/           # Recursive descent parser
├── Semantic/         # Symbol table, scope handling and type checking
├── Utils/            # Common utilities
└── main.cpp          # Driver program
```

---

## Sample Program

```c
int x = 10;
int y = 20;

bool flag = x < y;

if (flag) {
    x = x + y;
}

while (x > 0) {
    x = x - 5;
}
```

---

## Semantic Checks Performed

* Redeclaration of variables
* Use of undefined variables
* Use of uninitialized variables
* Scope resolution using lexical scoping
* Variable shadowing
* Type checking for expressions
* Type compatibility in declarations
* Type compatibility in assignments
* Boolean condition validation for `if` and `while`

---

## Technologies Used

* C++
* Object-Oriented Programming
* Recursive Descent Parsing
* Abstract Syntax Tree (AST)
* Symbol Tables
* Semantic Analysis
* Static Type Checking
* Interpreter Design

---

## Future Improvements

* Functions and function calls
* Arrays
* String data type
* `for` loops
* Code generation
* Intermediate Representation (IR)
* Optimizations
* Improved error reporting

---

## Author

**Soumil Soni**

If you find this project interesting, feel free to star the repository.
