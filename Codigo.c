#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct LISTA
{ 
	char *val;
	struct LISTA *sig;
}LISTA;

LISTA* crean(FILE *arch);
LISTA* crear(FILE *arch);
void captura(FILE *arch, LISTA **p2);
void imprime(LISTA  *p2);
int main()
{ 
	LISTA *p2;
	FILE *arch;
	arch=fopen("Rules.txt","r");
	p2=crear(arch);
	captura(arch,&p2);
	imprime(p2);
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
	char cadena[6];
	LISTA *aux=*p2,*nue;
	while(fgets(cadena,sizeof(cadena),arch))
	{	
		nue=crean(arch);
		nue->val=(char*)malloc(sizeof(char)*(6));
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

