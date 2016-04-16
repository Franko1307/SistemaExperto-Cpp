#pragma once
#include "prototipos.hpp"
template <typename Type> class Nodo{
public:
  Type id_nodo;
  Estado estado;
  size_t cuantos;
  size_t total;
  bool conectivo;
  Nodo<Type> *sig;
  Nodo<Type> *ant;
  Tipo tipo;
  lista_arco<Type> *salientes;
  Nodo(Type id_nodo, Tipo tipo, bool conectivo):
    id_nodo(id_nodo),
    estado(SINVALOR),
    tipo(tipo),
    conectivo(conectivo),
    sig(NULL),
    ant(NULL){}
  bool operator != (Type x) {
    if (id_nodo != x) return true;
    return false;
  }

};
template <typename Type> class Arco {
public:
  bool cambiar;
  Nodo<Type> *dir_nodo;
  Arco<Type> *sig;
  Arco<Type> *ant;
  lista_arco<Type> *salientes;
  Arco(bool cambiar, Nodo<Type> *dir_nodo) : cambiar(cambiar), dir_nodo(dir_nodo), sig(NULL), ant(NULL){}
  bool operator != (Type x) {
    if (dir_nodo->id_nodo != x) return true;
    return false;
  }
};
template <typename Type> class Nodo_aux {
public:
  Nodo<Type> *dir_nodo;
  Nodo_aux<Type> *sig;
  Nodo_aux(Nodo<Type> *dir_nodo) : dir_nodo(dir_nodo), sig(NULL) {}
  bool operator != (Type x) {
    if (dir_nodo->id_nodo != x) return true;
    return false;
  }
};
