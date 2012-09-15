
#ifndef _TComplejo_
#define _TComplejo_
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class TComplejo{
    friend ostream & operator<<(ostream &,const TComplejo &);
    friend TComplejo operator+(double,const TComplejo &);
    friend TComplejo operator-(double,const TComplejo &);
    friend TComplejo operator*(double,const TComplejo &);
    private:
        double re; //parte real
        double im; //parte imaginaria
    public:
        TComplejo();
        TComplejo(double);
        TComplejo(double,double);
        TComplejo(const TComplejo &);
        ~TComplejo();
        double Re() const;
        double Im() const;
        void Re(double);
        void Im(double);
        double Mod() const;
        double Arg() const;
        TComplejo operator+(const TComplejo &) const;
        TComplejo operator-(const TComplejo &) const;
        TComplejo operator*(const TComplejo &) const;
        TComplejo operator+(double) const;
        TComplejo operator-(double) const;
        TComplejo operator*(double) const;
        TComplejo& operator=(const TComplejo &);
        bool operator==(const TComplejo &) const;
        bool operator!=(const TComplejo &) const;
};
#endif


