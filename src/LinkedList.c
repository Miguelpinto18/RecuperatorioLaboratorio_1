#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*) malloc(sizeof(LinkedList));

    if(this != NULL)
    {
    	this->size = 0;
    	this->pFirstNode = NULL;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this!= NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    int i;

    if(this != NULL && nodeIndex > -1 && nodeIndex < ll_len(this))
    {
    	pNode = this->pFirstNode;
    	for(i=0; i<nodeIndex; i++)
    	{
    		pNode = pNode->pNextNode;
    	}
    }

	return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNodeAnterior = NULL;
    int len = ll_len(this);
    Node* pNode = (Node*)malloc(sizeof(Node));

    if(this != NULL && pNode != NULL)
    {
    	if(nodeIndex == 0)
    	{
    		pNode->pNextNode = this->pFirstNode; //en el nuevo nodo cargo el primer nodo que ya existia (evitar perdida de info)
    		this->pFirstNode = pNode; //el primer nodo va a apuntar al nuevo nodo
        	pNode->pElement = pElement;
    		this->size++;
    		returnAux = 0;
    	}
    	else if(nodeIndex >0 && nodeIndex < len)
    	{
    		pNodeAnterior = getNode(this, nodeIndex-1); //obtengo el nodo anterior
    		pNode->pNextNode = pNodeAnterior->pNextNode; //cargo el nodo anterior en el nuevo nodo para no perder info
    		pNodeAnterior->pNextNode = pNode; // el nodo anterior ahora apunta al nuevo nodo que se agrego en el medio
        	pNode->pElement = pElement;
    		this->size++;
    		returnAux = 0;
    	}
    	else if(nodeIndex == len) //agrega al final
    	{
    		pNodeAnterior = getNode(this, nodeIndex-1);
    		pNodeAnterior->pNextNode = pNode;
    		pNode->pNextNode = NULL; //null porque el nuevo nodo es el ultimo
        	pNode->pElement = pElement;
    		this->size++;
    		returnAux = 0;
    	}

    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this != NULL)
    {
    	addNode(this, len, pElement);
    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Permite traer un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    int len = ll_len(this);
    Node* pNode = (Node*)malloc(sizeof(Node));

    if(this != NULL && index > -1 && index < len)
    {
    	pNode = getNode(this, index);
    	returnAux = pNode->pElement;
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);
    Node* pNode = NULL;

    if(this != NULL && index > -1 && index < len)
    {
    	pNode = getNode(this, index);
    	pNode->pElement = pElement;
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int len = ll_len(this);
    Node* pNode = (Node*)malloc(sizeof(Node));
    Node* pNodeAnterior = NULL;

    if(this != NULL && index > -1 && index < len)
    {
    	if(index == 0)
    	{
    		pNode = this->pFirstNode;
    		this->pFirstNode = pNode->pNextNode;
    	}
    	else
    	{
			if(index > -1 && index < len)
			{
				pNodeAnterior = getNode(this, index-1);
				pNode = pNodeAnterior->pNextNode;
				pNodeAnterior->pNextNode = pNode->pNextNode;
			}
    		else
    		{
				pNodeAnterior = getNode(this, index-1);
				pNodeAnterior->pNextNode = NULL;
    		}
    	}

		this->size--;
		free(pNode);
		pNode = NULL;
		returnAux = 0;

    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int len = ll_len(this);
    int i;

    if(this != NULL)
    {
    	for(i = len; i>-1; i--)
    	{
    		ll_remove(this, i);
    	}
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	ll_clear(this);
    	free(this);
    	this = NULL;
    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    int len = ll_len(this);

    if(this != NULL)
    {
    	for(i=0; i<len; i++)
    	{
    		if(pElement == ll_get(this, i))
    		{
    			returnAux = i;
    			break;
    		}
    	}
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this != NULL)
    {
    	if(len == 0)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this != NULL && index > -1 && index < len+1)
    {
    	if(!addNode(this, index, pElement))
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    int len = ll_len(this);
    void* elementoEnLista = NULL;

    if(this != NULL && index > -1 && index < len)
    {
    	elementoEnLista = ll_get(this, index);

    	if(!ll_remove(this, index))
    	{
    		returnAux = elementoEnLista;
    	}
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{

    int returnAux = -1;
    int index;

    if(this!= NULL)
    {
    	index = ll_indexOf(this, pElement);

    	if(index == -1)
    	{
    		returnAux = 0;
    	}
    	else
    	{
    		returnAux = 1;
    	}
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{

    int returnAux = -1;
    int len2 = ll_len(this2);
    void* elementoListaDos;

    if(this!=NULL && this2!=NULL)
    {
    	returnAux = 1;

    	for(int i = 0;i<len2;i++)
    	{
    		elementoListaDos = ll_get(this2, i);

    		if(ll_contains(this, elementoListaDos) == 0) //si no esta el elemento
    		{
    			returnAux = 0;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int len = ll_len(this);
    void* pElement;
    int i;


    if(this != NULL && from >-1 && to < len+1 && from < to)
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
    	{
        	for(i = from; i<to; i++)
        	{
        		pElement = ll_get(this, i);
        		ll_add(cloneArray, pElement);
        	}
    	}
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int len = ll_len(this);

    if(this != NULL)
    {
    	cloneArray = ll_subList(this, 0, len);
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* pElementoA = NULL;
    void* pElementoB = NULL;
    void* auxElemento = NULL;
    int flagSwap;
    int i;
    int j;
    int len;



    if(this != NULL && pFunc != NULL && (order == 0 || order ==1))
    {
    	len = ll_len(this);

    	for(i=0; i<len-1; i++)
    	{
    		pElementoA = ll_get(this, i);

    		for(j=i+1; j<len; j++)
    		{
    			pElementoB = ll_get(this, j);

    			flagSwap = pFunc(pElementoA, pElementoB);

    			if(order == 0)
    			{
    				if(flagSwap == -1)
    				{
    					auxElemento = pElementoA;
    					pElementoA = pElementoB;
    					pElementoB = auxElemento;
    				}
    			}
    			else
    			{
    				if(flagSwap == 1)
    				{
    					auxElemento = pElementoB;
    					pElementoB = pElementoA;
    					pElementoA = auxElemento;
    				}
    			}
    			ll_set(this, i, pElementoA);
    			ll_set(this, j, pElementoB);
    			returnAux = 0;
    		}
    	}
    }

    return returnAux;

}

