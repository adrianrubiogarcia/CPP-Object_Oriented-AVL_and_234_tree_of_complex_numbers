
#include "ta234com.h"


// METODOS DE LA CLASE TA234Com


// Constructor por defecto
TA234Com::TA234Com(){
	raiz=NULL;
}


// Constructor de Copia
TA234Com::TA234Com(const TA234Com &a){
	if(!a.EsVacio()){  // si el arbol no es vacio
		TA234Nodo *aux=new TA234Nodo;
		if(!aux) cerr<<"Error al crear la memoria en TA234Com::TA234Com(const TA234Com &)"<<endl;
		else{
			aux->itIz=a.raiz->itIz;
			aux->itMe=a.raiz->itMe;
			aux->itDe=a.raiz->itDe;
			raiz=aux;
			raiz->hijoIz=a.raiz->hijoIz;
			raiz->hijoMeIz=a.raiz->hijoMeIz;
			raiz->hijoMeDe=a.raiz->hijoMeDe;
			raiz->hijoDe=a.raiz->hijoDe;
		}
	}
	else raiz=NULL;
}


// Destructor
TA234Com::~TA234Com(){
	if(raiz!=NULL){
		delete raiz;
		raiz=NULL;
	}
}


// funcion EsVacio
bool
TA234Com::EsVacio() const{
	if(raiz==NULL) return true;
	else return false;
}


