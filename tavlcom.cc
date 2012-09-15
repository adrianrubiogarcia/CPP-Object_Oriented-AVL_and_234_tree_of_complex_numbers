
#include "tavlcom.h"


// METODOS DE LA CLASE TAVLCom


// Constructor por defecto
TAVLCom::TAVLCom(){
	raiz=NULL;
}


// Constructor de Copia
TAVLCom::TAVLCom(const TAVLCom &a){
	if(!a.EsVacio()){  // si el arbol no es vacio
		TAVLNodo *aux=new TAVLNodo;
		if(!aux) cerr<<"Error al crear la memoria en TAVLCom::TAVLCom(const TAVLCom &)"<<endl;
		else{
			aux->fe=a.raiz->fe;
			aux->item=a.raiz->item;
			raiz=aux;
			raiz->iz=a.raiz->iz;
			raiz->de=a.raiz->de;
		}
	}
	else raiz=NULL;
}


// Destructor
TAVLCom::~TAVLCom(){
	if(raiz!=NULL){
		delete raiz;
		raiz=NULL;
	}
}


// funcion EsVacio
bool
TAVLCom::EsVacio() const{
	if(raiz==NULL) return true;
	else return false;
}


// funcion  Insertar
bool
TAVLCom::Insertar(const TComplejo &d){
	TAVLCom a,c,e,g;
	TComplejo aux,nulo;
	if(d==nulo) return false;    // Si el numero a insertar es nulo (no hace nada)
	else{
		if(EsVacio()){                      // Si el nodo esta vacio se coloca el elemento
			raiz=new TAVLNodo;
			if(!raiz) cerr<<"Error al crear la memoria en TAVLCom::Insertar(const TComplejo &)"<<endl;
			else{
				raiz->item=d;
				return true;
			}
		}
		else{                     
			if(d.Mod()==raiz->item.Mod()) return false; // si el elemento ya existe no hace nada
			else{                           // si no existe...
				if(d.Mod()>raiz->item.Mod()){           // vemos si va a la derecha (es mayor)
					if (raiz->de.Insertar(d)){     //llamada recursiva
						raiz->fe=raiz->de.Altura()-raiz->iz.Altura();  // se actualiza el factor de equilibrio
						if(raiz->fe>1){   // si el fe es mayor que uno hay que hacer alguna rotacion
							if(raiz->de.raiz->fe==1){  //rotacion DD
								a=raiz->iz;
								c=raiz->de.raiz->iz;
								e=raiz->de.raiz->de;
								aux=raiz->item;
								raiz->item=raiz->de.raiz->item;
								if(raiz->iz.EsVacio())
									raiz->iz.Insertar(aux);
								else
									raiz->iz.raiz->item=aux;
								raiz->de=e;
								raiz->iz.raiz->iz=a;
								raiz->iz.raiz->de=c;
								raiz->iz.raiz->fe=raiz->iz.raiz->de.Altura()-raiz->iz.raiz->iz.Altura();
								raiz->fe=raiz->de.Altura()-raiz->iz.Altura();
							}
							if(raiz->de.raiz->fe==-1){  //rotacion DI
								a=raiz->iz;
								c=raiz->de.raiz->iz.raiz->iz;
								e=raiz->de.raiz->iz.raiz->de;
								g=raiz->de.raiz->de;
								aux=raiz->item;
								raiz->item=raiz->de.raiz->iz.raiz->item;
								if(raiz->iz.EsVacio())
									raiz->iz.Insertar(aux);
								else
									raiz->iz.raiz->item=aux;
								raiz->iz.raiz->iz=a;
								raiz->iz.raiz->de=c;
								raiz->de.raiz->iz=e;
								raiz->de.raiz->de=g;
								raiz->iz.raiz->fe=raiz->iz.raiz->de.Altura()-raiz->iz.raiz->iz.Altura();
								raiz->de.raiz->fe=raiz->de.raiz->de.Altura()-raiz->de.raiz->iz.Altura();
								raiz->fe=raiz->de.Altura()-raiz->iz.Altura();
							}
						}
						return true;
					}
					else return false;
				}
				else{                       // sabemos que va a la izquierda (es menor)
					if (raiz->iz.Insertar(d)){     //llamada recursiva
						raiz->fe=raiz->de.Altura()-raiz->iz.Altura();  // se actualiza el factor de equilibrio
						if (raiz->fe<-1){ // hay que hacer alguna rotacion
							if(raiz->iz.raiz->fe==-1){  //rotacion II
								a=raiz->iz.raiz->iz;
								c=raiz->iz.raiz->de;
								e=raiz->de;
								aux=raiz->item;
								raiz->item=raiz->iz.raiz->item;
								if(raiz->de.EsVacio())
									raiz->de.Insertar(aux);
								else
									raiz->de.raiz->item=aux;
								raiz->iz=a;
								raiz->de.raiz->iz=c;
								raiz->de.raiz->de=e;
								raiz->de.raiz->fe=raiz->de.raiz->de.Altura()-raiz->de.raiz->iz.Altura();
								raiz->fe=raiz->de.Altura()-raiz->iz.Altura();
							}
							if(raiz->iz.raiz->fe==1){  //rotacion ID
								a=raiz->iz.raiz->iz;
								c=raiz->iz.raiz->de.raiz->iz;
								e=raiz->iz.raiz->de.raiz->de;
								g=raiz->de;
								aux=raiz->item;
								raiz->item=raiz->iz.raiz->de.raiz->item;
								if(raiz->de.EsVacio())
									raiz->de.Insertar(aux);
								else
									raiz->de.raiz->item=aux;
								raiz->iz.raiz->iz=a;
								raiz->iz.raiz->de=c;
								raiz->de.raiz->iz=e;
								raiz->de.raiz->de=g;
								raiz->iz.raiz->fe=raiz->iz.raiz->de.Altura()-raiz->iz.raiz->iz.Altura();
								raiz->de.raiz->fe=raiz->de.raiz->de.Altura()-raiz->de.raiz->iz.Altura();
								raiz->fe=raiz->de.Altura()-raiz->iz.Altura();
							}
						}
						return true;
					}
					else return false;
				}
			}
		}
	}
}


