#pragma once

enum Estado { SINVALOR = -1, VERDADERO = 1, FALSO = 0};
enum Tipo { PREGUNTA, INTERMEDIO, CONCLUSION };
#define CONJUNCION false
#define DISYUNCION true

template <typename Type> class lista_arco;

template <typename Type> void eliminar(Type * principio) {
  Type *aux = principio;
  while (principio) {
    aux = principio;
    principio = aux->sig;
    delete aux;
  }
}
template <typename Type, typename T> Type * buscar(Type *x, T b) {
  Type *a = x;
  while (a && *a != b) a = a->sig;
  if (a) return a;
  return NULL;
}
