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
void ciclo1 (LISTA *p2);
int main()
{ 
	LISTA *p2;
	FILE *arch;
	arch=fopen("Rules.txt","r");
	if(!arch)
	{
		printf("No se puede abrir el archivo");
		return 1;
	}
	p2=crear(arch);
	captura(arch,&p2);
	imprime(p2);
	paso1 (p2);
	ciclo1(p2);
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
	int i,j;
    LISTA *aux=p2,*corre,*ant;
	char produ[50]="";
//Separa el producto y la produccion
	while(aux!=NULL)
	{
		i=0;
		while(aux->val[i]!='-'&&aux->val[i]!='\0')
		{
			aux->produ[i]=aux->val[i];
			i++;
		}
		aux->produ[i]='\0';
		i+=2;
		j=0;
		while(aux->val[i]!='\0'&&aux->val[i]!='\n')
		{
			aux->produccion[j++]=aux->val[i++];
		}
		aux->produccion[j]='\0';
		aux=aux->sig;
	}
//Junta los que tengan el mismo producto
	aux=p2;
	while(aux!=NULL)
	{
		ant=aux;
		corre=aux->sig;
		while(corre!=NULL)
		{
			if(strcmp(aux->produ,corre->produ)==0)
			{
				strcat(aux->produccion,"|");
				strcat(aux->produccion,corre->produccion);
				ant->sig=corre->sig;
				free(corre->val);
				free(corre);
				corre=ant->sig;
			}
			else
			{
				ant=corre;
				corre=corre->sig;
			}
		}
		aux=aux->sig;
	}
	
	aux=p2;
	while(aux!=NULL)
	{
		printf("%s  %s\n",aux->produ,aux->produccion);
		aux=aux->sig;
	}
}

//Hace el primer ciclo de arriba hacia abajo
void ciclo1 (LISTA *p2)
{
	LISTA *aux=p2,*aux1=p2;
	int i;
	char op;
	while(aux1!=NULL)
	{
		aux=p2;
		while(aux!=NULL)
		{
			i=0;
			while(aux->produccion[i]!='\0')
			{
				if(aux1->produ[0]==aux->produccion[i])
				{
					if(aux->produccion[i+1]=='|')
					{
						op=aux->produccion[i-1];
						strcpy(aux->produccion,"{op}");
						i++;
					}
					else
					{
						op=aux->produccion[i+1];
						strcpy(aux->produccion,"{op}");
						i++;
					}
				}
			}
			aux=aux->sig;
		}
		aux1=aux1->sig;
	}
}



/* 
//Codigo extra que puede servir
//Imprime los productos y produccion por separado
	aux=p2;
	while(aux!=NULL)
	{
		printf("%s  %s",aux->produ,aux->produccion);
		aux=aux->sig;
	}
*/