// funcion  Insertar
bool
TA234Com::Insertar(const TComplejo &num){
	TA234Com a,b,c,d,e,f,p;
	TA234Nodo nodoaux;
	TComplejo aux,nulo;
	if(num==nulo) return false;    // Si el numero a insertar es nulo (no hace nada)
	else{
		if(EsVacio()){                      // Si el arbol esta vacio se coloca el elemento
			raiz=new TA234Nodo;
			if(!raiz) cerr<<"Error al crear la memoria en TA234Com::Insertar(const TComplejo &)"<<endl;
			else{
				raiz->itIz=num;
				return true;
			}
		}
		else{               // si el elemento ya existe no hace nada
			if((num.Mod()==raiz->itIz.Mod())||(num.Mod()==raiz->itMe.Mod())||(num.Mod()==raiz->itDe.Mod())) 
				return false; 
			else{                           // si no existe... (Algoritmo)
				if(raiz->CuatroNodo()){ //si la raiz es 4-nodo DIVIDE RAIZ
					a=raiz->hijoIz;
					b=raiz->hijoMeIz;
					c=raiz->hijoMeDe;
					d=raiz->hijoDe;
					raiz->hijoIz.~TA234Com();
					raiz->hijoMeIz.~TA234Com();
					raiz->hijoMeDe.~TA234Com();
					raiz->hijoDe.~TA234Com();
					raiz->hijoIz.raiz = new TA234Nodo;
					raiz->hijoMeIz.raiz = new TA234Nodo;
					if((!raiz->hijoIz.raiz)||(!raiz->hijoMeIz.raiz)) cerr<<"Error al crear la memoria en TA234Com::Insertar(const TComplejo &) al hacer DIVIDERAIZ"<<endl;
					else{ //si los nodos se han creado bien
						raiz->hijoIz.raiz->itIz=raiz->itIz;
						raiz->hijoMeIz.raiz->itIz=raiz->itDe;
						raiz->itIz=raiz->itMe;
						raiz->itMe.~TComplejo();
						raiz->itDe.~TComplejo();
						raiz->hijoIz.raiz->hijoIz=a;
						raiz->hijoIz.raiz->hijoMeIz=b;
						raiz->hijoMeIz.raiz->hijoIz=c;
						raiz->hijoMeIz.raiz->hijoMeIz=d;
						if(num.Mod()>raiz->itIz.Mod()) return raiz->hijoMeIz.Insertar(num);
						else return raiz->hijoIz.Insertar(num);
					}
				}
				else{ // si la raiz no es cuatro nodo ...
					if(raiz->NodoHoja()){ //si el nodo es nodo hoja (insertamos)
						if(raiz->DosNodo()){ // si es un 2-nodo
							if(num.Mod()>raiz->itIz.Mod()){
								raiz->itMe=num;
							}
							else{
								raiz->itMe=raiz->itIz;
								raiz->itIz=num;
							}
						}
						else{ // si s un 3-nodo
							if(num.Mod()<raiz->itIz.Mod()){
								raiz->itDe=raiz->itMe;
								raiz->itMe=raiz->itIz;
								raiz->itIz=num;
							}
							else{
								if(num.Mod()<raiz->itMe.Mod()){
									raiz->itDe=raiz->itMe;
									raiz->itMe=num;
								}
								else{
									raiz->itDe=num;
								}
							}
						}
						return true;
					}					
					else{ //si no es nodo hoja (comprobamos reestructuraciones y hacemos llamada recursiva) 
						// obtenemos el siguiente nodo en el camino de busqueda
						if(raiz->DosNodo()){ //si es 2-nodo
							if(num.Mod()<raiz->itIz.Mod()){ // va en el subarbol izquierdo
								p=raiz->hijoIz;
								e=raiz->hijoMeIz;
								if(p.raiz->CuatroNodo()){ // si p es 4-nodo DIVIDE HIJO DE 2
									c=p.raiz->hijoMeDe;
									d=p.raiz->hijoDe;
									raiz->hijoIz.raiz->hijoMeDe.~TA234Com();
									raiz->hijoIz.raiz->hijoDe.~TA234Com();
									raiz->itMe=raiz->itIz;
									raiz->itIz=p.raiz->itMe;
									raiz->hijoMeDe=e;
									raiz->hijoMeIz.~TA234Com();
									raiz->hijoMeIz.raiz = new TA234Nodo;
									if(!raiz->hijoMeIz.raiz) cerr<<"Error al crear la memoria en TA234Com::Insertar(const TComplejo &) al hacer DIVIDEHIJODE2"<<endl;
									else{ //se asigna el nuevo nodo y se liberan los items
										raiz->hijoMeIz.raiz->itIz=p.raiz->itDe;
										raiz->hijoIz.raiz->itMe.~TComplejo();
										raiz->hijoIz.raiz->itDe.~TComplejo();
										raiz->hijoMeIz.raiz->hijoIz=c;
										raiz->hijoMeIz.raiz->hijoMeIz=d;
										if(num.Mod()<raiz->itIz.Mod()) return raiz->hijoIz.Insertar(num);
										else return raiz->hijoMeIz.Insertar(num);
									}
								}
								else return raiz->hijoIz.Insertar(num);
							}
							else{ // va en el subarbol medio izquierdo
								p=raiz->hijoMeIz;
								e=raiz->hijoIz;
								if(p.raiz->CuatroNodo()){ // si p es 4-nodo DIVIDE HIJO DE 2
									c=p.raiz->hijoMeDe;
									d=p.raiz->hijoDe;
									raiz->hijoMeIz.raiz->hijoMeDe.~TA234Com();
									raiz->hijoMeIz.raiz->hijoDe.~TA234Com();
									raiz->itMe=p.raiz->itMe;
									raiz->hijoMeDe.raiz = new TA234Nodo;
									if(!raiz->hijoMeDe.raiz) cerr<<"Error al crear la memoria en TA234Com::Insertar(const TComplejo &) al hacer DIVIDEHIJODE2"<<endl;
									else{ //se asigna el nuevo nodo y se liberan los items
										raiz->hijoMeDe.raiz->itIz=p.raiz->itDe;
										raiz->hijoMeIz.raiz->itMe.~TComplejo();
										raiz->hijoMeIz.raiz->itDe.~TComplejo();
										raiz->hijoMeDe.raiz->hijoIz=c;
										raiz->hijoMeDe.raiz->hijoMeIz=d;
										if (num.Mod()<raiz->itMe.Mod())
										return raiz->hijoMeIz.Insertar(num);
										else
										return raiz->hijoMeDe.Insertar(num);
									}
								}
								else return raiz->hijoMeIz.Insertar(num);
							}
						}
						else { // si es 3-nodo
							if(num.Mod()<raiz->itIz.Mod()){ // va en el subarbol izquierdo
								p=raiz->hijoIz;
								e=raiz->hijoMeIz;
								f=raiz->hijoMeDe;
								if(p.raiz->CuatroNodo()){ // si p es 4-nodo DIVIDE HIJO DE 3
									c=p.raiz->hijoMeDe;
									d=p.raiz->hijoDe;
									raiz->hijoIz.raiz->hijoMeDe.~TA234Com();
									raiz->hijoIz.raiz->hijoDe.~TA234Com();
									raiz->itDe=raiz->itMe;
									raiz->itMe=raiz->itIz;
									raiz->itIz=p.raiz->itMe;
									raiz->hijoDe=f;
									raiz->hijoMeDe=e;
									raiz->hijoMeIz.~TA234Com();
									raiz->hijoMeIz.raiz = new TA234Nodo;
									if(!raiz->hijoMeIz.raiz) cerr<<"Error al crear la memoria en TA234Com::Insertar(const TComplejo &) al hacer DIVIDEHIJODE3"<<endl;
									else{ //se asigna el nuevo nodo y se liberan los items
										raiz->hijoMeIz.raiz->itIz=p.raiz->itDe;
										raiz->hijoIz.raiz->itMe.~TComplejo();
										raiz->hijoIz.raiz->itDe.~TComplejo();
										raiz->hijoMeIz.raiz->hijoIz=c;
										raiz->hijoMeIz.raiz->hijoMeIz=d;
										if(num.Mod()<raiz->itIz.Mod()) return raiz->hijoIz.Insertar(num);
										else return raiz->hijoMeIz.Insertar(num);
									}
								}
								else return raiz->hijoIz.Insertar(num);
							}
							else{
								if(num.Mod()<raiz->itMe.Mod()){ // va en el subarbol medio izquierdo
									p=raiz->hijoMeIz;
									e=raiz->hijoIz;
									f=raiz->hijoMeDe;
									if(p.raiz->CuatroNodo()){ // si p es 4-nodo DIVIDE HIJO DE 3
										c=p.raiz->hijoMeDe;
										d=p.raiz->hijoDe;
										raiz->hijoMeIz.raiz->hijoMeDe.~TA234Com();
										raiz->hijoMeIz.raiz->hijoDe.~TA234Com();
										raiz->itDe=raiz->itMe;
										raiz->itMe=p.raiz->itMe;
										raiz->hijoDe=f;
										raiz->hijoMeDe.~TA234Com();
										raiz->hijoMeDe.raiz = new TA234Nodo;
										if(!raiz->hijoMeDe.raiz) cerr<<"Error al crear la memoria en TA234Com::Insertar(const TComplejo &) al hacer DIVIDEHIJODE3"<<endl;
										else{ //se asigna el nuevo nodo y se liberan los items
											raiz->hijoMeDe.raiz->itIz=p.raiz->itDe;
											raiz->hijoMeIz.raiz->itMe.~TComplejo();
											raiz->hijoMeIz.raiz->itDe.~TComplejo();
											raiz->hijoMeDe.raiz->hijoIz=c;
											raiz->hijoMeDe.raiz->hijoMeIz=d;
											if (num.Mod()<raiz->itMe.Mod())
											return raiz->hijoMeIz.Insertar(num);
											else
											return raiz->hijoMeDe.Insertar(num);
										}
									}
									else return raiz->hijoMeIz.Insertar(num);
								}
								else{ // va en el subarbol medio derecho
									p=raiz->hijoMeDe;
									e=raiz->hijoIz;
									f=raiz->hijoMeIz;
									if(p.raiz->CuatroNodo()){ // si p es 4-nodo DIVIDE HIJO DE 3
										c=p.raiz->hijoMeDe;
										d=p.raiz->hijoDe;
										raiz->hijoMeDe.raiz->hijoMeDe.~TA234Com();
										raiz->hijoMeDe.raiz->hijoDe.~TA234Com();
										raiz->itDe=p.raiz->itMe;
										raiz->hijoDe.raiz = new TA234Nodo;
										if(!raiz->hijoDe.raiz) cerr<<"Error al crear la memoria en TA234Com::Insertar(const TComplejo &) al hacer DIVIDEHIJODE3"<<endl;
										else{ //se asigna el nuevo nodo y se liberan los items
											raiz->hijoDe.raiz->itIz=p.raiz->itDe;
											raiz->hijoMeDe.raiz->itMe.~TComplejo();
											raiz->hijoMeDe.raiz->itDe.~TComplejo();
											raiz->hijoDe.raiz->hijoIz=c;
											raiz->hijoDe.raiz->hijoMeIz=d;
											if(num.Mod()<raiz->itDe.Mod())
											return raiz->hijoMeDe.Insertar(num);
											else
											return raiz->hijoDe.Insertar(num);
										}
									}
									else return raiz->hijoMeDe.Insertar(num);
								}
							}
						}
					}
				}
			}
		}
	}
}


