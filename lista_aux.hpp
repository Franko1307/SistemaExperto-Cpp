#pragma once

template <typename Type> class lista_aux {

  Nodo_aux<Type> *principio;
  Nodo_aux<Type> *final;
public:
  lista_aux() : principio(NULL), final(NULL) {}
  ~lista_aux() {eliminar(principio);}
  void agregar(Nodo<Type>*);
  Nodo<Type> *sacar_primero();
};

template <typename Type> void lista_aux<Type>::agregar(Nodo<Type> *n) {
  if (buscar (principio, n->id_nodo)) return;

  Nodo_aux<Type> *na = new Nodo_aux<Type>(n);

  if (principio) {
    final->sig = na;
    final = na;
  } else {
    principio = na;
    final = principio;
  }

}
template <typename Type> Nodo<Type> *lista_aux<Type>::sacar_primero() {
  if (!principio) {
    return NULL;
  }
  Nodo_aux<Type> *na = principio;
  principio = na->sig;
  Nodo<Type> *n = na->dir_nodo;
  delete na;
  return n;
}
