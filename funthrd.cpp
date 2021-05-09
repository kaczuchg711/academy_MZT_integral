//////////////////////////////////////////////////////////////////////////////////
//   funthrd.cpp
//   thread function implementations

#include "stdafx.h"
#include <iostream>
#include "timethrd.h"

using namespace std;

DWORD WINAPI ThreadFunc1(LPVOID lpParam ) 
{
	THREAD_DATA *ptrDat = (THREAD_DATA *)(lpParam);

	CThreadTime *thrd_timer = ptrDat->thrd_timer;
	thrd_timer->begin();
	
	ptrDat->ret = 0;
	//pobrac dane, przekazywane potokowi
	//.....
	int local_ndiv = ptrDat->ndiv/ ptrDat->np;
	int ip = ptrDat->ip;
	double dx = ptrDat->dx;
	double (*p_fun)(double x, double b, double c);
	p_fun = ptrDat->p_fun;
	double a = ptrDat->a;
	double b = ptrDat->b;
	double c = ptrDat->c;
	double dxd2 = dx / 2;

	int i = local_ndiv * ip;
	double x_b = i * dx,  //Wspolrzedna x poczatku odcinku dx 
		   x_e,  //Wspolrzedna x konca odcinku dx 
		   f_b,  //wartosc funkcji podintegralnej na poczatku odcinku dx  
		   f_e,  //wartosc funkcji podintegralnej na koncu odcinku dx  
		   s;    //suma = suma + (f_b+f_e)*dx/2 - metoda trapezu

	s = 0.0;

	//napisac kod calkowania numerycznego metoda trapezow
	//printf("Hej jestem watek %d i robie od %d do %d \n", ptrDat->ip, local_ndiv * ip, local_ndiv * ip + local_ndiv);
	for (; i < local_ndiv * ip + local_ndiv; i++)
	{
	//	if (ip == 0)
		//	printf("%d\n",i);
		//ob
		f_b = p_fun(x_b, b, c);
		x_e = (i + 1.) * dx;
		f_e = p_fun(x_e, b, c);
		s += (f_b + f_e) * dxd2;
		x_b = x_e;
	}
	
	ptrDat->s = s;
	printf("Hej jestem watek %d moje obliczone pole %f\n", ptrDat->ip, ptrDat->s);

	thrd_timer->getelapstime();
	ptrDat->ret = 0;
	
	return 0; 
}