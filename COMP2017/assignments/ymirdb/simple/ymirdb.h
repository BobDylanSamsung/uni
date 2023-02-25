#ifndef YMIRDB_H
#define YMIRDB_H

#define MAX_KEY 16
#define MAX_LINE 1024

#include <stddef.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>


enum item_type {
    INTEGER=0,
    ENTRY=1
};

typedef struct element element_t;
typedef struct entry entry_t;
typedef struct snapshot snapshot_t;
typedef struct database database_t;

struct element {
  enum item_type type;
  union {
    int value;
    entry_t* entry;
  };
	element_t* next;
	element_t* prev;
};

struct entry {
  char key[MAX_KEY];
  bool is_simple;
  element_t * head;
  size_t length;

  entry_t* next;
  entry_t* prev;
  
  size_t forward_size; 
  size_t forward_max; 
  entry** forward;  // this entry depends on these
    
  size_t backward_size; 
  size_t backward_max; 
  entry** backward; // these entries depend on this
};

struct snapshot {
  int id;
  entry_t* head;
  snapshot_t* next;
  snapshot_t* prev;
};

struct database {
	int num_entries;
	entry_t* entry_head;
	snapshot_t* snapshot_head;
};


bool general_dispatch(char* line, database_t* db);
void list_dispatch(char* line, database_t* db);
database_t* init_database();
entry_t* entry_set(char* key, char* values, database_t* db);
element_t* link_elements(char* values, database_t* db);
element_t* link_push(char* values, database_t* db);
void entry_get(entry_t* entry);
bool entry_push(char* key, char* values, database_t* db);
bool entry_append(char* key, char* values, database_t* db);
entry_t* retrieve_key(char* key, database_t* db);
int entry_add(database_t* db, entry_t* entry);
bool entry_pick(char* key, int index, database_t* db);
bool entry_pluck(char* key, int index, database_t* db);
bool entry_pop(char* key, database_t* db);
void command_help();
int num_elements(char* values);
void clear_database(database_t* db);
void remove_entries(database_t* db);
void list_entries(database_t* db);
void list_keys(database_t* db);
int check_valid_key(char* key, database_t* db);
entry_t* entry_delete(char* key, database_t* db);
void find_min(char* key, database_t* db);
void find_max(char* key, database_t* db);
void find_sum(char* key, database_t* db);
void find_length(char* key, database_t* db);
void bubblesort(entry_t* entry);
void entry_uniq(entry_t* entry);
void display_links(entry_t* entry);
void entry_reverse(entry_t* entry);
void save_snapshot(database_t* db);
void list_snapshots(database_t* db);
entry_t* copy_entry(entry_t* entry);
void delete_snapshot_id(database_t* db, int id);
void delete_snapshot(snapshot_t* snap, database_t* db);
void snapshot_checkout(database_t* db, int id);
void snapshot_rollback(database_t* db, int id);
bool is_num(char* str);
bool is_key(char* str);


const char* HELP =
	"BYE   clear database and exit\n"
	"HELP  display this help message\n"
	"\n"
	"LIST KEYS       displays all keys in current state\n"
	"LIST ENTRIES    displays all entries in current state\n"
	"LIST SNAPSHOTS  displays all snapshots in the database\n"
	"\n"
	"GET <key>    displays entry values\n"
	"DEL <key>    deletes entry from current state\n"
	"PURGE <key>  deletes entry from current state and snapshots\n"
	"\n"
	"SET <key> <value ...>     sets entry values\n"
	"PUSH <key> <value ...>    pushes values to the front\n"
	"APPEND <key> <value ...>  appends values to the back\n"
	"\n"
	"PICK <key> <index>   displays value at index\n"
	"PLUCK <key> <index>  displays and removes value at index\n"
	"POP <key>            displays and removes the front value\n"
	"\n"
	"DROP <id>      deletes snapshot\n"
	"ROLLBACK <id>  restores to snapshot and deletes newer snapshots\n"
	"CHECKOUT <id>  replaces current state with a copy of snapshot\n"
	"SNAPSHOT       saves the current state as a snapshot\n"
	"\n"
	"MIN <key>  displays minimum value\n"
	"MAX <key>  displays maximum value\n"
	"SUM <key>  displays sum of values\n"
	"LEN <key>  displays number of values\n"
	"\n"
	"REV <key>   reverses order of values (simple entry only)\n"
	"UNIQ <key>  removes repeated adjacent values (simple entry only)\n"
	"SORT <key>  sorts values in ascending order (simple entry only)\n"
	"\n"
	"FORWARD <key> lists all the forward references of this key\n"
	"BACKWARD <key> lists all the backward references of this key\n"
	"TYPE <key> displays if the entry of this key is simple or general\n";

#endif
