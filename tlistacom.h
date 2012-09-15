
#ifndef _TListaCom_
#define _TListaCom_
#include "tcomplejo.h"
using namespace std;

class TListaNodo;
class TListaPos;

class TListaCom{
    friend class TListaNodo;
    friend class TListaPos;
    friend ostream & operator<<(ostream &,const TListaCom &);
    private:
        TListaNodo *primero;    //primera posicion de la lista
        TListaNodo *ultimo;     //ultima posicion de la lista
    public:
        TListaCom();
        TListaCom(const TListaCom &);
        ~TListaCom();
        bool EsVacia() const;
        bool InsCabeza(const TComplejo &);
        bool InsertarI(const TComplejo &,const TListaPos &);
        bool InsertarD(const TComplejo &,const TListaPos &);
        bool Borrar(const TComplejo &);
        bool BorrarTodos(const TComplejo &);
        bool Borrar(const TListaPos &);
        TComplejo Obtener(const TListaPos &) const;
        bool Buscar(const TComplejo &) const;
        int Longitud() const;
        TListaPos Primera() const;
        TListaPos Ultima() const;
        TListaCom& operator=(const TListaCom &);
        bool operator==(const TListaCom &) const;
        bool operator!=(const TListaCom &) const;
        TListaCom operator+(const TListaCom &) const;
        TListaCom operator-(const TListaCom &) const;
	//funciones del examen de prueba de practicas
	TListaCom Sublista(int,int) const;
	TListaCom Suma(const TListaCom&) const;
	bool Borrar_Si(const char*);
	TListaCom Ordenada(const char*) const;
};

class TListaNodo{
    friend class TListaCom;
    friend class TListaPos;
    private:
        TComplejo e;            //elemento del nodo (numero complejo)
        TListaNodo *anterior;   //puntero al siguiente nodo
        TListaNodo *siguiente;  //puntero al anterior nodo
    public:
        TListaNodo();
        TListaNodo(const TListaNodo &);
        ~TListaNodo();
        TListaNodo& operator=(const TListaNodo &);
        TComplejo GetE() const {return e;};
        TListaNodo* GetAnterior() const {return anterior;};
        TListaNodo* GetSiguiente() const {return siguiente;};
};

class TListaPos{
    friend class TListaCom;
    friend class TListaNodo;
    private:
        TListaNodo *pos;       //puntero a un nodo de la lista
    public:
        TListaPos();
        TListaPos(const TListaPos &);
        ~TListaPos();
	TListaNodo * GetPos() const;
        TListaPos& operator=(const TListaPos &);
        bool operator==(const TListaPos &) const;
        bool operator!=(const TListaPos &) const;
        TListaPos Anterior() const;
        TListaPos Siguiente() const;
        bool EsVacia() const;
};
#endif

