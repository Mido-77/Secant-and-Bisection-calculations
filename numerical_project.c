//Mohamed Tarek Essam - 232004026
// Numerical Methods

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tinyexpr.h" // For parsing and evaluating user-defined math functions
#include "tinyexpr.c"

#define MAX_ITER 100
#define MAX_FUNC_LEN 100

// Helper function to clear the input buffer (useful after scanf)
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Prompt user for function and store it in a string
void getFunction(char *func) {
    printf("Enter the function f(x) = 0 :\n");
    fgets(func, MAX_FUNC_LEN, stdin);
    func[strcspn(func, "\n")] = 0; // remove newline character
}

// Evaluates the function at a given x using TinyExpr
double evalFunction(const char *func, double x) {
    te_variable vars[] = { {"x", &x} };
    int err;
    te_expr *expr = te_compile(func, vars, 1, &err);
    if (expr) {
        double result = te_eval(expr);
        te_free(expr);
        return result;
    } else {
        printf("Failed to parse function at position %d\n", err);
        exit(1);
    }
}

// Implements the Secant method
void secantMethod() {
    char func[MAX_FUNC_LEN];
    double x0, x1, x2;
    int i, iter;

    getFunction(func); // Get function from user

    while (1) { // [Added]: loop until valid input
        printf("Enter x0: ");
        if (scanf("%lf", &x0) != 1) { 
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        printf("Enter x1: ");
        if (scanf("%lf", &x1) != 1) { 
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        double fx0 = evalFunction(func, x0);
        double fx1 = evalFunction(func, x1);

        if (fabs(fx1 - fx0) < 1e-9) {
            printf("Bad initial guesses: f(x0) and f(x1) are too close. Choose different values.\n");
        } else {
            break; // Valid input
        }
    }

    printf("Enter number of iterations: ");
    if (scanf("%d", &iter) != 1 || iter <= 0) {
        printf("Invalid number of iterations. Exiting.\n");
        exit(1);
    }
    clearBuffer();

    // Iteratively apply the Secant formula
    for (i = 0; i < iter; i++) {
        double fx0 = evalFunction(func, x0);
        double fx1 = evalFunction(func, x1);

        if (fabs(fx1 - fx0) < 1e-9) {
            printf("Division by zero (or very close) in secant formula. Stopping.\n");
            break;
        }

        x2 = x1 - (fx1 * (x1 - x0)) / (fx1 - fx0);

        // Print detailed steps
        printf("\n--- Iteration %d ---\n", i + 1);
        printf("x0 = %.4lf, f(x0) = %.4lf\n", x0, fx0);
        printf("x1 = %.4lf, f(x1) = %.4lf\n", x1, fx1);
        printf("x2 = %.4lf\n", x2);

        x0 = x1;
        x1 = x2;
    }

    printf("\nFinal approximation: %.4lf\n", x2);
}

// Implements the Bisection method
void bisectionMethod() {
    char func[MAX_FUNC_LEN];
    double a, b, xm, fa, fb, fxm, prev_xm = 0.0, error = 0.0;
    int iter, calcMaxIter, i;

    getFunction(func); // Get function from user

    // [Added] Repeat input until a correct interval is given
    while (1) {
        printf("Enter point a: ");
        if (scanf("%lf", &a) != 1) { 
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        printf("Enter point b: ");
        if (scanf("%lf", &b) != 1) { 
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        fa = evalFunction(func, a);
        fb = evalFunction(func, b);

        if (fa * fb >= 0) {
            printf("f(a) and f(b) must have opposite signs (i.e., the root must be between a and b).\n");
            printf("Please enter a new interval.\n");
        } else {
            break; // Correct input
        }
    }

    printf("Enter error tolerance (0 if not used): ");
    if (scanf("%lf", &error) != 1 || error < 0) {
        printf("Invalid error tolerance. Exiting.\n");
        exit(1);
    }
    clearBuffer();

    printf("Do you want to calculate max iteration based on error? (1 = Yes, 0 = No): ");
    if (scanf("%d", &calcMaxIter) != 1) {
        printf("Invalid input. Exiting.\n");
        exit(1);
    }
    clearBuffer();

    if (calcMaxIter && error > 0) {
        iter = (int)((log(fabs(b - a)) - log(error)) / log(2)) + 1;
        printf("Calculated max iterations: %d\n", iter);
    } else {
        printf("Enter number of iterations: ");
        if (scanf("%d", &iter) != 1 || iter <= 0) {
            printf("Invalid number of iterations. Exiting.\n");
            exit(1);
        }
        clearBuffer();
    }

    // Iteratively apply the Bisection method
    for (i = 0; i < iter; i++) {
        xm = (a + b) / 2;
        fxm = evalFunction(func, xm);

        printf("\n--- Iteration %d ---\n", i + 1);
        printf("a = %.4lf, f(a) = %.4lf\n", a, fa);
        printf("b = %.4lf, f(b) = %.4lf\n", b, fb);
        printf("xm = (a + b) / 2 = (%.4lf + %.4lf) / 2 = %.4lf\n", a, b, xm);
        printf("f(xm) = %.4lf\n", fxm);

        if (fxm == 0 || (i > 0 && fabs((xm - prev_xm) / xm) <= error && fabs(xm) > 1e-9)) {
            printf("Stopping criteria met.\n");
            break;
        }

        if (fa * fxm < 0) {
            b = xm;
            fb = fxm;
        } else {
            a = xm;
            fa = fxm;
        }

        prev_xm = xm;
    }

    printf("\nFinal approximation: %.4lf\n", xm);
}

// Entry point of the program
int main() {
    int choice;

    printf("Choose a method:\n1. Secant Method\n2. Bisection Method\nYour choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice.\n");
        return 1;
    }
    clearBuffer();

    switch (choice) {
        case 1:
            secantMethod();
            break;
        case 2:
            bisectionMethod();
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
