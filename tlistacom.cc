
#include "tlistacom.h"

// METODOS DE LA CLASE TLISTACOM
// Constructor por defecto
TListaCom::TListaCom(){
    primero=NULL;
    ultimo=NULL;
}

// Constructor de copia
TListaCom::TListaCom(const TListaCom &lista){
    TListaNodo *aux,*nodo,*ant;
    if(lista.EsVacia()){//si la lista a copiar es vacia con asingar null es suficiente
        primero=NULL; ultimo=NULL;
    }
    else{                     //si la lista que se quiere copiar no esta vacia
        aux=lista.primero;    //se crea el primer nodo y se asigna el atributo primero
        ant=new TListaNodo(*aux);
        if(!ant) cerr<<"ERROR:_No_se_ha_podido_realizar_la_reserva_de_memoria_en_TListaCom::TListaCom(TListaCom&)"<<endl;
        else{
            ant->siguiente=NULL;
            ant->anterior=NULL;
            primero=ant;
            aux=aux->siguiente;
            if(lista.Longitud()==1) ultimo=ant; //si la lista original solo tenia un nodo se asigna el atributo ultimo
            else{ //si la lista contiene mas de un nodo
                while(aux!=NULL){    //se siguen creando nodos hasta que queden en la lista origen
                    nodo=new TListaNodo(*aux);
                    if(!nodo) cerr<<"ERROR:_No_se_ha_podido_realizar_la_reserva_de_memoria_en_TListaCom::TListaCom(TListaCom&)"<<endl;
                    else{
                        nodo->siguiente=NULL;
                        nodo->anterior=ant;
                        ant->siguiente=nodo;
                        ant=nodo;
                        aux=aux->siguiente;
                    }
                }
                ultimo=nodo;        //ultimo sera el ultimo nodo creado
            }
        }
    }
}

// Destructor
TListaCom::~TListaCom(){
    TListaNodo *aux,*sig;
    if(EsVacia()==false){ //si la lista contiene nodos liberamos toda la memoria
        if(Longitud()==1){//si la lista solo contiene un nodo
            delete primero;
            primero=NULL;
            ultimo=NULL;
        }
        else{
            aux=primero;
            sig=aux->siguiente;
            while(aux!=NULL){
                delete aux;
                aux=sig;
                if(aux!=NULL) sig=aux->siguiente;
            }
            primero=NULL;
            ultimo=NULL;
        }
    }
}

// Metodo EsVacia (true si la lista esta vacia)
bool
TListaCom::EsVacia() const{
    if((primero==NULL)&&(ultimo==NULL)) return true;
    else return false;
}

// Metodo InsCabeza (inserta el elemento al principio de la lista)
bool
TListaCom::InsCabeza(const TComplejo &num){
    TListaNodo *aux;
    aux=new TListaNodo();
    if(!aux){
        cerr<<"ERROR:_No_se_ha_podido_realizar_la_reserva_de_memoria_en_TListaCom::InsCabeza(TComplejo&)"<<endl;
        return false;
    }
    else{
        aux->e=num;
        aux->siguiente=primero;
        aux->anterior=NULL;
	if(primero!=NULL) primero->anterior=aux;
        primero=aux;
        if(ultimo==NULL) ultimo=aux;
        return true;
    }
}

// Metodo InsertarI (inserta el elemento a la izquierda de la posicion)
bool
TListaCom::InsertarI(const TComplejo &num,const TListaPos &posicion){
    TListaNodo *aux,*nodo;
    if((this->EsVacia())||(posicion.EsVacia())) return false;//si la lista o la posicion estan vacias
    else{//si las dos no estan vacias
        aux=primero;
        while((aux!=NULL)&&(aux!=posicion.pos)){//recorremos la lista para ver si la posicion pertenece a esa lista
            aux=aux->siguiente;
        }
        if(aux==NULL) return false; //si no pertenece devolvemos false
        else{ //si la posicion pertenece a la lista insertamos el elemento correspondiente a la izquierda
            nodo=new TListaNodo();
            if(!nodo){
                cerr<<"ERROR:_No_se_ha_podido_realizar_la_reserva_de_memoria_en_TListaCom::InsertarI(TComplejo&,TListaPos&)"<<endl;
                return false;
            }
            else{//si la posicion si que pertenece a la lista
	    	if(aux->anterior==NULL){//si la posicion es la primera
		    primero=nodo;
        	}
        	else{//si la posicion no es la primera
                    aux->anterior->siguiente=nodo;
		    nodo->anterior=aux->anterior;
	    	}
		aux->anterior=nodo;
		nodo->siguiente=aux;
                nodo->e=num;
                return true;
            }
        }
    }
}

