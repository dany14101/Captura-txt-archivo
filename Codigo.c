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
	char produ[50];
	char producion[50];
	struct REGLAS *sig;
}REGLAS;

LISTA* crean(FILE *arch);
LISTA* crear(FILE *arch);
void captura(FILE *arch, LISTA **p2);
int imprime(LISTA  *p2);
void paso1 (LISTA *p2,REGLAS *p3,int k);
int main()
{ 
	int i;
	LISTA *p2;
	FILE *arch;
	arch=fopen("Rules.txt","r");
	p2=crear(arch);
	captura(arch,&p2);
	i=imprime(p2);
	REGLAS *p3=(REGLAS*)malloc(sizeof(REGLAS)*i);
	paso1 (p2,p3,i);
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
int imprime(LISTA  *p2)
{
	int k=0;
	LISTA *aux=p2;
	while(aux!= NULL)
	{
		printf("%s",aux->val);
		aux=aux->sig;
		k++;
	}
	return(k);
}

// Función para que separe el producto y la produccion
void paso1(LISTA *p2, REGLAS *P3, int k)
{
    LISTA *aux = p2;
    REGLAS *corre = P3;
    int i = 0, j = 0;
    
    printf("\n");
    
    // Separar producto y producción de cada nodo de LISTA
    while (aux != NULL)
    {
        i = 0;
        // Copiar producto hasta el '-'
        while (aux->val[i] != '-' && aux->val[i] != '\0')
        {
            corre->produ[i] = aux->val[i];
            i++;
        }
        corre->produ[i] = '\0'; // Fin de cadena para 'produ'
        
        // Mostrar producto
        printf("%s", corre->produ);
        
        // Saltar el "->"
        i = i + 2;
        j = 0;
        
        // Copiar la producción después del "->"
        while (aux->val[i] != '\0')
        {
            corre->producion[j] = aux->val[i];
            i++;
            j++;
        }
        corre->producion[j] = '\0'; // Fin de cadena para 'producion'
        
        // Mostrar producción
        printf("%s", corre->producion);
        
        aux = aux->sig;
        corre++; // Avanzar al siguiente nodo de REGLAS
    }
    
    // Unir productos iguales en un solo nodo con la producción concatenada
    corre = P3;
    while (corre != NULL && corre->sig != NULL) // Comprobar que corre->sig no sea NULL
    {
        if (strcmp(corre->produ, corre->sig->produ) == 0)
        {
            strcat(corre->producion, "|");
            strcat(corre->producion, corre->sig->producion);
            corre->sig = corre->sig->sig;
        }
        else
        {
            corre = corre->sig;
        }
    }
    
    // Imprimir la lista final de REGLAS
    corre = P3;
    while (corre != NULL)
    {
        printf("%s -> %s\n", corre->produ, corre->producion);
        corre++;
    }
}
