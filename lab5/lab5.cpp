#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

class fraction{
    public:
        int n, d;

        int gcd(int a, int b); // function to get the gcd of a and b
        fraction(int n=0, int d=1): n(n/gcd(abs(n), abs(d))), d(d/gcd(abs(n), abs(d))) {} 
        // Ctor with two parameters, notice that the gcd should be the absolute value of a and b
        fraction(const fraction& f){};  // copy ctor
        
        double toDouble(){ return 1.0*n/d; }  // Typecast to double
        string toString(); // to string
};

int fraction::gcd(int a, int b){
    if(!b) return a;
    else return gcd(b, a%b); // recursion
}

string fraction::toString(){ 
    string str;
    if(n%d) str = to_string(n) + "/" + to_string(d); 
    else str = to_string(n/d); // if it is an integer, return as integer
    return str; 
}

// Arithmetical operators of fractions: + - * /
fraction operator+(const fraction &a, const fraction &b){
    fraction res(a.n*b.d+b.n*a.d, a.d*b.d);
    return res;
}

fraction operator-(const fraction &a, const fraction &b){
    fraction res(a.n*b.d-b.n*a.d, a.d*b.d);
    return res;
}

fraction operator*(const fraction &a, const fraction &b){
    fraction res(a.n*b.n, a.d*b.d);
    return res;
}

fraction operator/(const fraction &a, const fraction &b){
    fraction res(a.n*b.d, b.n*a.d);
    return res;
}

// Relational operators of fraction: < <= == != >= >
bool operator<(const fraction &a, const fraction &b){
    fraction c = a-b;  // judge by the result of a-b
    if(c.n<0) return true;  // The result is the same as the numerator symbol bit
    else return false;
}

bool operator<=(const fraction &a, const fraction &b){
    fraction c = a-b;
    if(c.n<=0) return true;
    else return false;
}

bool operator==(const fraction &a, const fraction &b){
    fraction c = a-b;
    if(c.n==0) return true;
    else return false;
}

bool operator>=(const fraction &a, const fraction &b){
    fraction c = a-b;
    if(c.n>=0) return true;
    else return false;
}

bool operator>(const fraction &a, const fraction &b){
    fraction c = a-b;
    if(c.n>0) return true;
    else return false;
}

// Inserter and extractor for streams
ostream& operator<<(ostream& out, const fraction &f){
    string str;
    if(f.n%f.d) str = to_string(f.n) + "/" + to_string(f.d); // output as a string
    else str = to_string(f.n/f.d);  // if is an integer 
    out << str;
    return out;
}

istream& operator>>(istream& in, fraction &f){
    char c;
    int n, d;
    in >> f.n >> c >> f.d; // jump the '/'
    return in;
}

// funtion to change the finite decimal string into fraction
fraction toFrac(string decimal){
    int isNeg = 0;
    if(decimal[0]=='-') isNeg = 1; // if is negative
    int frac = decimal.length() - decimal.find('.') - 1;
    int count = 1;
    if(frac<(decimal.length()-isNeg)) // the multiplier
        count = pow(10, frac);
    return fraction(stod(decimal)*count, count);
}

int main(){
    cout << "Input fraction1: ";
    fraction f;
    cin >> f;  // input with the format "numerator/denominator" directly
    cout << "Fraction1: ";
    cout << f << endl; // output with the format "numerator/denominator" directly
    cout << "Input fraction2: ";
    fraction g;
    cin >> g;
    cout << "Fraction2: ";
    cout << g << endl;

    // Arithmetical operators: + - * /
    fraction k = f+g;
    cout << "Result of '+' is: ";
    cout << k << endl;
    k = f-g;
    cout << "Result of '-' is: ";
    cout << k << endl;
    k = f*g;
    cout << "Result of '*' is: ";
    cout << k << endl;
    k = f/g;
    cout << "Result of '/' is: ";
    cout << k << endl;

    // Relational operators: < <= == != >= >
    cout << "Result of '<' is: " << (f<g) << endl;
    cout << "Result of '<=' is: " << (f<=g) << endl;
    cout << "Result of '==' is: " << (f==g) << endl;
    cout << "Result of '>=' is: " << (f>=g) << endl;
    cout << "Result of '>' is: " << (f>g) << endl;

    cout << "Result of typecast to double of f1 is: " << f.toDouble() << endl; // Typecast to double
    cout << "Result of typecast to string of f1 is: " << "\"" <<f.toString() << "\"" << endl; // to string

    // Conversion from a finite decimal string
    cout << "Input a finite decimal string: ";
    string dec;
    cin >> dec;
    fraction p = toFrac(dec);
    cout << "The faction is: " << p;
}