// Metodo InsertarD (inserta el elemento a la derecha de la posicion)
bool
TListaCom::InsertarD(const TComplejo &num,const TListaPos &posicion){
    TListaNodo *aux,*nodo;
    if((this->EsVacia())||(posicion.EsVacia())) return false;//si la lista o la posicion estan vacias
    else{//si las dos no estan vacias
        aux=primero;
        while((aux!=NULL)&&(aux!=posicion.pos)){//recorremos la lista para ver si la posicion pertenece a esa lista
            aux=aux->siguiente;
        }
        if(aux==NULL) return false; //si no pertenece devolvemos false
        else{ //si la posicion pertenece a la lista insertamos el elemento correspondiente a la derecha
            nodo=new TListaNodo();
            if(!nodo){
                cerr<<"ERROR:_No_se_ha_podido_realizar_la_reserva_de_memoria_en_TListaCom::InsertarD(TComplejo&,TListaPos&)"<<endl;
                return false;
            }
            else{// si la posicion si que pertenece a la lista
		if(aux->siguiente==NULL){//si la posicion es la ultima
		    ultimo=nodo;
        	}
        	else{//si la posicion no es la ultima
                    aux->siguiente->anterior=nodo;
		    nodo->siguiente=aux->siguiente;
	    	}
		aux->siguiente=nodo;
		nodo->anterior=aux;
                nodo->e=num;
                return true;
            }
        }
    }
}

// Metodo Borrar (borra la primera ocurrencia del elemento en la lista)
bool
TListaCom::Borrar(const TComplejo &num){
    TListaNodo *aux,*ant,*sig;
    if(this->Buscar(num)){ //si el numero si que existe en la lista
        aux=primero;
        while(aux->e!=num){
            aux=aux->siguiente;
        }
        if(aux->anterior==NULL){//si el elemento a borrar esta el primero
            if(aux->siguiente==NULL){//si solo existe dicho elemento
                primero=NULL;
                ultimo=NULL;
            }
            else{//si existen mas elementos
                aux->siguiente->anterior=NULL;
                primero=aux->siguiente;
            }
        }
        else{
            if(aux->siguiente==NULL){//si el elemento a borrar esta el ultimo
                aux->anterior->siguiente=NULL;
                ultimo=aux->anterior;
            }
            else{//si el elemento a borrar esta en el interior
                aux->anterior->siguiente=aux->siguiente;
                aux->siguiente->anterior=aux->anterior;
            }
        }
	delete aux;
	return true;
    }//si el numero no existe en la lista
    else return false;
}

// Metodo BorrarTodos (borra todas ocurrencia del elemento en la lista)
bool
TListaCom::BorrarTodos(const TComplejo &num){
    if(this->Buscar(num)==false) return false;//si no esta el elemento no se puede borrar
    else{ //si el elemento existe en la lista
        while(this->Buscar(num)){//mientras siga existiendo lo ira borrando y asi borraremos todas las ocurrencias del mismo
            if(this->Borrar(num)==false) return false;
        }
        return true;
    }
}

// Metodo Borrar (borra el elemento que hay en la posicion de la lista)
bool
TListaCom::Borrar(const TListaPos &posicion){
    TListaNodo *aux,*ant,*sig;
    if((this->EsVacia())||(posicion.EsVacia())) return false;//si la lista o la posicion estan vacias
    else{//si las dos no estan vacias
        aux=primero;
        while((aux!=NULL)&&(aux!=posicion.pos)){//recorremos la lista para ver si la posicion pertenece a esa lista
            aux=aux->siguiente;
        }
        if(aux==NULL) return false; //si no pertenece devolvemos false
        else{ //si la posicion pertenece a la lista eliminamos el elemento correspondiente
	    if(aux->anterior==NULL){//si el elemento a borrar esta el primero
            	if(aux->siguiente==NULL){//si solo existe dicho elemento
                    primero=NULL;
                    ultimo=NULL;
            	}
            	else{//si existen mas elementos
                    aux->siguiente->anterior=NULL;
                    primero=aux->siguiente;
            	}
            }
            else{
            	if(aux->siguiente==NULL){//si el elemento a borrar esta el ultimo
                    aux->anterior->siguiente=NULL;
                    ultimo=aux->anterior;
            	}
            	else{//si el elemento a borrar esta en el interior
                    aux->anterior->siguiente=aux->siguiente;
                    aux->siguiente->anterior=aux->anterior;
            	}
            }
	    delete aux;
            posicion.~TListaPos(); //la posicion tiene que pasar a estar vacia
            return true;
        }
    }
}