// funcion Borrar
bool
TA234Com::Borrar(const TComplejo &num){
	TA234Com q,r;
	TA234Com a,b,c,d,e,f;
	TComplejo num_aux,nulo;
	TA234Nodo *aux;
	if(num==nulo){ //si el elemento a insertar es nulo NO HACE NADA
		return false;
	}
	else{ //si el elemento a insertar no es nulo
		if(!Buscar(num)){ //si el elemento no existe NO HACE NADA
			return false;
		}
		else{ //si el elmento si que existe BUSQUEDA DEL ELEMENTO
			if(raiz->itIz==num || raiz->itMe==num || raiz->itDe==num){//si el numero esta en este nodo
				if(!raiz->NodoHoja()){ //si el elemento no esta en un nodo hoja SUSTITUIMOS MAYOR IZQ
					if(raiz->itIz==num){
						num_aux = raiz->itIz;
						aux = raiz->hijoMeIz.raiz;
						while (!aux->NodoHoja()){ //llego hasta el mayor de su izquierda
							if(aux->CuatroNodo()) aux = aux->hijoDe.raiz;
							if(aux->TresNodo())   aux = aux->hijoMeDe.raiz;
							if(aux->DosNodo())    aux = aux->hijoMeIz.raiz;
						}      //hago el cambio de etiqueta
						if(aux->CuatroNodo()){
							raiz->itIz = aux->itDe;
							aux->itDe = num_aux;
						}
						if(aux->TresNodo()){
							raiz->itIz = aux->itMe;
							aux->itMe = num_aux;
						}
						if(aux->CuatroNodo()){
							raiz->itIz = aux->itIz;
							aux->itIz = num_aux;
						}
					}
					if(raiz->itMe==num){
						num_aux = raiz->itMe;
						aux = raiz->hijoMeDe.raiz;
						while (!aux->NodoHoja()){ //llego hasta el mayor de su izquierda
							if(aux->CuatroNodo()) aux = aux->hijoDe.raiz;
							if(aux->TresNodo())   aux = aux->hijoMeDe.raiz;
							if(aux->DosNodo())    aux = aux->hijoMeIz.raiz;
						}     //hago el cambio de etiqueta
						if(aux->CuatroNodo()){
							raiz->itMe = aux->itDe;
							aux->itDe = num_aux;
						}
						if(aux->TresNodo()){
							raiz->itMe = aux->itMe;
							aux->itMe = num_aux;
						}
						if(aux->CuatroNodo()){
							raiz->itMe = aux->itIz;
							aux->itIz = num_aux;
						}
					}
					if(raiz->itDe==num){
						num_aux = raiz->itDe;
						aux = raiz->hijoDe.raiz;
						while (!aux->NodoHoja()){ //llego hasta el mayor de su izquierda
							if(aux->CuatroNodo()) aux = aux->hijoDe.raiz;
							if(aux->TresNodo())   aux = aux->hijoMeDe.raiz;
							if(aux->DosNodo())    aux = aux->hijoMeIz.raiz;
						}     //hago el cambio de etiqueta
						if(aux->CuatroNodo()){
							raiz->itDe = aux->itDe;
							aux->itDe = num_aux;
						}
						if(aux->TresNodo()){
							raiz->itDe = aux->itMe;
							aux->itMe = num_aux;
						}
						if(aux->CuatroNodo()){
							raiz->itDe = aux->itIz;
							aux->itIz = num_aux;
						}
					}
					return Borrar(num); //llamamos a buscar en el mismo nodo para seguir la busqueda
				}
				else{ //si el elemento esta en un nodo hoja BORRAMOS
					if(raiz->DosNodo()){
						delete raiz;
						raiz = NULL;
					}
					else{
						if(raiz->TresNodo()){ // si es un 3-nodo
							if(raiz->itIz==num) raiz->itIz = raiz->itMe;
							raiz->itMe.~TComplejo();
						}
						else{ // si es un 4-nodo
							if(raiz->itIz==num){
								raiz->itIz = raiz->itMe;
								raiz->itMe = raiz->itDe;
							}
							if(raiz->itMe==num){
								raiz->itMe = raiz->itDe;
							}
							raiz->itDe.~TComplejo();
						}
					}
					return true;
				}
			}
			else{ //si el elemento no esta en este nodo COMPROBAMOS REESTRUCTURACIONES
			// sacamos q = siguiente en el camino de busqueda y r = hermano izquierda (si existe)
				if(num.Mod()<raiz->itIz.Mod()){ //esta en el subarbol izquierdo
					q = raiz->hijoIz;
					r = raiz->hijoMeIz;
					if(q.raiz->TresNodo() || q.raiz->CuatroNodo()){
					 //si q es 3-nodo o 4-nodo SEGUIMOS
						return raiz->hijoIz.Borrar(num);
					}
					else{ //si q es 2-nodo (REESTRUCTURAR)
						if(r.raiz->DosNodo()){ //si r es 2-nodo COMBINACION
							if(raiz->DosNodo()){ //COMBINACION EN RAIZ
								a = q.raiz->hijoIz;
								b = q.raiz->hijoMeIz;
								c = r.raiz->hijoIz;
								d = r.raiz->hijoMeIz;
								raiz->hijoIz.raiz->hijoIz.~TA234Com();
								raiz->hijoIz.raiz->hijoMeIz.~TA234Com();
								raiz->hijoMeIz.raiz->hijoIz.~TA234Com();
								raiz->hijoMeIz.raiz->hijoMeIz.~TA234Com();
								raiz->itMe = raiz->itIz;
								raiz->itIz = q.raiz->itIz;
								raiz->itDe = r.raiz->itIz;
								raiz->hijoIz  =  a;
								raiz->hijoMeIz = b;
								raiz->hijoMeDe = c;
								raiz->hijoDe  =  d;
								return Borrar(num);
							}
							else{ //COMBINACION EN Q
								c = r.raiz->hijoIz;
								d = r.raiz->hijoMeIz;
								raiz->hijoMeIz.raiz->hijoIz.~TA234Com();
								raiz->hijoMeIz.raiz->hijoMeIz.~TA234Com();
								if(raiz->TresNodo()){ //p es 3-nodo
									raiz->hijoIz.raiz->itMe = raiz->itIz;
									raiz->hijoIz.raiz->itDe = r.raiz->itIz;
									raiz->itIz = raiz->itMe;
									raiz->itMe.~TComplejo();
									raiz->hijoIz.raiz->hijoMeDe = c;
									raiz->hijoIz.raiz->hijoDe  =  d;
									raiz->hijoMeIz = raiz->hijoMeDe;
									if(!raiz->hijoMeDe.EsVacio())
										raiz->hijoMeDe.~TA234Com();
								}
								else{ //p es 4-nodo
									raiz->hijoIz.raiz->itMe = raiz->itIz;
									raiz->hijoIz.raiz->itDe = r.raiz->itIz;
									raiz->itIz = raiz->itMe;
									raiz->itMe = raiz->itDe;
									raiz->itDe.~TComplejo();
									raiz->hijoIz.raiz->hijoMeDe = c;
									raiz->hijoIz.raiz->hijoDe  =  d;
									raiz->hijoMeIz = raiz->hijoMeDe;
									raiz->hijoMeDe = raiz->hijoDe;
									if(!raiz->hijoDe.EsVacio())
										raiz->hijoDe.~TA234Com();
								}
								return raiz->hijoIz.Borrar(num);
							}
						}
						else{ //si r es 3-nodo o 4-nodo ROTACION
							c = r.raiz->hijoIz;
							d = r.raiz->hijoMeIz;
							e = r.raiz->hijoMeDe;
							f = r.raiz->hijoDe;
							raiz->hijoMeIz.raiz->hijoIz.~TA234Com();
							raiz->hijoMeIz.raiz->hijoMeIz.~TA234Com();
							raiz->hijoMeIz.raiz->hijoMeDe.~TA234Com();
							raiz->hijoMeIz.raiz->hijoDe.~TA234Com();
							raiz->hijoIz.raiz->itMe = raiz->itIz;
							raiz->itIz = r.raiz->itIz;
							raiz->hijoMeIz.raiz->itIz = raiz->hijoMeIz.raiz->itMe;
							raiz->hijoMeIz.raiz->itMe = raiz->hijoMeIz.raiz->itDe;
							raiz->hijoMeIz.raiz->itDe.~TComplejo();
							raiz->hijoIz.raiz->hijoMeDe  =  c;
							raiz->hijoMeIz.raiz->hijoIz  =  d;
							raiz->hijoMeIz.raiz->hijoMeIz = e;
							raiz->hijoMeIz.raiz->hijoMeDe = f;
							return raiz->hijoIz.Borrar(num);
						}
					}
				}
				else{
					if(num.Mod()<raiz->itMe.Mod() || raiz->DosNodo()){//esta en subarbol medio izq
						q = raiz->hijoMeIz;
						r = raiz->hijoIz;
						if(q.raiz->TresNodo() || q.raiz->CuatroNodo()){
						//si q es 3-nodo o 4-nodo SEGUIMOS
							return raiz->hijoMeIz.Borrar(num);
						}
						else{ //si q es 2-nodo (REESTRUCTURAR)
							if(r.raiz->DosNodo()){ //si r es 2-nodo COMBINACION
								if(raiz->DosNodo()){ //COMBINACION EN RAIZ
									a = r.raiz->hijoIz;
									b = r.raiz->hijoMeIz;
									c = q.raiz->hijoIz;
									d = q.raiz->hijoMeIz;
									raiz->hijoIz.raiz->hijoIz.~TA234Com();
									raiz->hijoIz.raiz->hijoMeIz.~TA234Com();
									raiz->hijoMeIz.raiz->hijoIz.~TA234Com();
									raiz->hijoMeIz.raiz->hijoMeIz.~TA234Com();
									raiz->itMe = raiz->itIz;
									raiz->itIz = r.raiz->itIz;
									raiz->itDe = q.raiz->itIz;
									raiz->hijoIz  =  a;
									raiz->hijoMeIz = b;
									raiz->hijoMeDe = c;
									raiz->hijoDe  =  d;
									return Borrar(num);
								}
								else{ //COMBINACION EN Q
								   c = q.raiz->hijoIz;
								   d = q.raiz->hijoMeIz;
								   raiz->hijoMeIz.raiz->hijoIz.~TA234Com();
								   raiz->hijoMeIz.raiz->hijoMeIz.~TA234Com();
								   if(raiz->TresNodo()){ //p es 3-nodo
									raiz->hijoIz.raiz->itMe = raiz->itIz;
									raiz->hijoIz.raiz->itDe = q.raiz->itIz;
									raiz->itMe.~TComplejo();
									raiz->hijoIz.raiz->hijoMeDe = c;
									raiz->hijoIz.raiz->hijoDe  =  d;
									raiz->hijoMeIz = raiz->hijoMeDe;
									if(!raiz->hijoMeDe.EsVacio())
										raiz->hijoMeDe.~TA234Com();
								   }
								   else{ //p es 4-nodo
									raiz->hijoIz.raiz->itMe = raiz->itIz;
									raiz->hijoIz.raiz->itDe = q.raiz->itIz;
									raiz->itIz = raiz->itMe;
									raiz->itMe = raiz->itDe;
									raiz->itDe.~TComplejo();
									raiz->hijoIz.raiz->hijoMeDe = c;
									raiz->hijoIz.raiz->hijoDe  =  d;
									raiz->hijoMeDe = raiz->hijoDe;
									if(!raiz->hijoDe.EsVacio())
										raiz->hijoDe.~TA234Com();
								   }
								   return raiz->hijoIz.Borrar(num);
								}
							}
							else{ //si r es 3-nodo o 4-nodo ROTACION
							   if(r.raiz->TresNodo()){ //si r es 3-nodo
							      c = r.raiz->hijoMeDe;
							      e = q.raiz->hijoIz;
							      f = q.raiz->hijoMeIz;
							      raiz->hijoIz.raiz->hijoMeDe.~TA234Com();
							      raiz->hijoMeIz.raiz->hijoIz.~TA234Com();
							      raiz->hijoMeIz.raiz->hijoMeIz.~TA234Com();
							      raiz->hijoMeIz.raiz->itMe = raiz->hijoMeIz.raiz->itIz;
							      raiz->hijoMeIz.raiz->itIz = raiz->itIz;
							      raiz->itIz = r.raiz->itMe;
							      raiz->hijoIz.raiz->itMe.~TComplejo();
							      raiz->hijoMeIz.raiz->hijoIz  =  c;
							      raiz->hijoMeIz.raiz->hijoMeIz = e;
							      raiz->hijoMeIz.raiz->hijoMeDe = f;
							   }
							   else{ //si r es 4-nodo
							      d = r.raiz->hijoDe;
							      e = q.raiz->hijoIz;
							      f = q.raiz->hijoMeIz;
							      raiz->hijoIz.raiz->hijoDe.~TA234Com();
							      raiz->hijoMeIz.raiz->hijoIz.~TA234Com();
							      raiz->hijoMeIz.raiz->hijoMeIz.~TA234Com();
							      raiz->hijoMeIz.raiz->itMe = raiz->hijoMeIz.raiz->itIz;
							      raiz->hijoMeIz.raiz->itIz = raiz->itIz;
							      raiz->itIz = r.raiz->itDe;
							      raiz->hijoIz.raiz->itDe.~TComplejo();
							      raiz->hijoMeIz.raiz->hijoIz  =  d;
							      raiz->hijoMeIz.raiz->hijoMeIz = e;
							      raiz->hijoMeIz.raiz->hijoMeDe = f;
							   }
							   return raiz->hijoMeIz.Borrar(num);
							}
						}
					}
					else{
						if(num.Mod()<raiz->itDe.Mod() || raiz->TresNodo()){ //esta en medio der
						    q = raiz->hijoMeDe;
						    r = raiz->hijoMeIz;
						    if(q.raiz->TresNodo() || q.raiz->CuatroNodo()){
						    //si q es 3-nodo o 4-nodo SEGUIMOS
							return raiz->hijoMeDe.Borrar(num);
						    }
						    else{ //si q es 2-nodo (REESTRUCTURAR)
							if(r.raiz->DosNodo()){ //si r es 2-nodo COMBINACION
							//como p es 3-nodo o 4-nodo COMBINACION EN Q
								c = q.raiz->hijoIz;
								d = q.raiz->hijoMeIz;
								raiz->hijoMeDe.raiz->hijoIz.~TA234Com();
								raiz->hijoMeDe.raiz->hijoMeIz.~TA234Com();
								if(raiz->TresNodo()){ //p es 3-nodo
									raiz->hijoMeIz.raiz->itMe = raiz->itMe;
									raiz->hijoMeIz.raiz->itDe = q.raiz->itIz;
									raiz->itMe.~TComplejo();
									raiz->hijoMeIz.raiz->hijoMeDe = c;
									raiz->hijoMeIz.raiz->hijoDe  =  d;
									if(!raiz->hijoMeDe.EsVacio())
										raiz->hijoMeDe.~TA234Com();
								}
								else{ //p es 4-nodo
									raiz->hijoMeIz.raiz->itMe = raiz->itMe;
									raiz->hijoMeIz.raiz->itDe = q.raiz->itIz;
									raiz->itMe = raiz->itDe;
									raiz->itDe.~TComplejo();
									raiz->hijoMeIz.raiz->hijoMeDe = c;
									raiz->hijoMeIz.raiz->hijoDe  =  d;
									raiz->hijoMeDe = raiz->hijoDe;
									if(!raiz->hijoDe.EsVacio())
										raiz->hijoDe.~TA234Com();
								}
								return raiz->hijoMeIz.Borrar(num);
							}
							else{ //si r es 3-nodo o 4-nodo ROTACION
							   if(r.raiz->TresNodo()){ //si r es 3-nodo
							      c = r.raiz->hijoMeDe;
							      e = q.raiz->hijoIz;
							      f = q.raiz->hijoMeIz;
							      raiz->hijoMeIz.raiz->hijoMeDe.~TA234Com();
							      raiz->hijoMeDe.raiz->hijoIz.~TA234Com();
							      raiz->hijoMeDe.raiz->hijoMeIz.~TA234Com();
							      raiz->hijoMeDe.raiz->itMe = raiz->hijoMeDe.raiz->itIz;
							      raiz->hijoMeDe.raiz->itIz = raiz->itMe;
							      raiz->itMe = r.raiz->itMe;
							      raiz->hijoMeIz.raiz->itMe.~TComplejo();
							      raiz->hijoMeDe.raiz->hijoIz  =  c;
							      raiz->hijoMeDe.raiz->hijoMeIz = e;
							      raiz->hijoMeDe.raiz->hijoMeDe = f;
							   }
							   else{ //si r es 4-nodo
							      d = r.raiz->hijoDe;
							      e = q.raiz->hijoIz;
							      f = q.raiz->hijoMeIz;
							      raiz->hijoMeIz.raiz->hijoDe.~TA234Com();
							      raiz->hijoMeDe.raiz->hijoIz.~TA234Com();
							      raiz->hijoMeDe.raiz->hijoMeIz.~TA234Com();
							      raiz->hijoMeDe.raiz->itMe = raiz->hijoMeDe.raiz->itIz;
							      raiz->hijoMeDe.raiz->itIz = raiz->itMe;
							      raiz->itMe = r.raiz->itDe;
							      raiz->hijoMeIz.raiz->itDe.~TComplejo();
							      raiz->hijoMeDe.raiz->hijoIz  =  d;
							      raiz->hijoMeDe.raiz->hijoMeIz = e;
							      raiz->hijoMeDe.raiz->hijoMeDe = f;
							   }
							   return raiz->hijoMeDe.Borrar(num);
							}
						    }
						}
						else{ // esta en el subarbol derecho
							q = raiz->hijoDe;
							r = raiz->hijoMeDe;
							if(q.raiz->TresNodo() || q.raiz->CuatroNodo()){
							//si q es 3-nodo o 4-nodo SEGUIMOS
								return raiz->hijoDe.Borrar(num);
							}
							else{ //si q es 2-nodo (REESTRUCTURAR)
							  if(r.raiz->DosNodo()){ //si r es 2-nodo COMBINACION
								// q es 4-nodo COMBINACION EN Q
								c = q.raiz->hijoIz;
								d = q.raiz->hijoMeIz;
								raiz->hijoDe.raiz->hijoIz.~TA234Com();
								raiz->hijoDe.raiz->hijoMeIz.~TA234Com();
								raiz->hijoMeDe.raiz->itMe = raiz->itDe;
								raiz->hijoMeDe.raiz->itDe = q.raiz->itIz;
								raiz->itDe.~TComplejo();
								raiz->hijoMeDe.raiz->hijoMeDe = c;
								raiz->hijoMeDe.raiz->hijoDe  =  d;
								raiz->hijoDe.~TA234Com();
								return raiz->hijoMeDe.Borrar(num);
							  }
							  else{ // r es 3-nodo o 4-nodo ROTACION
							    if(r.raiz->TresNodo()){ //si r es 3-nodo
							      c = r.raiz->hijoMeDe;
							      e = q.raiz->hijoIz;
							      f = q.raiz->hijoMeIz;
							      raiz->hijoMeDe.raiz->hijoMeDe.~TA234Com();
							      raiz->hijoDe.raiz->hijoIz.~TA234Com();
							      raiz->hijoDe.raiz->hijoMeIz.~TA234Com();
							      raiz->hijoDe.raiz->itMe = raiz->hijoDe.raiz->itIz;
							      raiz->hijoDe.raiz->itIz = raiz->itDe;
							      raiz->itDe = r.raiz->itMe;
							      raiz->hijoMeDe.raiz->itMe.~TComplejo();
							      raiz->hijoDe.raiz->hijoIz  =  c;
							      raiz->hijoDe.raiz->hijoMeIz = e;
							      raiz->hijoDe.raiz->hijoMeDe = f;
							    }
							    else{ //si r es 4-nodo
							      d = r.raiz->hijoDe;
							      e = q.raiz->hijoIz;
							      f = q.raiz->hijoMeIz;
							      raiz->hijoMeDe.raiz->hijoDe.~TA234Com();
							      raiz->hijoDe.raiz->hijoIz.~TA234Com();
							      raiz->hijoDe.raiz->hijoMeIz.~TA234Com();
							      raiz->hijoDe.raiz->itMe = raiz->hijoDe.raiz->itIz;
							      raiz->hijoDe.raiz->itIz = raiz->itDe;
							      raiz->itDe = r.raiz->itDe;
							      raiz->hijoMeDe.raiz->itDe.~TComplejo();
							      raiz->hijoDe.raiz->hijoIz  =  d;
							      raiz->hijoDe.raiz->hijoMeIz = e;
							      raiz->hijoDe.raiz->hijoMeDe = f;
							    }
							    return raiz->hijoDe.Borrar(num);
							  }
							}
						}
					}
				}
			}
		}
	}
}


