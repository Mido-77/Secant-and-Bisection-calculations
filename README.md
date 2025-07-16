# 📐 Numerical Methods: Secant & Bisection Method in C

This project implements two fundamental **Numerical Methods** — the **Secant Method** and the **Bisection Method** — to find the roots of non-linear equations `f(x) = 0`, using a user-defined mathematical function. The project uses the **TinyExpr** library to parse and evaluate expressions at runtime.

---

## 🚀 Features

- 🔢 **User-defined function support** (e.g. `x^2 - 4`)
- 📉 Implements:
  - ✅ **Secant Method**
  - ✅ **Bisection Method**
- 🛡️ Input validation and error handling
- ✍️ Step-by-step iteration output
- 🧠 Optional automatic max iteration calculation for Bisection (based on error)
- ⚙️ Easy switch between methods from the main menu

---

## 📦 Dependencies

- [tinyexpr.h](https://github.com/codeplea/tinyexpr) – Lightweight math expression parser for C

Make sure `tinyexpr.h` and `tinyexpr.c` are included in the same directory.

---

## 🧠 Algorithms Used

### 1️⃣ Secant Method  
An iterative root-finding method that uses two initial guesses:

\[
x_{n+1} = x_n - f(x_n) \cdot \frac{x_n - x_{n-1}}{f(x_n) - f(x_{n-1})}
\]

- Requires: `x0`, `x1`, and number of iterations
- Stops on near-zero denominator

### 2️⃣ Bisection Method  
A reliable bracketing method using an interval `[a, b]` where `f(a)` and `f(b)` have opposite signs:

\[
x_m = \frac{a + b}{2}
\]

- Requires: `a`, `b`, error tolerance or max iterations
- Optional: calculates `max_iter = log2((b-a)/error)`

---


## 💻 How to Run

```bash
gcc -o num_methods main.c tinyexpr.c -lm
./num_methods

