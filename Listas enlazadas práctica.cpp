/*   LISTAS SIMPLEMENTE ENLAZADAS  */

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std ;


class NODO
{
	public :
		char NOM[20] ;
		NODO * SIG ;
		NODO(char *) ;
		~NODO() ;
};

NODO::NODO ( char * S )
{
	strcpy ( NOM , S ) ;	
}

NODO::~NODO()
{
	cout << "\n\n\t  MATANDO A ... " << NOM ;
	getchar() ;
}


class LISTA 
{
	private :
		NODO * INICIO ;
		void PONER_P (NODO *);
		void PONER_F (NODO *);
		void INSERT (NODO *);
		NODO * MAXIMO() ;
		NODO * MINIMO() ;
		NODO * BUSCAR ( char *);
		void MATAR (NODO *);
		void SACAR (NODO *);
	public :
		LISTA() ;
		~LISTA() ;
		void AGREGAR_P(char *);
		void AGREGAR_F(char *);
		void INSERTAR(char *);
		void MIRAR() ;
		void MIRARCP() ;
		void RARIM() ;
		void MAYOR() ;
		void MENOR() ;
		int POSICION (char *);
		void ELIMINAR (char *);
		void ORDENAR1() ;
		void ORDENAR2() ;
};


LISTA::LISTA()
{
	INICIO = NULL ;	
}

LISTA::~LISTA()
{
	NODO * P ;
	P = INICIO ;
	while (P)
	{
		delete P;
		P = P->SIG;
	}
	/*  DEBE DESTRUIR TODOS LOS NODOS  */
//	cout << "\n\n\t  DESTRUCTOR DE LA LISTA" ;
//	cout << "\n\n\t  ESTA ES PARA USTEDES ... " ;
	getchar() ;
}

void LISTA::AGREGAR_P ( char * S )
{
	NODO * P ;
	P = new NODO(S) ;

	PONER_P(P);	
}

void LISTA::PONER_P ( NODO * PN )
{
	PN->SIG = INICIO ;
	INICIO = PN ;	
}


void LISTA::AGREGAR_F ( char * S )
{
	NODO * P ;
	P = new NODO(S) ;

	PONER_F(P);	
}

void LISTA::PONER_F ( NODO * PN )
{
	NODO * P ;
	P = INICIO ;

	PN->SIG = NULL ;
	if ( ! INICIO ) 
	{
		/*  LISTA VACIA  */
		INICIO = PN ;
		return ;			
	}
	/*  LISTA NO VACIA  */
	while ( P->SIG )
		P = P->SIG ;/*  LLEVA P AL ULTIMO NODO  */
	P->SIG = PN ;			
}

void LISTA::INSERTAR ( char * S )
{
	NODO * P ;
	P = new NODO(S) ;

	INSERT(P);	
}

void LISTA::INSERT ( NODO * PN )
{
	NODO * P , * ANT ;
	P = INICIO ;
	ANT = NULL ;

	if ( ! INICIO ) 
	{
		/*  LISTA VACIA  */
		PN->SIG = NULL ;   								/* 1 */
		INICIO = PN ;   								/* 2 */
		return ;			
	}
	/*   LISTA NO VACIA   */
	while ( P ) 
	{
		if ( strcmp(P->NOM , PN->NOM) < 0 ) 
		{
			/*  BARRIDO  */
			ANT = P ;
			P = P->SIG ;					
		}
		else 
		{
			/*  EUREKA  */
			if ( ANT ) 
			{
				/*  NODO INTERMEDIO  */
				PN->SIG = P ;  					/* 3 */
				ANT->SIG = PN ;					/* 4 */
				return ;
			}
			/*  NUEVO PRIMER NODO   */
			PN->SIG = INICIO ; 						/* 5 */
			INICIO = PN ; 							/* 6 */
			return ;					
		}  /* else  */			
	} /* while */
	/*   NUEVO ULTIMO NODO   */
	PN->SIG = NULL ;  										/* 7 */
	ANT->SIG = PN ; 										/* 8 */
}


void LISTA::MIRAR()
{
	NODO * P ;
	P = INICIO ;

	cout << "\n\n\n\n\t\t CONTENIDO DE LA LISTA \n\n";
	while ( P ) 
	{
		cout << "\n\n\t\t" << P->NOM ;
		P = P->SIG ;     //    OJO !!!!  NO P++ 			
	}
	getchar() ;	
}

void LISTA::MIRARCP()
{
	NODO * P ;
	P = INICIO ;

	cout << "\n\n\n\n\t\t CONTENIDO DE LA LISTA \n\n";
	while ( P )
	{
		cout << "\n\n\t\t" << P << "\t" << 
			P->NOM << "\t" << P->SIG ;
		P = P->SIG ;     //    OJO !!!!  NO P++ 			
	}
	getchar() ;	
}


void LISTA::RARIM()
{
	int I = 0;

	NODO * P;
	P = INICIO;
	while (P)
	{
		I++;
		P= P->SIG;
	}

	NODO * PP[I];
	P = INICIO;
	I= 0;

	while (P)
	{
		PP[I] = P;
		P = P->SIG;
		I++;					
	}
	cout << "\n\n\n\t\t CONTENIDO INVERSO DE LA LISTA\n\n";
	I=I-1;
	for (I ; I >= 0 ; I--)
	{
		cout << "\n\n\t " << PP[I]->NOM;						
	}

//cout << "\n\n\n\n\t\t CONTENIDO INVERSO DE LA LISTA \n\n";
//	cout << "\n\n\t  ESTA TAMBIEN ES PARA USTEDES ... JE JE " ;
	getchar() ;
}