// funcion Borrar
bool
TAVLCom::Borrar(const TComplejo &d){
	bool res;
	TAVLCom a,c,e,g;
	TAVLNodo *aux;
	TComplejo num_aux,nulo;
	if(d==nulo) return false;
	else{
		if(EsVacio()) return false;
		else{ //si el arbol no esta vacio
			if(raiz->item==d){ //si hemos encontrado el numero
				if(raiz->NodoHoja()){ //si es un nodo hoja (LO QUITAMOS)
					delete raiz;
					raiz = NULL;
					return true;
				}
				else{ //si no es un nodo hoja (SUSTITUIMOS POR EL MAYOR DE LA IZQUIERDA
					if(!raiz->iz.EsVacio()){ //si tiene hijo izquierdo
						aux = raiz->iz.raiz;
						while (!aux->de.EsVacio()){ //mientras que no lleguemos al mayor del subarbol izquierdo	
							aux = aux->de.raiz;
						}
						num_aux = raiz->item;
						raiz->item = aux->item;
						aux->item = num_aux;
						res = raiz->iz.Borrar(d); //llamada recursiva
					}
					else{ //si no tiene hijo hizquierdo al ser avl solo tendra un hijo derecho
						aux = raiz->de.raiz;
						num_aux = raiz->item;
						raiz->item = aux->item;
						aux->item = num_aux;
						res = raiz->de.Borrar(d); //llamada recursiva
					}
				}
			}
			else{ //si no hemos encontrado el numero (SEGUIMOS BUSCANDO DONDE CORRESPONDA)
				if(d.Mod()>raiz->item.Mod()) res = raiz->de.Borrar(d);
				else res = raiz->iz.Borrar(d);
			}
			if(res == true){ //si hemos quitado algun nodo del arbol (ACTUALIZAR FE Y COMPROBAR REESTRUCTURACIONES)
				raiz->fe = raiz->de.Altura() - raiz->iz.Altura();
				if((raiz->fe==2 && raiz->de.raiz->fe==0)||(raiz->fe==2 && raiz->de.raiz->fe==1)){ // ROTACION DD
					a = raiz->iz;
					c = raiz->de.raiz->iz;
					e = raiz->de.raiz->de;
					num_aux = raiz->item;
					raiz->item = raiz->de.raiz->item;
					if(raiz->iz.EsVacio())
						raiz->iz.Insertar(num_aux);
					else
						raiz->iz.raiz->item = num_aux;
					raiz->de = e;
					raiz->iz.raiz->iz = a;
					raiz->iz.raiz->de = c;
					raiz->iz.raiz->fe = raiz->iz.raiz->de.Altura()-raiz->iz.raiz->iz.Altura();
					raiz->fe = raiz->de.Altura()-raiz->iz.Altura();
				}
				if(raiz->fe==2 && raiz->de.raiz->fe==-1){ // ROTACION DI
					a = raiz->iz;
					c = raiz->de.raiz->iz.raiz->iz;
					e = raiz->de.raiz->iz.raiz->de;
					g = raiz->de.raiz->de;
					num_aux = raiz->item;
					raiz->item = raiz->de.raiz->iz.raiz->item;
					if(raiz->iz.EsVacio())
						raiz->iz.Insertar(num_aux);
					else
						raiz->iz.raiz->item = num_aux;
					raiz->iz.raiz->iz = a;
					raiz->iz.raiz->de = c;
					raiz->de.raiz->iz = e;
					raiz->de.raiz->de = g;
					raiz->iz.raiz->fe = raiz->iz.raiz->de.Altura()-raiz->iz.raiz->iz.Altura();
					raiz->de.raiz->fe = raiz->de.raiz->de.Altura()-raiz->de.raiz->iz.Altura();
					raiz->fe = raiz->de.Altura()-raiz->iz.Altura();
				}
				if((raiz->fe==-2 && raiz->iz.raiz->fe==0)||(raiz->fe==-2 && raiz->iz.raiz->fe==-1)){ // ROTACION II
					a = raiz->iz.raiz->iz;
					c = raiz->iz.raiz->de;
					e = raiz->de;
					num_aux = raiz->item;
					raiz->item = raiz->iz.raiz->item;
					if(raiz->de.EsVacio())
						raiz->de.Insertar(num_aux);
					else
						raiz->de.raiz->item = num_aux;
					raiz->iz = a;
					raiz->de.raiz->iz = c;
					raiz->de.raiz->de = e;
					raiz->de.raiz->fe = raiz->de.raiz->de.Altura()-raiz->de.raiz->iz.Altura();
					raiz->fe = raiz->de.Altura()-raiz->iz.Altura();
				}
				if(raiz->fe==-2 && raiz->iz.raiz->fe==1){ // ROTACION ID
					a = raiz->iz.raiz->iz;
					c = raiz->iz.raiz->de.raiz->iz;
					e = raiz->iz.raiz->de.raiz->de;
					g = raiz->de;
					num_aux = raiz->item;
					raiz->item = raiz->iz.raiz->de.raiz->item;
					if(raiz->de.EsVacio())
						raiz->de.Insertar(num_aux);
					else
						raiz->de.raiz->item = num_aux;
					raiz->iz.raiz->iz = a;
					raiz->iz.raiz->de = c;
					raiz->de.raiz->iz = e;
					raiz->de.raiz->de = g;
					raiz->iz.raiz->fe = raiz->iz.raiz->de.Altura()-raiz->iz.raiz->iz.Altura();
					raiz->de.raiz->fe = raiz->de.raiz->de.Altura()-raiz->de.raiz->iz.Altura();
					raiz->fe = raiz->de.Altura()-raiz->iz.Altura();
				}
			}
			return res;
		}
	}
}