// Metodo Obtener (obtiene el elemento que hay en la posicion de la lista)
TComplejo
TListaCom::Obtener(const TListaPos &posicion) const{
    TComplejo res;
    TListaNodo *aux;
    if((this->EsVacia()==false)&&(posicion.EsVacia()==false)){//si las dos no estan vacias
        aux=primero;
        while((aux!=NULL)&&(aux!=posicion.pos)){//recorremos la lista para ver si la posicion pertenece a esa lista
            aux=aux->siguiente;
        }
        if(aux!=NULL){ //si la posicion pertenece a la lista le damos valor a res
            res=aux->e;
        }
    }
return res;
}

// Metodo Buscar (true si el elemento existe en la lista)
bool
TListaCom::Buscar(const TComplejo &num) const{
    TListaNodo *aux;
    if(this->EsVacia()) return false;
    else{//si la lista tiene elementos
        aux=primero;
        while((aux!=NULL)&&(aux->e!=num)){//recorremos hasta encontralo o llegar al final de la lista
            aux=aux->siguiente;
        }
        if(aux==NULL) return false; //cuando hayamos terminado si hemos recorrido la lista entera NO ESTA
        else return true;
    }
}

// Metodo Longitud (devuelve el numero de elementos de la lista)
int
TListaCom::Longitud() const{
    int res=0;
    TListaNodo *aux;
    aux=primero;
    while(aux!=NULL){
        res++;
        aux=aux->siguiente;
    }
    return res;
}

// Metodo Primera (devuelve la primera posicion en la lista)
TListaPos
TListaCom::Primera() const{
    TListaPos res;
    if(this->EsVacia()==false) res.pos=primero;
return res;
}

// Metodo Ultima (devuelve la ultima posicion en la lista)
TListaPos
TListaCom::Ultima() const{
    TListaPos res;
    if(this->EsVacia()==false) res.pos=ultimo;
return res;
}

// Sobrecarga operador = (asignacion de los elementos de una lista a otra)
TListaCom&
TListaCom::operator=(const TListaCom &lista){
 if(*this!=lista){
    TListaNodo *aux,*nodo,*ant;
    if(this->EsVacia()==false) (*this).~TListaCom(); //si la lista destino tenia algo lo eliminamos
    if(lista.EsVacia()){//si la lista a copiar es vacia con asingar null es suficiente
        primero=NULL; ultimo=NULL;
    }
    else{                     //si la lista que se quiere copiar no esta vacia
        aux=lista.primero;    //se crea el primer nodo y se asigna el atributo primero
        ant=new TListaNodo(*aux);
        if(!ant) cerr<<"ERROR:_No_se_ha_podido_realizar_la_reserva_de_memoria_en_TListaCom::operator=(TListaCom&)"<<endl;
        else{
            ant->siguiente=NULL;
            ant->anterior=NULL;
            primero=ant;
            aux=aux->siguiente;
            if(lista.Longitud()==1) ultimo=ant; //si la lista original solo tenia un nodo se asigna el atributo ultimo
            else{ //si la lista contiene mas de un nodo
                while(aux!=NULL){    //se siguen creando nodos hasta que queden en la lista origen
                    nodo=new TListaNodo(*aux);
                    if(!nodo) cerr<<"ERROR:_No_se_ha_podido_realizar_la_reserva_de_memoria_en_TListaCom::operator=(TListaCom&)"<<endl;
                    else{
                        nodo->siguiente=NULL;
                        nodo->anterior=ant;
                        ant->siguiente=nodo;
                        ant=nodo;
                        aux=aux->siguiente;
                    }
                }
                ultimo=nodo;        //ultimo sera el ultimo nodo creado
            }
        }
    }
 }
return *this;
}

// Sobrecarga operador == (igualdad de dos listas)
bool
TListaCom::operator==(const TListaCom &lista) const{
    TListaNodo *aux1,*aux2;
    if(this->Longitud()!=lista.Longitud()) return false; //si no tienen la misma longitud FALSE
    else{ //si las dos tienen la misma longitud
        if((this->EsVacia())&&(lista.EsVacia())) return true; //si las dos estan vacias TRUE
        else{
            aux1=primero; aux2=lista.primero;
            while((aux1!=NULL)&&(aux1->e==aux2->e)){ //recorremos la lista mientras los elementos sean iguales hasta el final
                aux1=aux1->siguiente;
                aux2=aux2->siguiente;
            }
            if(aux1==NULL) return true;  //si hemos llegado al final de la lista todos los elementos son iguales
            else return false;
        }
    }
}

