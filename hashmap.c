#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#include <stdbool.h>


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
  int hash_code = hash(key, map->capacity);
  map->current = hash_code;
  

  Pair *new_pair = createPair(key, value);

  while(map->capacity > map->current)
  {
    if(map->buckets[map->current] == NULL)
    {  
      
      map->buckets[map->current] = new_pair;
      map->size++;
      return;
    }
    else
    {      
      map->current++;
      if(map->current == map->capacity)
        map->current = 0;
    }
  }
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)

  Pair **aux_bucket = map->buckets;
    
  map->capacity *=2;

  map->buckets = malloc(map->capacity * sizeof(Pair**));
  map->size = 0;

  map->current = 0;
  for(int i = map->current ; i < map->capacity/2 ; i++){

    if(!(aux_bucket[i] == NULL))
    {
      insertMap(map, aux_bucket[i]->key, aux_bucket[i]->value);
    }
  }

  return;

}


HashMap * createMap(long capacity) {
    
    HashMap *new_map = (HashMap*) malloc(sizeof(HashMap));
    new_map->buckets = (Pair**) malloc(capacity * sizeof(Pair*));
    new_map->capacity = capacity;
    new_map->size = 0;
    new_map->current = -1;
    
    
    return new_map;
}

void eraseMap(HashMap * map,  char * key) {    

  int hash_code = hash(key, map->capacity);
  map->current = hash_code;

  
  while(map->current < map->capacity)
  {
    if(map->buckets[map->current] != NULL)
    {
      if(strcmp(map->buckets[map->current]->key, key) == 0)
      { 
        free(map->buckets[map->current]); 
        map->buckets[map->current]->key = NULL;
        map->size--;
        return;
      }
    }
    map->current++;
  }
    
  return;

}

Pair * searchMap(HashMap * map,  char * key) {   
  int hash_code = hash(key, map->capacity);
  

  map->current = hash_code;
  for(int i = map->current ; map->current < map->capacity ; i++)  {
    
    if(map->buckets[i] == NULL) return NULL;

    if(strcmp(map->buckets[i]->key, key) == 0) 
      return map->buckets[i];
    
  }
    
  return NULL;
  
}

Pair * firstMap(HashMap * map)
{
    int posicion = 0;

    while(map->buckets[posicion] == NULL || map->buckets[posicion]->key == NULL)
    {
        posicion++;

        if(posicion >= map->capacity)
        {
            return NULL;
        }
    }

    map->current = posicion;
    
    return map->buckets[posicion];
}

Pair * nextMap(HashMap * map) {

  if(map->current == map->capacity) map->current = 0;
  
  for(int i = map->current +1; i < map->capacity - 1 ; i++)
    {
        if(map->buckets[i] != NULL) return map->buckets[i];
    }
  
  return NULL;
  
}
