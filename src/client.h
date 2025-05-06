#include "common.h"


typedef struct {
   int id;
   char* name;
   char* address;
   char* email;
   client next;
   client prev;
} client;