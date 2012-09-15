
#include "tcomplejo.h"

// Constructor por defecto
TComplejo::TComplejo(){
   re=(double)0;
   im=(double)0;
}
// Constructor sobrecargado a partir de la parte real
TComplejo::TComplejo(double valorRe){
   re=(double)valorRe;
   im=(double)0;
   //im=0.0;
}
// Constructor sobrecargado a partir de la parte real y la parte imaginaria
TComplejo::TComplejo(double valorRe, double valorIm){
   re=(double)valorRe;
   im=(double)valorIm;
}
// Constructor de copia
TComplejo::TComplejo(const TComplejo &num){
   re=num.re;
   im=num.im;
}

// Destructor
TComplejo::~TComplejo(){
   re=(double)0;
   im=(double)0;
}

// Metodo Re (devuelve la parte real del numero complejo)
double TComplejo::Re() const{
   return re;
}

// Metodo Im (devuelve la parte imaginaria del numero complejo)
double TComplejo::Im() const{
   return im;
}

// Metodo Re (modifica la parte real del numero complejo)
void TComplejo::Re(double valorRe){
   re=(double)valorRe;
}

// Metodo Im (modifica la parte imaginaria del numero complejo)
void TComplejo::Im(double valorIm){
   im=(double)valorIm;
}

// Metodo Mod (calcula el modulo del numero complejo)
double TComplejo::Mod() const{
   return sqrt(re*re+im*im);
}

// Metodo Arg (calcula el argumento del numero complejo)
double TComplejo::Arg() const{
   return atan2(im,re);
}

// Sobrecarga operador + (suma de dos numeros complejos)
TComplejo TComplejo::operator+(const TComplejo &num) const{
   TComplejo res;
   res.Re(re+num.Re());
   res.Im(im+num.Im());
return res;
}

// Sobrecarga operador - (resta de dos numeros complejos)
TComplejo TComplejo::operator-(const TComplejo &num) const{
   TComplejo res;
   res.Re(re-num.Re());
   res.Im(im-num.Im());
return res;
}

// Sobrecarga operador * (multiplicacion de dos numeros complejos)
TComplejo TComplejo::operator*(const TComplejo &num) const{
   TComplejo res;
   double mod1,mod2,arg1,arg2,resMod,resArg;
   mod1=(*this).Mod();
   mod2=num.Mod();
   arg1=(*this).Arg();
   arg2=num.Arg();
   resMod=mod1*mod2;
   resArg=arg1+arg2;
   res.Re(resMod*cos(resArg));
   res.Im(resMod*sin(resArg));
return res;
}

// Sobrecarga operador + (suma de un numero complejo mas un valor)
TComplejo TComplejo::operator+(double valor) const{
   TComplejo res;
   res.Re(re+valor);
   res.Im(im);
return res;
}

// Sobrecarga operador - (resta de un numero complejo menos un valor)
TComplejo TComplejo::operator-(double valor) const{
   TComplejo res;
   res.Re(re-valor);
   res.Im(im);
return res;
}

// Sobrecarga operador * (multiplicacion de un numero complejo por un valor)
TComplejo TComplejo::operator*(double valor) const{
   TComplejo res;
   res.Re(re*valor);
   res.Im(im*valor);
return res;
}

// Sobrecarga operador = (asignacion de los valores de un numero complejo a otro)
TComplejo& TComplejo::operator=(const TComplejo &num){
   re=(double)num.Re();
   im=(double)num.Im();
}

// Sobrecarga operador == (igualdad de dos numeros complejos)
bool TComplejo::operator==(const TComplejo &num) const{
   if((re==num.Re())&&(im==num.Im())) return true;
   else return false;
}

// Sobrecarga operador != (desigualdad de dos numeros complejos)
bool TComplejo::operator!=(const TComplejo &num) const{
   if((re!=num.Re())||(im!=num.Im())) return true;
   else return false;
}

// Sobrecarga operador << (Salida por pantalla)
ostream & operator<<(ostream &o,const TComplejo &num){
   o<<"("<<num.Re()<<" "<<num.Im()<<")";
return o;
}

// Sobrecarga operador + (suma de un valor mas un numero complejo)
TComplejo operator+(double valor,const TComplejo &num){
   TComplejo res;
   res.Re(valor+num.Re());
   res.Im(num.Im());
return res;
}

// Sobrecarga operador - (resta de un valor menos un numero complejo)
TComplejo operator-(double valor,const TComplejo &num){
   TComplejo res;
   res.Re(valor-num.Re());
   res.Im(num.Im()*(-1));
return res;
}

// Sobrecarga operador * (multiplicacion de un valor por un numero complejo)
TComplejo operator*(double valor,const TComplejo &num){
   TComplejo res;
   res.Re(valor*num.Re());
   res.Im(valor*num.Im());
return res;
}