// Sobrecarga operador != (desigualdad de dos listas)
bool
TListaCom::operator!=(const TListaCom &lista) const{
   if((*this)==lista) return false;
   else return true;
}

// Sobrecarga operador + (une dos listas)
TListaCom
TListaCom::operator+(const TListaCom &lista) const{
    TListaNodo *aux;
    TListaCom res(lista);//creamos una lista con el contenido de la lista de la derecha (pasada como parametro)
    if(this->EsVacia()==false){ //si la lista de la izquierda tiene elementos
        aux=ultimo;
        while(aux!=NULL){//recorremos la lista de la izquierda insertando desde el final hasta el principio en la cabeza de la lista resultante
            res.InsCabeza(aux->e);
            aux=aux->anterior;
        }
    }
return res;
}

// Sobrecarga operador - (quita a una lista los elementos de la otra)
TListaCom
TListaCom::operator-(const TListaCom &lista) const{
    TListaNodo *aux;
    TListaCom res(*this); //creamos una lista igual q la del operando de la izquierda
    if(lista.EsVacia()==false){ //si la lista de la derecha tiene elementos
        aux=lista.primero;
        while(aux!=NULL){ //quito de la lista resultante los que esten en la lista de la derecha
            res.BorrarTodos(aux->e);
            aux=aux->siguiente;
        }
    }
    return res;
}

// Sobrecarga operador << (Salida por pantalla)
ostream&
operator<<(ostream &o,const TListaCom &lista){
    TListaNodo *aux;
    o<<"{";
    if(lista.Longitud()>=1){ //si la lista tiene elementos para mostrar
        aux=lista.primero;
        while(aux!=NULL){ //recorremos la lista mostrando los valores separados por un espacio
            o<<aux->GetE();
            if(aux->GetSiguiente()!=NULL) o<<" ";
            aux=aux->GetSiguiente();
        }
    }
    o<<"}";
return o;
}


//funciones del examen de prueba de practicas*****************************************
//funcion Sublista devuelve una lista que contiene los elementos entre los indices inicio y final
TListaCom
TListaCom::Sublista(int inicio,int final) const{
	TListaCom res;
	TListaPos pos = Primera();
	TListaPos pos2;
	int i=1;
	while (i<inicio){
		i++;
		pos = pos.Siguiente();
	}
	res.InsCabeza(Obtener(pos));
	i++;
	while ((i<=final)&&(pos.EsVacia()!=true)){
		pos2 = res.Ultima();
		res.InsertarD(Obtener(pos),pos2);
		i++;
		pos = pos.Siguiente();
	}
return res;
}


//funcion Suma devuelve una lista con los elementos sumados de dos listas
TListaCom
TListaCom::Suma(const TListaCom& lista) const{
	TListaCom res;
	TListaPos pos1,pos2,posnueva;
	TComplejo a,b,suma;
	pos1=Primera();
	pos2=lista.Primera();
	while(pos1.EsVacia()!=true || pos2.EsVacia()!=true){
		a=Obtener(pos1);
		b=lista.Obtener(pos2);
		suma=a+b;
		if(res.EsVacia()) res.InsCabeza(suma);
		else{
			posnueva=res.Ultima();
			res.InsertarD(suma,posnueva);
		}
		pos1=pos1.Siguiente();
		pos2=pos2.Siguiente();
	}
return res;
}