// funcion  Buscar
bool
TAVLCom::Buscar(const TComplejo &d) const{
	if(EsVacio()) return false;
	else{
		if(d==raiz->item) return true;
		else{
			if(d.Mod()>raiz->item.Mod()) return(raiz->de.Buscar(d));
			else return(raiz->iz.Buscar(d));
		}
	}
}


// funcion  Altura
int
TAVLCom::Altura() const{
	int alturade, alturaiz;
	if (EsVacio()) return 0;
	else{
	    alturade=1+raiz->de.Altura();
	    alturaiz=1+raiz->iz.Altura();
	    if(alturade>alturaiz) return alturade;
	    else return alturaiz;
    }
}


// funcion  Nodos
int
TAVLCom::Nodos() const{
	if(EsVacio()) return 0;
	else return (1+raiz->iz.Nodos()+raiz->de.Nodos());
}


// funcion  NodosHoja
int
TAVLCom::NodosHoja() const{
	if(EsVacio()) return 0;
	else{
		if((raiz->iz.EsVacio())&&(raiz->de.EsVacio())) return 1;
		else return (raiz->iz.NodosHoja()+raiz->de.NodosHoja());
	}
}


// funcion  Inorden
TListaCom
TAVLCom::Inorden(){
	TListaCom inorden;
	InordenAux(inorden);
return inorden;
}