// funcion  Buscar
bool
TA234Com::Buscar(const TComplejo &d) const{
	TComplejo nulo;
	if((EsVacio())||(d==nulo)) return false;
	else{
		if(raiz->CuatroNodo()){ //si es un 4-NODO	
			if((d==raiz->itIz)||(d==raiz->itMe)||(d==raiz->itDe)) return true;
			else
				if(d.Mod()<raiz->itIz.Mod()) return raiz->hijoIz.Buscar(d);
				else 
					if (d.Mod()<raiz->itMe.Mod()) return raiz->hijoMeIz.Buscar(d);
					else
						if(d.Mod()<raiz->itDe.Mod()) return raiz->hijoMeDe.Buscar(d);
						else return raiz->hijoDe.Buscar(d);
		}
		else{
			if(raiz->TresNodo()){ //si es un 3-NODO
				if((d==raiz->itIz)||(d==raiz->itMe)) return true;
				else
					if(d.Mod()<raiz->itIz.Mod()) return raiz->hijoIz.Buscar(d);
					else 
						if (d.Mod()<raiz->itMe.Mod()) return raiz->hijoMeIz.Buscar(d);
						else return raiz->hijoMeDe.Buscar(d);
			}
			else{ //si es un 2-NODO
				if(d==raiz->itIz) return true;
				else
					if(d.Mod()<raiz->itIz.Mod()) return raiz->hijoIz.Buscar(d);
					else return raiz->hijoMeIz.Buscar(d);
			}
		}
	}
}


