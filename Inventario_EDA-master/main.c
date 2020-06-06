/**
 * Compilar:
 * gcc -Wall -std=c99 -o inventario.out main.c stock.c
 * 
 * Ejecutar:
 * ./inventario.out
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "stock.h"

//----------------------------------------------------------------------
//  Programa principal
//----------------------------------------------------------------------

/**
 * @brief Imprime un menu para el usuario
 * 
 * @return int La opcion a elegir del usuario
 */
int menu( void ) {

	//Guarda la opcion del usuario
	int eleccion;
	printf("\n\t\t\t INVENTARIO \n\n");

	printf("\tOPCION:\t\t\t\t\t\tCODIGO:\n\n");
	printf("Salir del programa \t\t\t\t\t 0\n");
	printf("Anadir productos \t\t\t\t\t 1\n");
	printf("Retirar un producto \t\t\t\t\t 2\n");
	printf("Buscar un producto \t\t\t\t\t 3\n");
	printf("Mostrar los productos existentes \t\t\t 4\n");
	printf("Mostrar el producto interno bruto\t\t\t 5\n");
	printf("Ordenar inventario( mediante cantidad ) \t\t 6\n");
	printf("Vaciar el inventario \t\t\t\t\t 7\n");

	printf("\n\nIngrese el codigo de la opcion deseada: "); scanf("%i", &eleccion);

	return eleccion;
}

/**
 * @brief Genera un codigo de barras mediante la suma de numeros aleatorios
 *
 * @return int El codigo de barras generado
 */
int Aleatorio( void ) {

	srand( time( 0 ) );

	//Variable que almacena la suma
      int numero = 0;

	for( size_t i = 0; i < ( 4 + rand() % ( 8 - 4 ) ) ; i++ ) {

		int digito = 100 + rand() % ( 1000 - 100 );
            numero = numero + digito;
	}

      return numero;
}

/**
 * @brief Añade productos al Inventario
 * 
 * @param this Referencia a un objeto Stock
 */
void Add_Inventario( Stock *this ) {

	//Almacena el numero para repetir
	int tam = 0;
    	printf("\nCuantos productos quiere añadir?: "); scanf("%i", &tam );

	//Contador
      size_t i = 0;

      while( i < tam ) {

            fflush(stdin);

		//Variable de un objeto producto
            Producto p;

		//Almacena una cadena
            char nombre[ 32 ];
            printf("\nIngresa el nombre del producto: "); scanf("%s", &nombre );

		//Almacena la cantidad
            int cantidad;
            printf("Ingresa la cantidad de producto: "); scanf("%i", &cantidad );

		//Almacena el codigo de barras
    		int codigo = Aleatorio();
            printf("Su codigo es: %i\n", codigo );

		//Almacena el precio
            float precio;
            printf("Ingresa el precio del producto: "); scanf("%f", &precio );

            p.bar_code = codigo;
            p.precio = precio;
           	strcpy( p.nombre, nombre );

		//Añade el producto al inventario
            Stock_add( this, &p, cantidad );

            i++;
	}
}

/**
 * @brief Retira un producto del Inventario
 * 
 * @param this Referencia a un objeto Stock
 */
void Remove_Inventario( Stock *this ) {

	//Variable para almacenar el codigo de barras
	int codigo = 0;
    	printf("\nIngresa el codigo de barras: "); scanf("%i", &codigo);

	//Si el producto se encuentra, lo retira
      if( Stock_search_by_bar_code( this, codigo ) ) {
		
		//Variable de un objeto producto
            Producto p = Stock_get( this );
            Stock_remove( this, &p );

            printf("Se ha retirado el producto\n\n");
		printf("Producto: %s\n", p.nombre );
      	printf("Codigo de barras: %i\n", p.bar_code );
      	printf("Precio: %.2f\n", p.precio );

      } else {

            printf("\nNo se encuentra el producto en el inventario.\n");
      }
}

/**
 * @brief Busca un producto en el Inventario
 * 
 * @param this Referencia a un objeto Stock
 */
void Search_Inventario( Stock *this ) {

	//Variable para almacenar el codigo de barras
	int codigo = 0;
    	printf("\nIngresa el codigo de barras: "); scanf("%i", &codigo);

      if( Stock_search_by_bar_code( this, codigo ) ) {
		
		//Variable de un objeto producto
      	Producto p = Stock_get( this );
            printf("\nProducto: %s\n", p.nombre );
      	printf("Codigo de barras: %i\n", p.bar_code );
      	printf("El precio es: %.2f\n", p.precio );

      } else {

            printf("\nNo se encuentra el producto en el inventario\n");
      }
}

/**
 * @brief Genera un reporte del Inventario, en la pantalla tanto en un archivo txt
 * 
 * @param this Referencia a un objeto Stock
 */
void Report_Inventario( Stock *this ) {

      if( Stock_report( this ) == true ) {

		printf("Se ha creado un archivo con el nombre \"Inventario\"\n");
		printf("En donde podra ver el reporte.\n");
	} else {

		printf("\nNo hay productos en el inventario para un reporte\n");
	}
}

/**
 * @brief Realiza la suma del valor de los productos almacenados en el Inventario
 * 
 * @param this Referencia a un objeto Stock
 */
void PIB_Inventario( Stock *this ) {

	//Variable para almacenar dinero
	float efectivo = 0;
    	Stock_PIB( this, &efectivo );
      printf("El producto interno bruto es:  $  %.2f \n", efectivo );
}

/**
 * @brief Ordena el Inventario
 * 
 * @param this Referencia a un objeto Stock
 */
void Sort_Inventario( Stock *this ) {

    	Stock_Ordenamiento( this ) ? printf("\nSe ordeno la lista.\n") : 
	    printf("\nLa lista esta vacia, no hay nada que ordenar.\n");
}

/**
 * @brief Vacia el Inventario
 * 
 * @param this 
 */
void MakeEmpty_Inventario( Stock* this ) {

	Stock_MakeEmpty( this );
	printf("\nEl inventario se vacio\n");
}


int main( void ) {

      Stock* stock = Stock_new();

      int opcion;
	do {

		opcion = menu();

		switch( opcion ) {

			case 0: break; //Salir

			case 1: //Añadir

				Add_Inventario( stock );

				break;

			case 2: //Retirar

				Remove_Inventario( stock );

				break;

		 	case 3: //Buscar mediante Codigo de barras

				Search_Inventario( stock );
				
				break;

            	case 4: //Reporte en un archivo

				Report_Inventario( stock );

                 		break;

			case 5: //Producto Interno Bruto

				PIB_Inventario( stock );

				break;

			case 6: //Ordenar

				Sort_Inventario( stock );
				break;

			case 7: //Vaciar inventario

				MakeEmpty_Inventario( stock );

				break;

			default: printf("Opcion incorrecta");
                              
      	}

	} while( opcion != 0 );

	//Destruye al inventario    
      Stock_delete( stock ) ? printf("\nSe elimino el inventario\n") : printf("\nNo se elimino el inventario\n");

      return 0;
}

