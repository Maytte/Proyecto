#ifndef STOCK_INC
#define STOCK_INC

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

//----------------------------------------------------------------------
//  Producto
//----------------------------------------------------------------------

typedef struct Producto{

      int bar_code;
      float precio;
      char nombre[32];
      // ... quizás más campos
} Producto;

// Los productos NO tienen operaciones, accesaremos directamente a los campos

//----------------------------------------------------------------------
//  Lista doblemente enlazada
//----------------------------------------------------------------------

typedef struct Node {

      Producto item;
      size_t cantidad;

      struct Node* prev;
      struct Node* next;
} Node;


typedef struct DLL {

      Node* first;
      Node* last;
      Node* cursor;
      size_t len;
} DLL;

/**
 * @brief Crea una lista
 * 
 * @return DLL* Una referencia a la lista
 */
DLL* DLL_New();

/**
 * @brief Elimina la lista
 * 
 * @param this Referencia a un objeto DLL
 * @return true Elimino la lista, false No se elimino la lista
 */
bool DLL_Delete( DLL** this );

/**
 * @brief Inserta un objeto producto
 * 
 * @param this Referencia a un objeto DLL
 * @param p Referencia a un objeto Producto
 * @param cant Cantidad de elementos del producto
 */
void DLL_InsertBack( DLL* this, Producto* p, size_t cant );

/**
 * @brief Retira un producto del inventario, en el caso de su cantidad ser 0 elimina el producto completamente 
 * 
 * @param this Referencia a un objeto DLL
 * @return Producto Referencia a un objeto Producto
 */
Producto DLL_Remove( DLL* this );

/**
 * @brief Busca un Producto en la lista
 * 
 * @param this Referencia a un objeto DLL
 * @param bar_code Codigo de barras del producto
 * @return true Encontro el producto, false No encontro el producto
 */
bool DLL_Search( DLL* this, int bar_code );

/**
 * @brief Realiza una copia de un producto
 * 
 * @param this Referencia a un objeto DLL
 * @return Producto Regresa un producto
 */
Producto DLL_Peek( DLL* this );

/**
 * @brief Imprime el reporte de los productos de la lista en un archivo txt
 * 
 * @param this Referencia a un objeto DLL
 * @return true Se realizo el reporte, false No se realizao el reporte
 */
bool DLL_Print( DLL* this );

/**
 * @brief Elimina los nodos de la lista
 * 
 * @param this Referencia a un objeto DLL
 */
void DLL_MakeEmpty( DLL* this );

/**
 * @brief Realiza la suma del valor de los productos almacenados en la lista
 * 
 * @param this Referencia a un objeto DLL
 * @param ganan Variable puntero en donde se almacena la suma
 */
void DLL_PIB( DLL* this, float* ganan );

/**
 * @brief Ordena la lista segun la cantidad de los productos
 * 
 * @param this Referencia a un objeto DLL
 * @param primero Referencia a un objeto Nodo
 * @param ultimo Referencia a un objeto Nodo
 */
void DLL_QuickSort( DLL* this, Node* primero, Node* ultimo );

//----------------------------------------------------------------------
//  Inventario
//----------------------------------------------------------------------

typedef struct Stock {

      DLL* list;
} Stock; // <- Stock es más corto que Inventario

/**
 * @brief Crea un Inventario
 * 
 * @return Devuelve una variable Stock* 
 */
Stock* Stock_new();

/**
 * @brief Elimina el Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @return true Si se elimino el inventario, false No se elimino el inventario
 */
bool Stock_delete( Stock* this );

/**
 * @brief Añade un producto a el Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @param p Referencia a un objeto Producto
 * @param cant Cantidad a añadir
 */
void Stock_add( Stock* this, Producto* p, size_t cant );

/**
 * @brief Retira un producto del Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @param p Referencia a un objeto Producto
 */
void Stock_remove( Stock* this, Producto* p );

/**
 * @brief Busca un producto en el Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @param p Referencia a un objeto Producto
 * @return true Encontro el producto, false No encontro el producto
 */
bool Stock_search( Stock* this, Producto* p );

/**
 * @brief Busca un producto en el inventario mediante su codigo de barras.
 * 
 * @param this Referencia a un objeto Stock
 * @param bar_code Codigo de barras del producto
 * @return true Encontro el producto, false No encontro el producto
 */
bool Stock_search_by_bar_code( Stock* this, int bar_code );

/**
 * @brief Obtiene una copia de un producto
 * 
 * @param this Referencia a un objeto Stock
 * @return Producto Regresa un producto
 */
Producto Stock_get( Stock* this );

/**
 * @brief Realiza un reporte de los productos que se encuntran en el inventario
 * 
 * @param this Referencia a un objeto Stock
 * @return true Se hizo el reporte, false No se hizo el reporte
 */
bool Stock_report( Stock* this );

/**
 * @brief Elimina todos los productos del inventario
 * 
 * @param this Referencia a un objeto Stock
 */
void Stock_MakeEmpty( Stock* this );

/**
 * @brief Realiza la suma del valor de los productos almacenados en el Inventario
 * 
 * @param this Referencia a un objeto Stock
 * @param dinero Variable puntero en donde se almacena la suma
 */
void Stock_PIB( Stock* this, float *dinero );

/**
 * @brief Ordena los productos del inventario acorde a su cantidad
 * 
 * @param this Referencia a un objeto Stock
 * @return true El inventario se ordeno, false El inventario no se ordeno
 */
bool Stock_Ordenamiento( Stock* this );


#endif   /* ----- #ifndef STOCK_INC  ----- */