// funcion  Altura
int
TA234Com::Altura() const{
	if (EsVacio()) return 0;
	else return (1+raiz->hijoIz.Altura());
}


// funcion  Nodos
int
TA234Com::Nodos() const{
	if(EsVacio()) return 0;
	else return (1+raiz->hijoIz.Nodos()+raiz->hijoMeIz.Nodos()+raiz->hijoMeDe.Nodos()+raiz->hijoDe.Nodos());
}


// funcion  NodosHoja
int
TA234Com::NodosHoja() const{
	if(EsVacio()) return 0;
	else{
		if((raiz->hijoIz.EsVacio())&&(raiz->hijoMeIz.EsVacio())&&(raiz->hijoMeDe.EsVacio())&&(raiz->hijoDe.EsVacio())) return 1;
		else return (raiz->hijoIz.NodosHoja()+raiz->hijoMeIz.NodosHoja()+raiz->hijoMeDe.NodosHoja()+raiz->hijoDe.NodosHoja());
	}
}

// funcion Niveles
TListaCom
TA234Com::Niveles(){
	int nodos=Nodos();
	int etiquetas=nodos*3;
	int altura=Altura();
	int j,nivel=1,posicion=0;
	TComplejo vectpreorden[etiquetas];  //me creo un vector con el recorrido preorden del arbol
	int vectniveles[etiquetas];        //y otro con sus respetivos niveles en el arbol
	for(j=0;j<etiquetas;j++) vectniveles[j]=0; //inicializo el vector de niveles a 0    
	NivelesAux(vectpreorden,vectniveles,posicion,nivel);
	//creo la lista con el recorrido en niveles del arbol
	TListaCom niveles;
	TListaPos ultima;
	int i,k;
	for(i=1;i<=altura;i++){
		for(k=0;k<etiquetas;k++){
			if(vectniveles[k]==i){//voy insertando elementos de mayor a menor altura
				if(niveles.EsVacia()) niveles.InsCabeza(vectpreorden[k]);
				else{
					ultima=niveles.Ultima();
					niveles.InsertarD(vectpreorden[k],ultima);
				}
			}
		}
	}
return niveles;
}


