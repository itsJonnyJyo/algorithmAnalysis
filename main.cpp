/*
**Name: Jonathan Jensen
**SSID: G03567847
**CRN: 16692
**Assignment: Algorithm Analysis Application
**/



#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

double TbyT(unsigned int degree, double coefficients[], double xValue);
double horner(unsigned int degree, double coefficients[], double xValue);

int main(){
	unsigned int degree = 5;//highest order of polynomial
	double xValue = -10;
	// coefficients in reverse order or...
	// (ascending order of corresponding degree)
	double coefficients[6] = {-1, 3, 5, -7, 11, 13};
	int counter = 0;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	
	t1 = high_resolution_clock::now();
	/*
	** evaluate for values of x; -10<=x<=10; at least 10^4 values;
	** x begins at -10; increments by [20/(10^4)]=0.002 until 10.
	** The measured time COULD be more accurate if I accounted for
	** the time taken to increment xValue and counter but the impact
	** of those calculations will be the same for both algorithms, 
	** therefore we still get a clear picture of which is most time 
	** efficient.
	*/
	while (xValue <= 10){
		TbyT(degree, coefficients, xValue);	
		xValue+= 0.002;
		counter++;
	}	
	t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "Term-by-Term averaged " << time_span.count()/counter << " seconds.";
	cout << endl;
		
	counter = 0;//reset counter
	xValue = -10;//reset xValue
	
	t1 = high_resolution_clock::now();
	/*
	** evaluate for values of x; -10<=x<=10; at least 10^4 values;
	** x begins at -10; increments by [20/(10^4)]=0.002 until 10.
	*/
	while (xValue <= 10){
		horner(degree, coefficients, xValue);	
		xValue+= 0.002;
		counter++;
	}	
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "Horner Rule averaged " << time_span.count()/counter << " seconds.";
	cout << endl;

	return 0;
}

double TbyT(unsigned int degree, double coefficients[], double xValue){
	double polyVal = coefficients[0];
	double term;

	for (int i = 1; i <= degree; i++){
		term = coefficients[i];
		for(int j = 1; j <= i; j++){
			term = term * xValue;
		}		
		polyVal += term;
	}
	return polyVal;
}

double horner(unsigned int degree, double coefficients[], double xValue){
	double polyVal = coefficients[degree];
	
	for (int i = 1; i <= degree; i++){
		polyVal = polyVal * xValue + coefficients[degree - i];
	}
	return polyVal;
}
