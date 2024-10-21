#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct LISTA
{ 
	char *val;
	struct LISTA *sig;
}LISTA;

typedef struct REGLAS
{
	char produ[10];
	char producion[10];
	struct REGLAS *sig;
}REGLAS;

LISTA* crean(FILE *arch);
LISTA* crear(FILE *arch);
void captura(FILE *arch, LISTA **p2);
void imprime(LISTA  *p2);
void ciclo1 (LISTA *p2,REGLAS *p3);
int main()
{ 
	int i;
	LISTA *p2;
	FILE *arch;
	arch=fopen("Rules.txt","r");
	p2=crear(arch);
	captura(arch,&p2);
	REGLAS *p3=(REGLAS*)malloc(sizeof(REGLAS));
	imprime(p2);
	ciclo1 (p2,p3);
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

//Funcion para que separe el producto y la produccion 
void ciclo1 (LISTA *p2,REGLAS *P3)
{
	LISTA *aux=p2;
	int i=0,j=0;
	while(aux!=NULL)
	{
		 i=0;
		while(aux->val[i]!='-'&&aux->val[i]!='\0')
		{
			P3->produ[i]=aux->val[i];
			i++;
		}
		P3->produ[i]='\0';
		printf("%s",P3->produ);
		i=i+2;
		j=0;
		while(aux->val[i]!='\0')
		{
			P3->producion[j]=aux->val[i];
			i++;
			j++;
		}
		P3->producion[j]='\0';
		printf("%s",P3->producion);
		aux=aux->sig;
	}
}