// funcion NivelesAux (DEVUELVE EL RECORRIDO PREORDEN CON NIVELES)
void
TA234Com::NivelesAux(TComplejo vector[],int niveles[],int &posicion,int nivel){
	if(!EsVacio()){
		if(raiz->DosNodo()){ //si el nodo raiz es 2-nodo
			vector[posicion]=raiz->itIz;
			niveles[posicion]=nivel;
			posicion++;
		}
		else
			if(raiz->TresNodo()){ //si el nodo raiz es 3-nodo
				vector[posicion]=raiz->itIz;
				niveles[posicion]=nivel;
				posicion++;
				vector[posicion]=raiz->itMe;
				niveles[posicion]=nivel;
				posicion++;
			}
			else{ //si el nodo raiz es 4-nodo
				vector[posicion]=raiz->itIz;
				niveles[posicion]=nivel;
				posicion++;
				vector[posicion]=raiz->itMe;
				niveles[posicion]=nivel;
				posicion++;
				vector[posicion]=raiz->itDe;
				niveles[posicion]=nivel;
				posicion++;
			}
		raiz->hijoIz.NivelesAux(vector,niveles,posicion,nivel+1); //llamada recursiva
		raiz->hijoMeIz.NivelesAux(vector,niveles,posicion,nivel+1); //llamada recursiva
		raiz->hijoMeDe.NivelesAux(vector,niveles,posicion,nivel+1); //llamada recursiva
		raiz->hijoDe.NivelesAux(vector,niveles,posicion,nivel+1); //llamada recursiva
	}
}