void LISTA::MAYOR()
{
	NODO * P ;
	P = MAXIMO() ;
	if (P)
		cout << "\n\n  EL MAYOR ES " << P->NOM ;
	getchar();	
}

void LISTA::MENOR()
{
	NODO * P ;
	P = MINIMO() ;
	if (P)
		cout << "\n\n  EL MINIMO ES " << P->NOM ;
	getchar();	
}

NODO * LISTA::MAXIMO()
{
	NODO * P , * PMAX ;
	PMAX = P = INICIO ;

	while (P) 
	{
		if ( strcmp(P->NOM , PMAX->NOM) > 0 )
			PMAX = P ;
		P = P->SIG ;			
	}
	return PMAX ;	
}


NODO * LISTA::MINIMO()
{
	NODO * P , * PMIN ;
	PMIN = P = INICIO ;

	while (P) 
	{
		if ( strcmp(P->NOM , PMIN->NOM) < 0 )
				PMIN = P ;
		P = P->SIG ;			
	}
	return PMIN ;	
}

int LISTA::POSICION ( char * S )
{
	NODO * P;
		
	P = BUSCAR(S);	
	if(P)
	{
		cout <<"\n\n\t\t LA POSICION DE " << P->NOM << " ES " << &P;
		return  0;
	}
	return -1;
	
/*
	RETORNA LA POSICION DEL NODO CON EL NOMBRE S
	RETORNA -1 SI ESTE NO SE ENCUENTRA EN LA LISTA
	UTILIZA LA FUNCION  :  NODO * BUSCAR( char * S )
	ESTA ES OTRA QUE TIENEN QUE HACER USTEDES		
	AH ... Y USARLA EN EL MAIN
*/
}

NODO * LISTA::BUSCAR( char * S)
{
	NODO * P ;
	P = INICIO ; 

	while (P) 
	{
		if ( ! strcmp ( P->NOM , S ))
				return P ;			
		P = P->SIG ;
	}
	return NULL ;	
} 

void LISTA::ELIMINAR ( char * S )
{
	NODO * P ;
	P = BUSCAR(S) ;

	if (P)
		MATAR(P) ;
}

void LISTA::MATAR ( NODO * PELIM )
{
	NODO * P ;
	P = INICIO ;

	if ( !INICIO || !PELIM )
		return ;

	if ( INICIO == PELIM ) {
		/*  MATAR AL PRIMER NODO  */
		INICIO = PELIM->SIG ;
		delete PELIM ;
		return ;
	}
	/*   MATAR OTRO NODO   */
	while ( P->SIG != PELIM && P )
		P = P->SIG ;

	if ( P )
	{
		//    P->SIG = PELIM->SIG ;
		P->SIG = P->SIG->SIG ;
		delete PELIM ;			
	}	
}

void LISTA::SACAR ( NODO * PELIM )
{
	NODO * P ;
	P = INICIO ;

	if ( !INICIO || !PELIM )
		return ;

	if ( INICIO == PELIM ) 
	{
		/*  SACAR AL PRIMER NODO  */
		INICIO = PELIM->SIG ;
		return ;
	}
	/*   SACAR OTRO NODO   */
	while ( P->SIG != PELIM && P )
		P = P->SIG ;

	if ( P ) 
		P->SIG = P->SIG->SIG ;
}

void LISTA::ORDENAR1()
{
	NODO * AUXINI , * P ;
	AUXINI = NULL ;

	while ( INICIO )
	{
		SACAR ( P = MAXIMO() );
		P->SIG = AUXINI ;
		AUXINI = P ;			
	}
	INICIO = AUXINI ;
} 

void LISTA::ORDENAR2()
{
	NODO * P ;
	LISTA AUXL ;

	while ( INICIO )
	{
		SACAR ( P = INICIO );
		AUXL.INSERT(P) ;			
	}
	INICIO = AUXL.INICIO ;
	AUXL.INICIO = NULL ;       //    NO OLVIDAR ESTA !!!!!
} 


char * GENERANOM() ;

int main()
{
	LISTA L ;
	char BUF[20] ;	

	strcpy ( BUF , GENERANOM() );
	while ( strcmp ( BUF , "FIN" ) ) 
	{
		L.AGREGAR_F(BUF) ;
		strcpy ( BUF , GENERANOM() );
	} 

	L.MIRAR() ;		

//	L.RARIM() ;

//	L.MAYOR();
//	L.MENOR();

//	cout << "\n\n   INGRESE EL NOMBRE A ELIMINAR   :   ";
//	cin >> BUF ;

//	L.ELIMINAR(BUF);

	L.ORDENAR2() ;

	L.MIRAR() ;		
	L.RARIM() ;

	cout << "\n\n\t INGRESE UN NOMBRE A BUSCAR A EN LA LISTA\n\t";
	cin >> BUF;
	if ((L.POSICION(BUF)) == -1 )
		cout << "\n\n\t NO SE ENCUENTRA EL NOMBRE";
				
	cout << "\n\n  FIN DEL PROGRAMA   \n";		
	getchar();   
	return 0 ;
}

char * GENERANOM()
{
	static char NOM[][20] = {"PEPE","LOLA","ANA","LAURA",
					  "CAROLINA","EDUARDO","ROBERTO","LORENA",
					  "MARIA","VERONICA","ANSELMO","PEDRO",
					  "ENZO","BETO","DIEGO","LIONEL","FIN"};
	static int I = 0 ;

	return NOM[I++] ;
}



