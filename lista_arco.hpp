#pragma once
#include "prototipos.hpp"
#include "estructuras.hpp"
#include <iostream>

template <typename Type> class lista_arco{
  Arco<Type> *principio;
  Arco<Type> *final;
public:
  lista_arco() : principio(NULL){}
  ~lista_arco(){eliminar(principio);}
  void agregar(Nodo<Type> *, bool);
  Arco<Type> *obtener_primero(){return principio;}
  void pintar();
  bool es_relevante();
};
template <typename Type> void lista_arco<Type>::agregar(Nodo<Type> *n, bool cambiar) {
  if (buscar(principio,n->id_nodo)) return;

  Arco<Type> *a = new Arco<Type>(cambiar,n);

  if (final) {
    final->sig = a;
    final = a;
  } else {
    principio = a;
    final = principio;
  }

}
template <typename Type> bool lista_arco<Type>::es_relevante() {
  Arco<Type> *a = principio;
  while (a && a->dir_nodo->estado != SINVALOR) a = a->sig;
  if (a) return true;
  return false;
}
template <typename Type> void lista_arco<Type>::pintar() {
  Arco<Type> *a = principio;
  std::cout << "{  ";
  while (a) {
    std::cout << a->dir_nodo->id_nodo << "["<<a->cambiar<<"], ";
    a = a->sig;
  }
  std::cout << "\b\b  }" << std::endl;
}
