#pragma once
#include "lista_arco.hpp"

template <typename Type> class lista_nodo {
  Nodo<Type> *principio;
  Nodo<Type> *final;
  Nodo<Type> *principio_c;
  Nodo<Type> *final_c;
public:
  lista_nodo() : principio(NULL), final(NULL), principio_c(NULL), final_c(NULL){}
  ~lista_nodo() {eliminar(principio);}
  void agregar_pregunta(Type);
  void agregar_conclusion(Type,bool);
  void agregar_intermedio(Type, bool);
  void conectar(Type, Type,bool);
  void pintar();
  Nodo<Type> *obtener_primero() {return principio;}
  Nodo<Type> *obtener_primero_c() {return principio_c;}
};
template <typename Type> void lista_nodo<Type>::agregar_intermedio(Type id, bool conectivo) {
  if (buscar(principio_c,id)) return;
  Nodo<Type> *a = new Nodo<Type>(id,INTERMEDIO,conectivo);
  a->salientes = new lista_arco<Type>;

  if (final_c) {
    final_c->sig = a;
    final_c = a;
  } else {
    principio_c = a;
    final_c = a;
    final->sig = principio_c;
  }
}
template <typename Type> void lista_nodo<Type>::agregar_pregunta(Type id) {
  Nodo<Type> *a;
  if (buscar(principio,id)) return;
  a = new Nodo<Type>(id,PREGUNTA,CONJUNCION);
  a->salientes = new lista_arco<Type>;
  if (final) {
    final->sig = a;
    final = a;
    final->sig = principio_c;
  } else {
    principio = a;
    final = a;
    final->sig = principio_c;
  }

}
template <typename Type> void lista_nodo<Type>::agregar_conclusion(Type id, bool conectivo) {
  Nodo<Type> *a;
  if (buscar(principio_c,id)) return;
  a = new Nodo<Type>(id,CONCLUSION, conectivo);
  a->salientes = new lista_arco<Type>;
  if (final_c) {
    final_c->sig = a;
    final_c = a;
  } else {
    principio_c = a;
    final_c = principio_c;
    if (final) final->sig = principio_c;
  }

}
template <typename Type> void lista_nodo<Type>::conectar(Type a, Type b, bool cambiar) {
  Nodo<Type> *n;
  Nodo<Type> *m;
  if ( !(n = buscar(principio,a)) ) return;
  if ( !(m = buscar(principio,b)) ) return;
  n->salientes->agregar(m,cambiar);
  m->total++;
}
template <typename Type> void lista_nodo<Type>::pintar() {
  Nodo<Type> *a = principio;
  while (a) {
    std::cout << a->id_nodo << "("<< a->cuantos << ","<< a->total <<") {"<<a->estado<<"}" << std::endl;
    std::cout << "Salientes: ";
    a->salientes->pintar();
    std::cout << std::endl;
    a = a->sig;
  }
}
