#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#define func2Zero 2/3.0
using namespace std;

vector<int> koefs;

double func(double x) {
    double result = 0;
    for (int i = 0; i < koefs.size() - 1; i++) {
        result += pow(x, koefs.size() - i - 1) * koefs[i];
    }
    result += koefs[koefs.size() - 1];
    return result;
}

double firstDerivative(double x, double deltaX = 0.0000001) {
    return (func(x + deltaX) - func(x)) / deltaX;
}

double secondDerivative(double x, double deltaX = 0.0000001) {
    double v1 = firstDerivative(x, deltaX);
    double v2 = firstDerivative(x + deltaX, deltaX);
    return (v2 - v1) / deltaX;
}


double halfMethod(double a, double b, double eps, int* pcounter) {
    while (fabs(a - b) > eps) {
        double temp = (b + a) / 2;
        if (func(a) * func(temp) > 0) {
            a = temp;
        }
        else if (func(a) * func(temp) < 0) {
            b = temp;
        }
        else {
            return temp;
        }
        (*pcounter)++;
    }
    return a;
}

double hordMethod(double a, double b, double eps, int* pcounter) {
    double prev;
    double sec = secondDerivative(b, eps);
    if (func(b) * secondDerivative(b, eps) < 0) {
        double temp = a;
        a = b;
        b = temp;
    }
    do {
        prev = a;
        a = a - (func(a) * (b - a)) / (func(b) - func(a));
        (*pcounter)++;
    } while (fabs(a - prev) > eps);
    return a;
}

void tabulation() {
    for (int i = 0; i < 50; i++) {
        std::cout << "=";
    }
    std::cout << "\n";
}


double newton(double a, double b, double eps, int* pcounter) {
    double prev = 0;
    if (func(a) * secondDerivative(b, eps) < 0) {
        double temp = a;
        a = b;
        b = temp;
    }
    do {
        prev = a;
        a = a - func(a) / firstDerivative(a, eps);
        (*pcounter)++;
    } while (abs(prev - a) > eps);
    return a;
}


int main()
{
    for (int i = 5; i >= 0; i--) {
        cout << "Enter a" << i << endl;
        int a;
        cin >> a;
        koefs.push_back(a);
    }
    
    double a = 0;
    double b = 0;
    double eps = 0;
    int counterHalf = 0;
    int counterHord = 0;
    int counterNewton = 0;
    do {
        cout << "Enter a left limit:\t";
        cin >> a;
        cout << "Enter a right limit:\t";
        cin >> b;
        if (func(a) * func(b) > 0) cout << "No roots" << endl;
        else break;
    } while (1);
    cout << "Enter precision value:\t";
    cin >> eps;

    tabulation();
    double resultHalf = halfMethod(a, b, eps, &counterHalf);
    double resultHord = hordMethod(a, b, eps, &counterHord);
    double resultNewton = newton(a, b, eps, &counterNewton);
    cout << "Half method:\t" << fixed << setprecision(10) << resultHalf << "\tIteration:\t" << counterHalf << endl;
    cout << "Hord method:\t" << fixed << setprecision(10) << resultHord << "\tIteration:\t" << counterHord << endl;
    cout << "Newton method:\t" << fixed << setprecision(10) << resultNewton << "\tIteration:\t" << counterNewton << endl;
    return 0;
}
