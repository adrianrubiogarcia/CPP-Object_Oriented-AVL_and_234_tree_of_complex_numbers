
#ifndef _TAVLCOM_
#define _TAVLCOM_
#include "tlistacom.h"
using namespace std;

class TAVLNodo;

class TAVLCom{
	friend class TAVLNodo;
	private:
		TAVLNodo *raiz; //puntero al nodo raiz del arbol
		void InordenAux(TListaCom &); //metodos auxiliares para
		void PreordenAux(TListaCom &); //reducir el coste temporal
		void PostordenAux(TListaCom &); //del calculo de los recorridos
		void NivelesAux(TComplejo [],int [],int &,int);
	public:
		TAVLCom();
		TAVLCom(const TAVLCom &);
		~TAVLCom();
		TAVLCom& operator=(const TAVLCom &);
		bool operator==(const TAVLCom &) const;
		bool operator!=(const TAVLCom &) const;
		bool EsVacio() const;
		bool Insertar(const TComplejo &);
		bool Borrar(const TComplejo &);
		bool Buscar(const TComplejo &) const;
		int Altura() const;
		int Nodos() const;
		int NodosHoja() const;
		TListaCom Inorden();
		TListaCom Preorden();
		TListaCom Postorden();
		TListaCom Niveles();
		TListaCom Mostrar_Nivel(int);
		TComplejo Num_Raiz() const;
};

class TAVLNodo{
	friend class TAVLCom;
	private:
		TComplejo item; // etiqueta del nodo
		TAVLCom iz,de; // arboles hijo (izquierdo y derecho)
		int fe;// factor de equilibrio
	public:
		TAVLNodo();
		TAVLNodo(const TAVLNodo &);
		~TAVLNodo();
		bool NodoHoja() const;
		TAVLNodo & operator=(const TAVLNodo &);
};
#endif


