#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct LISTA
{ 
	char *val;
	char produ [50];
	char produccion [50];
	struct LISTA *sig;
}LISTA;



LISTA* crean(FILE *arch);
LISTA* crear(FILE *arch);
void captura(FILE *arch, LISTA **p2);
void imprime(LISTA  *p2);
void paso1 (LISTA *p2);
int main()
{ 
	LISTA *p2;
	FILE *arch;
	arch=fopen("Rules.txt","r");
	p2=crear(arch);
	captura(arch,&p2);
	imprime(p2);
	paso1 (p2);
	fclose(arch);
}    

//Crea el nodo
LISTA * crean(FILE *arch)
{
	LISTA *p;
	p=(LISTA*)malloc(sizeof(LISTA));
	if(p)
	{
		p->val=(char*)malloc(sizeof(char)*300);
			if(p->val)
			{
				p->val[0]='\0';
			}
		p->sig=NULL;
	}
	return(p);
}
//Funcion de crea lista
LISTA* crear(FILE *arch)
{
	LISTA *p1;
	p1=crean(arch);
	return(p1);
}

//Funcion captura por linea en un nodo differente
void captura(FILE *arch, LISTA **p2)
{
	char cadena[100];
	LISTA *aux=*p2,*nue;
	while(fgets(cadena,sizeof(cadena),arch))
	{	
		nue=crean(arch);
		nue->val=(char*)malloc(sizeof(char)*(50));
		strcpy(nue->val,cadena);
		if(aux!=NULL)
		{
		aux->sig=nue;
		aux=nue;
		}
		else
		{
			*p2=nue;
			aux=nue;	
		}
	}
}

//Funcion de imprimir
void imprime(LISTA  *p2)
{
	LISTA *aux=p2;
	while(aux!= NULL)
	{
		printf("%s",aux->val);
		aux=aux->sig;
	}
}

// Función para que separe el producto y la produccion
void paso1(LISTA *p2)
{
	int i=0,j;
    LISTA *aux=p2;
	while(aux!=NULL)
	{
		i=0;
		j=0;
		while(aux->val[i]!='-')
		{
			aux->produ[i]=aux->val[i];
		}
		i+=2;
		while(aux->val[i]!='\0')
		{
			aux->produccion[j]=aux->val[i];
		}
		aux=aux->sig;
	}
	aux=p2;
	while(aux!=NULL)
	{
		printf(" %s  %s",aux->produ,aux->produccion);
		aux=aux->sig;
	}
}
