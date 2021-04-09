#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Voto{
    public:
       char nombre [30];
       char sino [3];
       int pos;
       int neg;
       Voto * sig;

       Voto()
       {
           nombre[0]=0;
           sino[0]=0;
           pos=0;
           neg=0;
           sig=0;
       }

       ~Voto()
       {
            cout <<"Eliminando candidato: " <<nombre <<endl;
       }
};
//===============================================================================================================================
class listaVotos{
    private:
       Voto * inicio;

    public:
       listaVotos()
       {
            inicio=0;
       }

       ~listaVotos()
       {
            while(inicio) borrar(inicio);
                cout <<"Eliminando lista..." <<endl;
       }
//-------------------------------------------------------------------------------------------------------------------------------
       void agregar (char * nombre, char * sino)
       {
           Voto * nuevo = new Voto;
           strcpy(nuevo->nombre, nombre);
           strcpy(nuevo->sino, sino);
           strupr(sino);
           
           if(strcmp(sino,"SI")==0) 
               nuevo->pos++;
           if(strcmp(sino,"NO")==0) 
               nuevo->neg++;

           if(inicio==0)
           {
               inicio=nuevo;
               return;
           }

           Voto * aux = inicio;
           
           while(aux->sig!=0)
           {
                aux=aux->sig;
           }
           aux->sig = nuevo;
        }
//-------------------------------------------------------------------------------------------------------------------------------
    int contar ()
    {
       int cont=0;
       Voto * aux = inicio;

       while(aux!=0)
       {
            cont++;
            aux=aux->sig;
       }
       return cont;
    }
//-------------------------------------------------------------------------------------------------------------------------------
    void mirar ()
    {
       if(inicio==0)
       {
            cout <<"Lista vacia" <<endl;
            return;
       }

       Voto * aux = inicio;
       while(aux!=0)
       {
            cout<<"Candidato: "<<aux->nombre <<"  Votos Positivos: " <<aux->pos <<"  Votos Negativos: " <<aux->neg <<endl;
            aux=aux->sig;
       }
    }
//-------------------------------------------------------------------------------------------------------------------------------
    void desenganchar (Voto * cual)
    {
       if(cual == inicio)
       {
           inicio = inicio->sig;
           cual->sig=0;
           return;
       }
       Voto * aux = inicio;
       while(aux->sig != cual)
       { // Busco al anterior al que tengo que sacar
           aux = aux->sig; //El bucle corta cuando en aux me queda la dirección del anterior
       }
       aux->sig = cual->sig;
       cual->sig=0;
    }
//-------------------------------------------------------------------------------------------------------------------------------
    void borrar(Voto * quien){
       if(inicio==0) 
           return;
       if(quien==0)
           return;

       desenganchar(quien);
       delete quien;
    }
//-------------------------------------------------------------------------------------------------------------------------------
    void * buscar(char * quien)
    {
       if(inicio==0)
           return 0;
       Voto * aux = inicio;

       while(aux)
       {
           if(strcmp(aux->nombre,quien)==0) 
               return aux;
           aux=aux->sig;
       }
       return 0; // Si no lo encontró
    }
//-------------------------------------------------------------------------------------------------------------------------------
    void * cuentaVoto(char * quien, char * vot)
    {  
       Voto * aux = inicio;

       while(aux){
           if(strcmp(aux->nombre,quien)==0)
           {
              strupr(vot);
               if(strcmp(vot,"SI")==0) 
                   aux->pos++;
               if(strcmp(vot,"NO")==0) 
                   aux->neg++;
               aux=aux->sig;
           }
           return 0; // Si no lo encontró
       }
    }
//-------------------------------------------------------------------------------------------------------------------------------
    Voto * buscarMinimo (void)
    {
        Voto * minimo = inicio;
        Voto * aux = inicio->sig;

        while(aux!=0)
        {
            if(aux->neg>minimo->neg)
            {
                minimo = aux;
            }
            aux = aux->sig;
        }
        return minimo;
    }
//-------------------------------------------------------------------------------------------------------------------------------
    Voto * buscarMax (void)
    {
        Voto * maxi = inicio;
        Voto * aux = inicio->sig;

        while(aux!=0)
        {
            if(aux->pos>maxi->pos)
            {
                maxi = aux;
            }
            aux = aux->sig;
        }
        return maxi;
    }
//-------------------------------------------------------------------------------------------------------------------------------
    int buscaPor()
    {
       Voto * aux = inicio;
       float cont=0;

       while(aux!=0)
       {
            if(aux->neg>0)
            {
                cont++;
            }
            aux=aux->sig;
       }
       cont=(cont/contar())*100;

       return cont;
     }
};
//===============================================================================================================================

int main()
{
    listaVotos * lv = new listaVotos;
    char nom[30];
    char vot[3];

    cout<<"Ingrese el candidato e indique SI o NO, ingrese Fin para salir \n" <<endl;
    cin.getline(nom,30);
    strupr(nom);

    while(strcmp(nom,"FIN")!=0)
    {
        if(lv->buscar(nom)==0)
        {
            cin.getline(vot,3);
            lv->agregar(nom,vot);
            cout<<"Ingrese el candidato e indique SI o NO, ingrese Fin para salir \n" <<endl;
            cin.getline(nom,30);
            strupr(nom);
        }
        else
        {
            cin.getline(vot,3);
            lv->cuentaVoto(nom,vot);
            cout<<"Ingrese el candidato e indique SI o NO, ingrese Fin para salir \n" <<endl;
            cin.getline(nom,30);
            strupr(nom);
         }
    }

    system("cls");

    lv->mirar();
    cout<<"\n Hay " <<lv->contar() <<" Candidatos" <<endl;
    cout<<"\n El idolo popular es: " <<lv->buscarMax()->nombre <<endl;
    cout<<"\n El Salvavidas de plomo es: " <<lv->buscarMinimo()->nombre <<endl;
    cout<<"\n El porcentaje de gente con votos negativos es: " <<lv->buscaPor() <<" porciento";
}
