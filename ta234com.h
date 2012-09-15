
#ifndef _TA234COM_
#define _TA234COM_
#include "tlistacom.h"
using namespace std;

class TA234Nodo;

class TA234Com{
	friend class TA234Nodo;
	private:
		TA234Nodo *raiz; //puntero al nodo raiz del arbol
		void NivelesAux(TComplejo [],int [],int &,int);
	public:
		TA234Com();
		TA234Com(const TA234Com &);
		~TA234Com();
		TA234Com& operator=(const TA234Com &);
		bool operator==(const TA234Com &) const;
		bool operator!=(const TA234Com &) const;
		bool EsVacio() const;
		bool Insertar(const TComplejo &);
		bool Borrar(const TComplejo &);
		bool Buscar(const TComplejo &) const;
		int Altura() const;
		int Nodos() const;
		int NodosHoja() const;
		TListaCom Niveles();
};

class TA234Nodo{
	friend class TA234Com;
	private:
		TComplejo itIz, itMe, itDe; // etiquetas del nodo
		TA234Com hijoIz, hijoMeIz, hijoMeDe, hijoDe; // arboles hijo
	public:
		TA234Nodo();
		TA234Nodo(const TA234Nodo &);
		~TA234Nodo();
		TA234Nodo & operator=(const TA234Nodo &);
		bool DosNodo() const;
		bool TresNodo() const;
		bool CuatroNodo() const;
		bool NodoHoja() const;
};
#endif