// Sobrecarga del Operador =  (asignacion)
TA234Com&
TA234Com::operator=(const TA234Com &a){
	if(*this!=a){        // Comprobamos autoasignacion
		if(!a.EsVacio()){  // si el arbol a copiar no es vacio
			if(!EsVacio()){
				delete raiz;
				raiz=NULL;
			}
			TA234Nodo *aux=new TA234Nodo;
			if(!aux) cerr<<"Error al crear la memoria en TA234Com::TA234Com(const TA234Com &)"<<endl;
			else{
				aux->itIz=a.raiz->itIz;
				aux->itMe=a.raiz->itMe;
				aux->itDe=a.raiz->itDe;
				raiz=aux;
				raiz->hijoIz=a.raiz->hijoIz;
				raiz->hijoMeIz=a.raiz->hijoMeIz;
				raiz->hijoMeDe=a.raiz->hijoMeDe;
				raiz->hijoDe=a.raiz->hijoDe;
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
TA234Com::operator==(const TA234Com &a) const{
	if((raiz==NULL)&&(a.raiz==NULL)) return true;
	else
		if(((raiz==NULL)&&(a.raiz!=NULL))||((raiz!=NULL)&&(a.raiz==NULL))) return false;
		else
			if((raiz->itIz==a.raiz->itIz)&&(raiz->itMe==a.raiz->itMe)&&(raiz->itDe==a.raiz->itDe))
				return ((raiz->hijoIz==a.raiz->hijoIz)&&(raiz->hijoMeIz==a.raiz->hijoMeIz)&&(raiz->hijoMeDe==a.raiz->hijoMeDe)&&(raiz->hijoDe==a.raiz->hijoDe));
			else 
				return false;
}


// Sobrecarga del Operador !=  (desigualdad)
bool
TA234Com::operator!=(const TA234Com &a) const{
	if(*this==a) return false;
	else return true;
}



// METODOS DE LA CLASE TA234Nodo


// Constructor por defecto
TA234Nodo::TA234Nodo(){
}


// Constructor de Copia
TA234Nodo::TA234Nodo(const TA234Nodo &nodo){
	itIz=nodo.itIz;  
	itMe=nodo.itMe;
	itDe=nodo.itDe;
	hijoIz=nodo.hijoIz;
	hijoMeIz=nodo.hijoMeIz;
	hijoMeDe=nodo.hijoMeDe;
	hijoDe=nodo.hijoDe;
}


// Destructor por defecto
TA234Nodo::~TA234Nodo(){
	itIz.~TComplejo();
	itMe.~TComplejo();
	itDe.~TComplejo();
	if(!hijoIz.EsVacio())
		hijoIz.~TA234Com();
	if(!hijoMeIz.EsVacio())
		hijoMeIz.~TA234Com();
	if(!hijoMeDe.EsVacio())
		hijoMeDe.~TA234Com();
	if(!hijoDe.EsVacio())
		hijoDe.~TA234Com();
}


// Sobrecarga del Operador =  (asignacion)
TA234Nodo&
TA234Nodo::operator=(const TA234Nodo &nodo){
	itIz=nodo.itIz;
	itMe=nodo.itMe;
	itDe=nodo.itDe;
	hijoIz=nodo.hijoIz;
	hijoMeIz=nodo.hijoMeIz;
	hijoMeDe=nodo.hijoMeDe;
	hijoDe=nodo.hijoDe;
return *this;
}


// funcion DosNodo (true si el nodo es un 2-nodo)
bool
TA234Nodo::DosNodo() const{
	TComplejo nulo;
	if((itIz!=nulo)&&(itMe==nulo)&&(itDe==nulo)) return true;
	else return false;
}


// funcion TresNodo (true si el nodo es un 3-nodo)
bool
TA234Nodo::TresNodo() const{
	TComplejo nulo;
	if((itIz!=nulo)&&(itMe!=nulo)&&(itDe==nulo)) return true;
	else return false;
}


// funcion CuatroNodo (true si el nodo es un 4-nodo)
bool
TA234Nodo::CuatroNodo() const{
	TComplejo nulo;
	if((itIz!=nulo)&&(itMe!=nulo)&&(itDe!=nulo)) return true;
	else return false;
}


// funcion NodoHoja (true si el nodo es un nodo hoja)
bool
TA234Nodo::NodoHoja() const{
	if((hijoIz.EsVacio())&&(hijoMeIz.EsVacio())&&(hijoMeDe.EsVacio())&&(hijoDe.EsVacio())) return true;
	else return false;
}