// funcion InordenAux (DEVUELVE EL RECORRIDO INORDEN)
void
TAVLCom::InordenAux(TListaCom &lista){
	if(!EsVacio()){
		raiz->iz.InordenAux(lista); //llamada recursiva
		if(lista.EsVacia()) lista.InsCabeza(raiz->item); //insercion del item en la lista
		else {
			TListaPos ultima=lista.Ultima();
			lista.InsertarD(raiz->item,ultima);
		}
		raiz->de.InordenAux(lista); //llamada recursiva
	}
}


// funcion  Preorden
TListaCom
TAVLCom::Preorden(){
	TListaCom preorden;
	PreordenAux(preorden);
return preorden;
}

// funcion PreordenAux (DEVUELVE EL RECORRIDO PREORDEN)
void
TAVLCom::PreordenAux(TListaCom &lista){
	if(!EsVacio()){
		if(lista.EsVacia()) lista.InsCabeza(raiz->item); //insercion del item en la lista
		else {
			TListaPos ultima=lista.Ultima();
			lista.InsertarD(raiz->item,ultima);
		}
		raiz->iz.PreordenAux(lista); //llamada recursiva
		raiz->de.PreordenAux(lista); //llamada recursiva
	}
}


// funcion  Postorden
TListaCom
TAVLCom::Postorden(){
	TListaCom postorden;
	PostordenAux(postorden);
return postorden;
}

// funcion PostordenAux (DEVUELVE EL RECORRIDO POSTORDEN)
void
TAVLCom::PostordenAux(TListaCom &lista){
	if(!EsVacio()){
		raiz->iz.PostordenAux(lista); //llamada recursiva
		raiz->de.PostordenAux(lista); //llamada recursiva
		if(lista.EsVacia()) lista.InsCabeza(raiz->item); //insercion del item en la lista
		else {
			TListaPos ultima=lista.Ultima();
			lista.InsertarD(raiz->item,ultima);
		}
	}
}


// funcion Niveles
TListaCom
TAVLCom::Niveles(){
	int nodos=Nodos();
	int altura=Altura();
	int j,nivel=1,posicion=0;
	TComplejo vectpreorden[nodos];  //me creo un vector con el recorrido preorden del arbol
	int vectniveles[nodos];       //y otro con sus respetivos niveles en el arbol
	for(j=0;j<nodos;j++) vectniveles[j]=0; //inicializo el vector de niveles a cero
	NivelesAux(vectpreorden,vectniveles,posicion,nivel);
	//creo la lista con el recorrido en niveles del arbol
	TListaCom niveles;
	int i,k;
	for(i=1;i<=altura;i++){
		for(k=0;k<nodos;k++){
			if(vectniveles[k]==i){//voy insertando elementos de mayor a menor altura
				if(niveles.EsVacia()) niveles.InsCabeza(vectpreorden[k]);
				else{
					TListaPos ultima=niveles.Ultima();
					niveles.InsertarD(vectpreorden[k],ultima);
				}
			}
		}
	}
return niveles;
}


// funcion NivelesAux (DEVUELVE EL RECORRIDO PREORDEN CON NIVELES)
void
TAVLCom::NivelesAux(TComplejo vector[],int niveles[],int &posicion,int nivel){
	if(!EsVacio()){
		vector[posicion]=raiz->item;
		niveles[posicion]=nivel;
		posicion++;
		raiz->iz.NivelesAux(vector,niveles,posicion,nivel+1); //llamada recursiva
		raiz->de.NivelesAux(vector,niveles,posicion,nivel+1); //llamada recursiva
	}
}