//funcion Borrar_Si borra los elementos que cumplen la condicion (parte entera PAR o IMPAR)
bool
TListaCom::Borrar_Si(const char *condicion){
	bool res;
	int numero;
	char *par="PAR";
	char *impar="IMPAR";
	TComplejo aux,nulo;
	TListaPos pos,poslista;
	TListaCom lista;
	pos=Primera();
	while(pos.EsVacia()==false){ //recorro la lista almacenando los que cumplen la condicion en un vector
		aux=Obtener(pos);
		numero=(int)aux.Mod();
		if(strcmp(condicion,par)==0){
			if(numero%2==0){
				if (lista.EsVacia())
					lista.InsCabeza(aux);
				else{
					poslista=lista.Ultima();
					lista.InsertarD(aux,poslista);
				}
			}
		}
		if(strcmp(condicion,impar)==0){
			if(numero%2!=0){
				if (lista.EsVacia())
					lista.InsCabeza(aux);
				else{
					poslista=lista.Ultima();
					lista.InsertarD(aux,poslista);
				}
			}
		}
		pos=pos.Siguiente();
	}
	if(lista.EsVacia()) res=false; //no hay ningun numero que cumpla la condicion
	else{
		this->~TListaCom();
		poslista=lista.Ultima();
		while(poslista.EsVacia()==false){
			if (EsVacia())
				InsCabeza(lista.Obtener(poslista));
			else{
				pos=Ultima();
				InsertarD(lista.Obtener(poslista),pos);
			}
			poslista=poslista.Anterior();
		}
		res=true;
	}
return res;
}

//funcion Ordenada devuelve una lista con los elementos ordenados (ASC o DES)
TListaCom
TListaCom::Ordenada(const char *condicion) const{
	char *asc="ASC";
	char *des="DES";
	TListaCom res,lista;
	TComplejo num,numpivot;
	TListaPos pos,poslista,pivot;
	lista=*this;
	for(int i=0;i<Longitud();i++){
		poslista=lista.Primera();
		pivot=poslista;
		while(poslista.EsVacia()==false){
			num=lista.Obtener(poslista);
			numpivot=lista.Obtener(pivot);
			if(strcmp(condicion,asc)==0){
				if(num.Mod()<=numpivot.Mod()) pivot=poslista;
			}
			if(strcmp(condicion,des)==0){
				if(num.Mod()>=numpivot.Mod()) pivot=poslista;
			}
			poslista=poslista.Siguiente();
		}
		if (res.EsVacia())
			res.InsCabeza(lista.Obtener(pivot));
		else{
			pos=res.Ultima();
			res.InsertarD(lista.Obtener(pivot),pos);
		}
		lista.Borrar(pivot);
	}
return res;
}



// METODOS DE LA CLASE TLISTANODO
// Constructor por defecto
TListaNodo::TListaNodo(){
    anterior=NULL;
    siguiente=NULL;
}

// Constructor de copia
TListaNodo::TListaNodo(const TListaNodo &nodo){
    e=nodo.e;
    anterior=nodo.anterior;
    siguiente=nodo.siguiente;
}

// Destructor
TListaNodo::~TListaNodo(){
    e.~TComplejo();
    anterior=NULL;
    siguiente=NULL;
}

// Sobrecarga operador = (asignacion de los valores de un nodo a otro)
TListaNodo&
TListaNodo::operator=(const TListaNodo &nodo){
    e=nodo.e;
    anterior=nodo.anterior;
    siguiente=nodo.siguiente;
return *this;
}


// METODOS DE LA CLASE TLISTAPOS
// Constructor por defecto
TListaPos::TListaPos(){
    pos=NULL;
}

// Constructor de copia
TListaPos::TListaPos(const TListaPos &posicion){
    pos=posicion.pos;
}

// Destructor
TListaPos::~TListaPos(){
    pos=NULL;
}

// Metodo GetPos() (devuleve el puntero al nodo de la posicion)
TListaNodo *
TListaPos::GetPos() const{
	return pos;
}

// Sobrecarga operador = (asignacion de los valores de una posicion a otra)
TListaPos&
TListaPos::operator=(const TListaPos &posicion){
    pos=posicion.pos;
return *this;
}

// Sobrecarga operador == (igualdad de dos posiciones)
bool
TListaPos::operator==(const TListaPos &posicion) const{
   if(pos==posicion.pos) return true;
   else return false;
}

// Sobrecarga operador != (desigualdad de dos posiciones)
bool
TListaPos::operator!=(const TListaPos &posicion) const{
   if((*this)==posicion) return false;
   else return true;
}

// Metodo Anterior (devuelve la posicion anterior)
TListaPos
TListaPos::Anterior() const{
    TListaPos res;
    if(pos!=NULL) res.pos=pos->anterior;
return res;
}

// Metodo Siguiente (devuelve la posicion siguiente)
TListaPos
TListaPos::Siguiente() const{
    TListaPos res;
    if(pos!=NULL) res.pos=pos->siguiente;
return res;
}

// Metodo EsVacia (true si la posicion no apunta a una lista)
bool
TListaPos::EsVacia() const{
    if(pos==NULL) return true;
    else return false;
}


