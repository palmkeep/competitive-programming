/*
 *  Author:      André Palmborg
 * 
 *  Course:      TDDD95
 *    Task:      1.6: polymul2
 */

#include <stdio.h>
#include <stdlib.h>

#include <stdexcept>

#include <complex>
typedef std::complex<long double> C;
const double PI = 3.141592653589793238460;

#include <valarray>
using std::valarray;
typedef std::valarray<C> Carray;



/* FFT_h
 *
 * Performs the inverse and regular Fast Fourier Transform using
 * the Cooley-Tukey algorithm on a valarray of samples.
 *
 * Input
 * Carray& samples  : Valarray of complex<long double> samples.
 * size_t N         : The size of the $samples valarray.
 * bool inv         : Boolean telling FFT_h if it should compute the inverse FFT.
 *
 * Returns void     : Transformed values are placed in the referenced $samples array
 */
void FFT_h(Carray& samples, const size_t N, const bool inv)
{
    double f = (inv) ? 2 : -2;

    if (N != 1)
    {
        Carray even = samples[std::slice(0, N/2, 2)];
        Carray odd  = samples[std::slice(1, N/2, 2)];

        FFT_h(even,   N/2, inv);
        FFT_h(odd,    N/2, inv);
        
        for (size_t i{0}; i < N/2; i++)
        {
            C t = even[i];
            C exp = std::polar(1.0L, (long double)f * PI * i / N) * odd[i];
            samples[i]          = t + exp;
            samples[i + N/2]    = t - exp;
        }
    }
}
// Maps regular or inverse FFT calls to FFT_h
void FFT(Carray& samples)   { FFT_h(samples, samples.size(), false); }
void iFFT(Carray& samples)  { FFT_h(samples, samples.size(), true); }


/* pMultiplication
 * Pointwise multiplication of two Complex valarrays
 * 
 * Side-effects : Will throw an exception if the given arrays are not the exact same size.
 *
 * Returns Carray P: New Carray with same length as A and B
 * */
Carray pointMultiplication(Carray& A, Carray& B)
{
    if (A.size() != B.size()) {
        throw std::invalid_argument("Pointwise array multiplication with differing array length");
    }

    Carray P;
    P.resize(A.size());
    for (size_t i{0}; i < A.size(); i++) {
        P[i] = A[i] * B[i];
    }

    return P;
}


/* inputArray
 *
 * Takes one polynomial from input and places it, in coefficient form, in
 * a referenced array.
 *
 * Side-effect: Removes input described below incl. last newline from stdin.
 * stdin    :   ^deg$
 *              ^c_0 c_1 ... c_deg$
 */
int inputArray(Carray& a)
{
    size_t a_size;
    scanf("%lu", &a_size);
    a.resize( (a_size+1) );

    int z = 1;
    long int n;
    for (size_t i{0}; i <= a_size; i++)
    {
        scanf("%lu ", &n);
        if (n != 0) { z = 0; }

        a[i] = (C)n;
    }
    return z;
}


/* takeInput
 *
 * Takes two polynomials from input and places them, in coefficient form, in two referenced arrays.
 * 
 * Returns 1 if one or more of the arrays are equal to 0
 * Returns 0 otherwise
 */
int takeInput(Carray& a, Carray& b)
{
    if (inputArray(a) == 1 || inputArray(b) == 1) {
        return 1;
    } else {
        return 0;
    }
}


/* polynomialMultiplication
 *
 * Polynomial multiplication using the Fast Fourier Transform.
 *
 * a * b = iFFT( FFT(b) .* FFT(b) )
 * Where * is normal polynomial multiplication and .* is pointwise multiplication.
 *
 * Side-effects:    Will attempt to read two polynomials from stdin.
 *                  When computed the result will be sent to stdout.
 */
void polynomialMultiplication()
{
    Carray a;
    Carray b;
    int z = takeInput(a, b);
    
    // Handles cases where one or more of the arrays are equal to zero
    if (z == 1) { puts("0\n0"); return; }

    // Make e the smallest power of 2 larger than max(a.size(), b.size()).
    size_t s = (a.size() < b.size()) ? b.size() : a.size();
    size_t e = 1;
    while (e < s) { e<<=1; }

    // Create new zero-padded arrays of length e*2 from values in a and b
    Carray A;
    A.resize(e*2);
    for (size_t i{0}; i < a.size(); i++) {A[i] = a[i];}

    Carray B;
    B.resize(e*2);
    for (size_t i{0}; i < b.size(); i++) {B[i] = b[i];}

    // Multiply polynomials
    FFT(A);
    FFT(B);
    Carray P = pointMultiplication(A, B);
    iFFT(P);
  
    // Get the degree of the resulting polynomial.
    size_t max_i{0};
    for (size_t i{0}; i < P.size(); i++) {
        if ( 1e-1 < std::abs(P[i].real()) ) {
            max_i = i+1;
        }
    }
    printf("%lu\n", max_i-1);

    // Print rounded coefficients of the resulting polynomial.
    long int f, c;
    long double v;
    for (size_t i{0}; i < max_i; i++)
    {
        f = (long int)std::floor(P[i].real()/P.size());
        c = f + 1;

        v = P[i].real()/P.size();
        if (v - (long double)f < (long double)c - v) {
            printf("%ld ", f);
        } else {
            printf("%ld ", c);
        }
    }
    fputs("\n", stdout);
}


/* Repeats per test case to solve polymul1 and polymul2 */
int main()
{
    int z;
    scanf("%d ", &z);
    for (int i{0}; i < z; i++) { polynomialMultiplication(); }
}

