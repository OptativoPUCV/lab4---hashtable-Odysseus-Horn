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

  Pair* par = searchMap(map, key);

  if(par == NULL)
    return;

  int hash_code = hash(key, map->capacity);

  map->current = hash_code;

  
  while(map->current < map->size)
  {
    if(strcmp(map->buckets[map->current]->key, key) == 0)
    {
      map->buckets[map->capacity] = NULL;
      map->size--;
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

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
