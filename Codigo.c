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
int trans(LISTA *aux);
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
	LISTA *aux=p2;
	char pal[50],pal1 [50];
	char  l[0];
	while(aux!=NULL)
	{
		for(int i=0;aux->produccion[i]!='\0';i++)
		{
			if(aux->produccion[i]==aux->produ[0])
			{
				if(aux->produccion[i+1]!='|')
				{
					for(int j=0;aux->produccion[j]!='\0';j++)
					{
						pal[j]=aux->produccion[i+j];
					}
					for(int k=0;k<i-1;k++)
					{
						pal1[k]=aux->produccion[k];
					}
					l[0]=aux->produccion[i+1];
					l[1]='\0';
					strcat(aux->produccion,pal);
					strcat(aux->produccion,"{");
					strcat(aux->produccion,l);
					strcat(aux->produccion,"}");
					strcat(aux->produccion,pal1);
				}
				else
				{
					for(int j=1;aux->produccion[j]!='\0';j++)
					{
						pal[j]=aux->produccion[i+j];
					}
					for(int k=0;k<i;k++)
					{
						pal1[k]=aux->produccion[k];
					}
					l[0]=aux->produccion[i-1];
					l[1]='\0';
					strcat(aux->produccion,pal);
					strcat(aux->produccion,"{");
					strcat(aux->produccion,l);
					strcat(aux->produccion,"}");
					strcat(aux->produccion,pal1);
				}
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


/* 
//Codigo extra que puede servir
//Imprime los productos y produccion por separado
	aux=p2;
	while(aux!=NULL)
	{
		printf("%s  %s",aux->produ,aux->produccion);
		aux=aux->sig;
	}

//Funcion no funcional con str
char *pos,cadena[100],cadena2[100],*pr;
	pos=strstr(aux->produccion,aux->produ);
	  if (pos != NULL) {
        // Guardar la parte de la cadena antes de la subcadena
        strncpy(cadena, aux->produccion, pos - aux->produccion);
        cadena[pos - aux->produccion] = '\0'; // Asegúrate de terminar la cadena

        // Copiar la parte después de la subcadena
        strcpy(cadena2, pos + strlen(aux->produ)); // +strlen para saltar la subcadena

        // Formar la nueva cadena
        strcpy(aux->produccion, "{");
        strcat(aux->produccion, cadena);
        strcat(aux->produccion, "}");
        strcat(aux->produccion, cadena2);
        return 1;
    }
    return 0;
*/