// Sobrecarga del Operador =  (asignacion)
TAVLCom&
TAVLCom::operator=(const TAVLCom &a){
	if(*this!=a){         // Comprobamos autoasignacion
		if(!a.EsVacio()){  // si el arbol a copiar no es vacio
			if(!EsVacio()){ //si el arbol que invoca no es vacio liberamos toda la memoria
				delete raiz;
				raiz=NULL;
			}
			TAVLNodo *aux=new TAVLNodo;
			if(!aux) cerr<<"Error al crear la memoria en TAVLCom::operator=(const TAVLCom &)"<<endl;
			else{
				aux->fe=a.raiz->fe;
				aux->item=a.raiz->item;
				raiz=aux;
				raiz->iz=a.raiz->iz;
				raiz->de=a.raiz->de;
			}
		}
		else{
			if(!EsVacio()){
				delete raiz;
				raiz=NULL;
			}
		}
	}
return *this;
}


// Sobrecarga del Operador ==  (igualdad)
bool
TAVLCom::operator==(const TAVLCom &a) const{
	if((raiz==NULL)&&(a.raiz==NULL)) return true;
	else{
		if(((raiz==NULL)&&(a.raiz!=NULL))||((raiz!=NULL)&&(a.raiz==NULL))) return false;
		else{
			if((raiz->item==a.raiz->item)&&(raiz->fe==a.raiz->fe)){
				if(raiz->iz==a.raiz->iz)
					return raiz->de==a.raiz->de;
				else return false;
			}
			else return false;
		}
	}
}


// Sobrecarga del Operador !=  (desigualdad)
bool
TAVLCom::operator!=(const TAVLCom &a) const{
	if(*this==a) return false;
	else return true;
}


// Ejercicios de EXAMEN ***********************************************************
//funcion Mostrar_Nivel devuelve una lista con los nodos del nivel 
TListaCom
TAVLCom::Mostrar_Nivel(int niv){
	TListaCom res;
	int nodos=Nodos();
	int i,nivel=1,posicion=0;
	TComplejo vectpreorden[nodos];  //me creo un vector para el recorrido preorden del arbol
	int vectniveles[nodos];       //y otro con sus respetivos niveles en el arbol
	for(i=0;i<nodos;i++) vectniveles[i]=0; //inicializo el vector de niveles a cero
	NivelesAux(vectpreorden,vectniveles,posicion,nivel);
	//creo la lista con los nodos del arbol correspondientes al nivel
	for(i=0;i<nodos;i++){
		if(vectniveles[i]==niv){//voy insertando los elementos que estan en ese nivel
			if(res.EsVacia()) res.InsCabeza(vectpreorden[i]);
			else{
				TListaPos ultima=res.Ultima();
				res.InsertarD(vectpreorden[i],ultima);
			}
		}
	}
return res;
}

TComplejo
TAVLCom::Num_Raiz() const{
	return raiz->item;
}



// METODOS DE LA CLASE TAVLNODO

// Constructor por defecto
TAVLNodo::TAVLNodo(){
	fe=0;
}


// Constructor de Copia
TAVLNodo::TAVLNodo(const TAVLNodo &nodo){
	fe=nodo.fe;
	item=nodo.item;
	iz=nodo.iz;
	de=nodo.de;
}


// Destructor por defecto
TAVLNodo::~TAVLNodo(){
	fe=0;
	item.~TComplejo();
	if(!iz.EsVacio())
		iz.~TAVLCom();
	if(!de.EsVacio())
		de.~TAVLCom();
}


//Funcion NodoHoja (true si el nodo es un nodo hoja)
bool
TAVLNodo::NodoHoja() const{
	if(iz.EsVacio() && de.EsVacio()) return true;
	else return false;
}


// Sobrecarga del Operador =  (asignacion)
TAVLNodo&
TAVLNodo::operator=(const TAVLNodo &nodo){
	fe=nodo.fe;
	item=nodo.item;
	iz=nodo.iz;
	de=nodo.de;
return *this;
}

