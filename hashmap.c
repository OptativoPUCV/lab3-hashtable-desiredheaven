#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {

  long indice = hash(key, map->capacity);
  long aux = indice;
  while (1)
  {
   Pair* dato = map->buckets[indice];
    if (dato == NULL || dato->key == NULL)
    {
      Pair* nuevo = createPair(key,value);
      map->buckets[indice]= nuevo;
      map->size++;
      map->current = indice;

      return;

    }
    indice = (indice +1)%map->capacity;
    if (indice == aux)
    {
      return;
    }
  }
  
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
}


HashMap * createMap(long capacity) {
  HashMap * Map = (HashMap*)malloc(sizeof(HashMap));
  Map ->size = 0;
  Map->capacity = capacity;
  Map->current = -1;
  Map -> buckets = (Pair**)malloc(sizeof(Pair*)*capacity);

  return Map;
}

void eraseMap(HashMap * map,  char * key) {

  long indice = hash(key, map->capacity);
  long aux = indice;
  while (1)
  {
   Pair* dato = map->buckets[indice];
    if (dato != NULL && strcmp(key,dato->key)==0)
    {
      map->buckets[indice]->key = NULL;
      map->size--;
      map->current = indice;

      return;
    }
        indice = (indice +1)%map->capacity;
    if (indice == aux)
    {
      return;
    }
  }
}


Pair * searchMap(HashMap * map,  char * key) { 

  long indice = hash(key, map->capacity);
  while (1)
    {
    Pair* dato = map->buckets[indice];
    if (dato != NULL && strcmp(key,dato->key)==0)
    {
      map->current = indice;
      return map->buckets[indice];
    }
            indice = (indice +1)%map->capacity;
      if (dato == NULL)
      {
        return NULL;
      }
    

}

}

Pair * firstMap(HashMap * map) {
  for(int i =0; i < map->capacity; i++)
    {
      if ((map->buckets[i]) != NULL && map->buckets != NULL)
        {
          map->current = i;
          return map->buckets[i]
        }
    }

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
