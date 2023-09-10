#include "Polynomial.h"
#include <cmath>
#include <iostream>

using namespace std;

//s
Polynomial::Polynomial()
{
	Deg = 0;
	Coefficients = new double[1];
	Coefficients[0] = 0;
}

//s
Polynomial:: ~Polynomial()
{
	Deg = 0;
	delete[] Coefficients;
}

//s
Polynomial::Polynomial(const int& deg)
{
	Deg = deg;
	Coefficients = new double[Deg+1];
	for (int i(Deg); i >= 0; i--)
		Coefficients[i] = 0;
}

Polynomial& Polynomial::operator =(const Polynomial& P)
{
	if (this == &P)
		return *this;
	delete[] Coefficients;
	Deg = P.Deg;
	Coefficients = new double[Deg + 1];
	for (int i(Deg); i >= 0; i--)
		Coefficients[i] = P.Coefficients[i];
	return *this;
}

//s
Polynomial::Polynomial(const Polynomial& M)
{
	Deg = M.Deg;
	Coefficients = new double[Deg + 1];
	for (int i(Deg); i >= 0; i--)
		Coefficients[i] = M.Coefficients[i];
}

//s
double Polynomial::ValueCalculating(const int& x) const
{
	double Result(0);
	for (int i(Deg); i >= 0; i--)
		Result += (Coefficients[i] * pow(x, i));
	return Result;
}

//s
Polynomial Polynomial::FirstDerivative()
{
	Polynomial New(*this);
	New.Coefficients[Deg] = 0;
	for (int i(Deg-1); i >= 0; i--)
		New.Coefficients[i] = Coefficients[i + 1] * (i + 1);
	return New;
}

//s
Polynomial Polynomial::operator+(const Polynomial& P) const
{
	if (Deg == P.Deg)
	{
		Polynomial Result(*this);
		for (int i(Deg); i >= 0; i--)
			Result.Coefficients[i] += P.Coefficients[i];
		return Result;
	}
	else
	{
		if (Deg > P.Deg)
		{
			Polynomial Result(*this);
			for (int i(P.Deg); i >= 0; i--)
				Result.Coefficients[i] += P.Coefficients[i];
			return Result;
		}
		else
		{
			Polynomial Result(P);
			for (int i(Deg); i >= 0; i--)
				Result.Coefficients[i] += Coefficients[i];
			return Result;
		}
	}
}

//s
Polynomial Polynomial::operator-(const Polynomial& P) const
{
	if (Deg == P.Deg)
	{
		Polynomial Result(*this);
		for (int i(Deg); i >= 0; i--)
			Result.Coefficients[i] -= P.Coefficients[i];
		return Result;
	}
	else
	{
		if (Deg > P.Deg)
		{
			Polynomial Result(*this);
			for (int i(P.Deg); i >= 0; i--)
				Result.Coefficients[i] -= P.Coefficients[i];
			return Result;
		}
		else
		{
			Polynomial Result(P);
			for (int i(P.Deg); i > Deg; i--)
				Result.Coefficients[i] = -1 * P.Coefficients[i];
			for (int i(Deg); i >= 0; i--)
				Result.Coefficients[i] = Coefficients[i] - P.Coefficients[i];
			return Result;
		}
	}
}

//s
Polynomial Polynomial::operator*(const Polynomial& P) const
{
	Polynomial Result(Deg + P.Deg);
	for (int i(Deg + P.Deg); i >= 0; i--)
		Result.Coefficients[i] = 0;
	for (int j(P.Deg); j >= 0; j--)
		for (int k(Deg); k >= 0; k--)
			Result.Coefficients[j + k] += (P.Coefficients[j] * Coefficients[k]);
	return Result;
}

//s
istream& operator >> (istream& in, Polynomial& P)
{
	cout << "¬ведите степень многочлена: ";
	in >> P.Deg;
	P.Coefficients = new double[P.Deg + 1];
	cout << "¬ведите коэффиценты многочлена, начина€ с коэффицента переменной максимальной степени и заканчива€ коэффицентом переменной с минимальной степенью: ";
	for (int i(P.Deg); i >= 0; i--)
		in >> P.Coefficients[i];
	cout << endl;
	return in;
}  

