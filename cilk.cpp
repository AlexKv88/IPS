#include<sstream>
#include<iomanip>
#include<iostream>
#include <math.h>
#include<windows.h>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>

double Integrate_p(const int a, const int b, const int n) // parallel
{ 
	double result;
	const double h = (double)(b - a) / n;
	cilk::reducer_opadd <double> sum;

	sum.set_value(0);

	cilk_for(long int i = 0; i < n - 1; ++i)
	{
		sum += 5 / sqrt(8 - 4 * (a + (i + 0.5)*h)*(a + (i + 0.5)*h));
	}

	return result = h*sum.get_value();

	
}

double Integrate_s(const int a, const int b, const int n) // serial
{
	double result,sum;
	const double h = (double)(b - a) / n;

	for(long int i = 0; i < n - 1; ++i)
	{
		sum += 5 / sqrt(8 - 4 * (a + (i + 0.5)*h)*(a + (i + 0.5)*h));
	}

	return result = h*sum;

}
int main()
{
	double result;
	 const int a = -1;
	 const int b = 1;
	 const int n = 1000000;
	DWORD starttime, elapsedtime;
	starttime = GetTickCount();

	// serial and parallel functions

	result = Integrate_s(a, b, n);
	//result = Integrate_s(a, b, n);

	elapsedtime = GetTickCount() - starttime;
	printf("Integral value: %lf", result);
	std::cout << std::endl << "Time Elapsed: " << elapsedtime << " ms" << std::endl;
	return 0;

}