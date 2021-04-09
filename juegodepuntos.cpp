#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

class JUGADOR{
	public:
		char NOM[20];
		int PUNTOS;
		JUGADOR * SIG;
		JUGADOR(char[] , int);
		~JUGADOR();
};


JUGADOR::JUGADOR(char S[], int P)
{
	strcpy(NOM, S);
	PUNTOS=P;	
}

JUGADOR::~JUGADOR()
{
	cout<<"\tA "<<NOM<<" LO ECHARON DEL JUEGO"<<endl;
}


class EXTENSION{
	JUGADOR * PRIMERO;
	public:
		int ANALIZAR(char[] , int );
		void ELIMINAR(JUGADOR *);
		int BUSCAR(char []);
		void AGREGAR(JUGADOR *);
		EXTENSION();
		~EXTENSION();
		
};

int EXTENSION::ANALIZAR(char S[], int P)
{
	JUGADOR * BUSCADOR, * ELIM;
	BUSCADOR = PRIMERO;
	int I=0;
	cout<<"\t\tEL JUGADOR "<<S<<" SACO UN "<<P<<endl;
	
	if(P==8)
	{
		if(!BUSCAR(S))
		{
			JUGADOR * N;
			N = new JUGADOR(S , P);
			AGREGAR(N);
			cout<<"\t\t\t "<<N->NOM<<" SE UNIO AL JUEGO"<<endl;
			return 2;
		}
	}
	BUSCADOR=PRIMERO;
	
	if(P==9)
	{
		while(BUSCADOR)
		{
			if(strcmp(BUSCADOR->NOM , S)==0)
			{
				BUSCADOR->PUNTOS=BUSCADOR->PUNTOS - 5;
				cout<<"\t\t\t\t "<<BUSCADOR->NOM<<" PERDIO 5 PUNTOS AHORA TIENE "<<BUSCADOR->PUNTOS<<" PUNTOS!!!!"<<endl;
				return 5;
			}
			BUSCADOR=BUSCADOR->SIG;
		}
			
	}
	
	BUSCADOR=PRIMERO;
	while(BUSCADOR)
	{
		if(strcmp(BUSCADOR->NOM , S)==0 && P!=9 && P!=1 && P!=0)
		{
			BUSCADOR->PUNTOS=BUSCADOR->PUNTOS + P ;
			cout<<"\t\t\t\t\tAHORA "<<BUSCADOR->NOM<<" TIENE "<<BUSCADOR->PUNTOS<<" PUNTOS!!!!"<<endl;
			if(BUSCADOR->PUNTOS >= 100)
			{
				return 4;
			}
			return 1;
		}
		if(strcmp(BUSCADOR->NOM , S)==0 && P<=1)
			ELIM=BUSCADOR;
		BUSCADOR=BUSCADOR->SIG;
	}
	BUSCADOR=PRIMERO;
	if(P<=1)
	{
		while(BUSCADOR)
		{
			if(strcmp(BUSCADOR->NOM , S)==0)
			{
				cout<<"\t\t\t\t\t\tSE ELIMINARA A "<<ELIM->NOM<<endl;
				ELIMINAR(ELIM);
			}
			BUSCADOR=BUSCADOR->SIG;
		}		
	}

	return 0;
	
}

void EXTENSION::AGREGAR(JUGADOR * N)
{
	JUGADOR * B;
	B=PRIMERO;
	
	if(!PRIMERO)
	{
		PRIMERO=N;
		N->SIG=NULL;
		return;
	}
	
	while(B)
	{
		if(!B->SIG)
		{
			B->SIG=N;
			N->SIG=NULL;
		}
		B=B->SIG;
	} 
}

int EXTENSION::BUSCAR(char S[])
{
	JUGADOR * B;
	B=PRIMERO;
	
	while(B){
		if(strcmp(B->NOM, S)==0)
			return 1;
		B=B->SIG;
	}
	return 0;
}

void EXTENSION::ELIMINAR(JUGADOR * PERDIO)
{
	JUGADOR * BUSC;
	BUSC=PRIMERO;
	
	if(PRIMERO==PERDIO)
	{
		PRIMERO=PERDIO->SIG;
		delete PERDIO;
		return;
	}
	
	while(BUSC->SIG){
		if(BUSC->SIG==PERDIO)
		{
			BUSC->SIG=PERDIO->SIG;
			delete PERDIO;
			return;
		}
		BUSC=BUSC->SIG;
	}
	
}

EXTENSION::EXTENSION()
{
	PRIMERO=NULL;
}

EXTENSION::~EXTENSION()
{
	cout<<"ACA MUEREN TODOS";
}

char * GENERARNOM();

int main()
{
	EXTENSION E;
	int F=1 , P, C;
	char NOM[20];
	int I=0;
	
	while(F==1)
	{
		P=rand()%10;
		strcpy( NOM, GENERARNOM());
		C = E.ANALIZAR(NOM, P);
		
		//cout<<NOM<<" SACO UN "<<P<<endl;
		//cout<<endl<<C<<endl;//MUESTRA LA DESICION DEL E.ANALIZAR;
		switch(C)
		{
			case 0 : break;	//cout<<"NADIE SE UNIO AL JUEGO... "<<NOM<<" TENIA SOLO "<<P<<" PUNTOS";
			case 1 : break;	//cout<<"A "<<NOM<<" SE LE AGREGARON "<<P<<" PUNTOS!!!"<<endl;	
			case 2 : break;	//cout<<NOM<<" SE A UNIDO AL JUEGO!!!"<<endl;break;	
			case 3 : break;	//cout<<"EL JUGADOR "<<NOM<<" PERDIO, FUE RETIRADO DEL JUEGO"<<endl;
			case 4 : F=0;   break; // UNO GANO;
			case 5 : break; //PERDIO 5 PUNHTOS;
				
				
		}// TODO ESTO SE PUEDE REEMPLAZAR POR UN IF(C==4) PERO CON EL SWITCH TE MUESTRA EL CAMINO QUE TOMA;
		if(I==30)
		{
			I=0;
			getchar();
		}
		else
		 	I++;
		
	}
	
	cout<<"FIN DEL PROGRAMA";
}


char * GENERARNOM()
{
	static char NOM[][20]= {"PEPE","LOLA","DANIELA","LAURA",
							"RAMIRO","ROMAN","MANUEL","ELIAS",
							"ANSELMO","MONICA","CAMILA","LUNA"};
	return NOM[rand()%12];
}