//s
ostream& operator << (ostream& out, const Polynomial& P) 
{
	bool FlagPrevZero(false), FlagAllZero(true);
	for (int i(P.Deg); i >= 0; i--)
	{
		if (P.Deg == 0)
			cout << P.Coefficients[0] << endl;
		else
			if (P.Deg == 1 && i == 1)
				cout << P.Coefficients[1] << "*x";
		else
			if (i == P.Deg && i != 0 && i != 1)
				if (P.Coefficients[i] == 0)
			    {
				FlagPrevZero = true;
				continue;
			}
			else
				if (P.Coefficients[i] == 1)
				{
					out << "x^" << i;
					FlagAllZero = false;
					FlagPrevZero = false;
				}
				else
					if (P.Coefficients[i] == -1)
					{
						out << "-x^" << i;
						FlagAllZero = false;
						FlagPrevZero = false;
					}
					else
					{
						out << P.Coefficients[i] << "*x^" << i;
						FlagAllZero = false;
						FlagPrevZero = false;
					}
		else
			//вывод младшего коэффицента
			if (i == 0)
			{
				if (P.Coefficients[i] != 0 && FlagPrevZero == false)
				{
					if (P.Coefficients[i]>0)
						out << "+" << P.Coefficients[i] << endl;
					else
						out << P.Coefficients[i] << endl;
				}
				else
					if (P.Coefficients[i] != 0 && FlagPrevZero==true)
					{
						if (P.Coefficients[i] > 0)
							out << "+" << P.Coefficients[i] << endl;
						else
							out << P.Coefficients[i] << endl;
						FlagPrevZero = false;
					}
					else
						if (P.Coefficients[i] == 0)
						{
							cout << endl;
							continue;
						}
			}
			else
				//вывод переменной с первой степенью
				if (i == 1)
				{
					//если предыдущий ненулевой
					if (P.Coefficients[i] != 0 && FlagPrevZero == false)
					{
						FlagPrevZero = false;
						if (P.Coefficients[i] == 1)
							out << "+x";
						else
							if (P.Coefficients[i] == -1)
								out << "-x";
							else
								if (P.Coefficients[i] > 0)
									out << "+" << P.Coefficients[i] << "*x";
								else
									out << P.Coefficients[i] << "*x";
					}
					else
						// вывод с предыдущим нулем
						if (P.Coefficients[i] != 0 && FlagPrevZero == true)
						{
							FlagPrevZero = false;
							if (P.Coefficients[i] == 1)
								out << "x";
							else
								if (P.Coefficients[i] == -1)
									out << "-x";
								else
									if (FlagAllZero == true)
										out << P.Coefficients[i] << "*x";
									else
										if (P.Coefficients[i] > 0)
											out << "+" << P.Coefficients[i] << "*x";
										else
											out << P.Coefficients[i] << "*x";
						}
						else
							if (P.Coefficients[i] == 0)
							{
								FlagPrevZero = true;
								continue;
							}
				}
		         // вывод остальных
				else
				{
					//когда все, кроме выводимого нулевые
					if (FlagAllZero == true && P.Coefficients[i] != 0)
					{
						FlagPrevZero = false;
						FlagAllZero = false;
						if (P.Coefficients[i] == 1)
							out << "x^" << i;
						else
							if (P.Coefficients[i] == -1)
								out << "-x^" << i;
							else
								if (P.Coefficients[i] > 0)
									out << P.Coefficients[i] << "*x^" << i;
					}
					else
						//когда предыдущий нулевой, остальные нет
							if (FlagPrevZero == true && FlagAllZero == false && P.Coefficients[i] != 0)
							{
								if (P.Coefficients[i] == 1)
									out << "+x^" << i;
								else
									if (P.Coefficients[i] == -1)
										out << "-x^" << i;
									else
										if (P.Coefficients[i] > 0)
											out << "+" << P.Coefficients[i] << "*x^" << i;
										else
											out << P.Coefficients[i] << "*x^" << i;
								FlagPrevZero = false;
							}
						else
						    //когда предыдущий ненулевой
							if (P.Coefficients[i] != 0)
							{
								if (P.Coefficients[i] == 1)
									out << "+x^" << i;
								else
									if (P.Coefficients[i] == -1)
										out << "-x^" << i;
									else
										if (P.Coefficients[i] > 0)
											out << "+" << P.Coefficients[i] << "*x^" << i;
										else
											out << P.Coefficients[i] << "*x^" << i;
								FlagPrevZero = false;
								FlagAllZero = false;
							}
							else
								if (P.Coefficients[i] == 0)
								{
									FlagPrevZero = true;
									continue;
								}
				}
	}
	return out;
}
