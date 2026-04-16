# Math Quiz Game - C++ Console Application

A console-based math quiz game built in C++ that generates arithmetic questions based on user-selected difficulty levels and operation types.

This project focuses on **dynamic question generation, configurable game logic, and performance tracking**, simulating an interactive learning system.

---

## Features

- Configurable number of questions  
- Difficulty levels:
  - Easy (0–10)
  - Medium (10–50)
  - Hard (50–100)
  - Mixed  
- Operation types:
  - Addition
  - Subtraction
  - Multiplication
  - Division
  - Mixed  
- Real-time feedback on answers  
- Score tracking:
  - Correct answers
  - Wrong answers  
- Final result summary (Pass / Fail)  
- Continuous play option  

---

## Core Concepts Applied

- Enums (`enum`) for:
  - Difficulty levels  
  - Operation types  
- Structs (`struct`) for:
  - Game state  
  - Round data  
- Random number generation (`rand`)  
- Modular function design  
- Input validation techniques  
- Conditional logic for dynamic behavior  
- Basic UI feedback using console colors  

---

## How It Works

1. User selects:
   - Number of questions  
   - Difficulty level  
   - Operation type  
2. Program generates random questions accordingly  
3. User answers each question  
4. System evaluates answers and provides feedback  
5. Final summary displays performance and result  

---

## How to Run

### Compile:
```bash
g++ -std=c++11 main.cpp -o quiz
./quiz
