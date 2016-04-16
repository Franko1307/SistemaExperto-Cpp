#pragma once
#include "lista_nodo.hpp"
#include "lista_aux.hpp"

template <typename Type> class sistema_experto{
  lista_nodo<Type> *lista;
  lista_aux<Type> *A;
public:
  sistema_experto();
  ~sistema_experto();
  void agregar_pregunta(Type id) {lista->agregar_pregunta(id);}
  void agregar_conclusion(Type id, bool conectivo) {lista->agregar_conclusion(id,conectivo);}
  void agregar_intermedio(Type id, bool conectivo) {lista->agregar_intermedio(id,conectivo);}
  void conectar(Type a, Type b, bool cambiar) {lista->conectar(a,b,cambiar);}
  void pintar() {lista->pintar();}
  void adivina();
  void decir_respuesta();
  Estado preguntar(Nodo<Type>*);
  void actualizar(Nodo<Type>*, Estado, bool);
  bool procesar(Nodo<Type>*);
  void decir_respuesta_mala();
};

template <typename Type> sistema_experto<Type>::sistema_experto() {
  lista = new lista_nodo<Type>;
  A = new lista_aux<Type>;
}
template <typename Type> sistema_experto<Type>::~sistema_experto() {
  delete lista;
  delete A;
}
template <typename Type> void sistema_experto<Type>::decir_respuesta_mala() {
  Nodo<Type> *n = lista->obtener_primero_c();
  while (n) {
    if (n->tipo == CONCLUSION && n->estado != FALSO) std::cout << n->id_nodo << std::endl;
    n = n->sig;
  }
}
template <typename Type> Estado sistema_experto<Type>::preguntar(Nodo<Type> *n) {
  std::cout << n->id_nodo << std::endl;
  std::cout << "1) SI" << std::endl;
  std::cout << "2) NO" << std::endl;
  std::cout << "3) NO LO SE" << std::endl;
  int resp;
  std::cin >> resp;
  if (resp == 1) n->estado = VERDADERO;
  else if (resp == 2) n->estado = FALSO;
  else n->estado = SINVALOR;
  return n->estado;
}
template <typename Type> void sistema_experto<Type>::decir_respuesta() {
  Nodo<Type> *n = lista->obtener_primero_c();
  while (n->tipo != CONCLUSION || n->estado != VERDADERO )n = n->sig;
  std::cout << "El animal que pensaste es: " << std::endl;
  std::cout << n->id_nodo << std::endl;
}
template <typename Type> void sistema_experto<Type>::adivina() {
  Nodo<Type> *n = lista->obtener_primero();
  Nodo<Type> *no;
  while (n && n->tipo == PREGUNTA) {
    if (n->estado == SINVALOR && n->salientes->es_relevante()) {
      n->estado = preguntar(n);
      if (n->estado != SINVALOR && procesar(n)) return decir_respuesta();
      else
        while (no = A->sacar_primero())
          if (no->salientes->es_relevante())
            if (procesar(no)) return decir_respuesta();
    }
    n = n->sig;
  }
  std::cout << "Parece ser que las respuestas no han llegado a nada" << std::endl;
  std::cout << "Estos son los animales que pueden ser" << std::endl;
  decir_respuesta_mala();
}
template <typename Type> void sistema_experto<Type>::actualizar(Nodo<Type> *n, Estado estado, bool cambiar) {
  if (cambiar)
    if (estado == VERDADERO) estado = FALSO;
    else estado = VERDADERO;

  //Disyuncion 'v'
  if (n->conectivo)
    if (estado == VERDADERO) n->estado = VERDADERO;
    else n->cuantos++;
  else  //conjuncion '^'
    if (estado == VERDADERO) n->cuantos++;
    else n->estado = FALSO;

  if (n->cuantos >= n->total )
    if (n->conectivo) n->estado = FALSO;
    else n->estado = VERDADERO;
}
template <typename Type> bool sistema_experto<Type>::procesar(Nodo<Type> *n) {
  Estado estado = n->estado;
  Arco<Type> *a = n->salientes->obtener_primero();
  while (a) {
    if (a->dir_nodo->estado != SINVALOR) {
      a = a->sig;
      continue;
    }
    actualizar(a->dir_nodo,estado,a->cambiar);
    if (a->dir_nodo->estado == VERDADERO)
      if (a->dir_nodo->tipo == CONCLUSION) return true;
      else A->agregar(a->dir_nodo);
    else if (a->dir_nodo->estado == FALSO) A->agregar(a->dir_nodo);
    a = a->sig;
  }
  return false;
}
