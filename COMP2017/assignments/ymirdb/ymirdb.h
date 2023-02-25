#ifndef YMIRDB_H
#define YMIRDB_H

/////////////////////////////////////////////
//MACROS
/////////////////////////////////////////////
#define MAX_KEY 16
#define MAX_LINE 1024


/////////////////////////////////////////////
//FILE LINKING
/////////////////////////////////////////////
#include <stddef.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>


/////////////////////////////////////////////
//ENUMS AND TYPEDEFS
/////////////////////////////////////////////
enum item_type {
    INTEGER=0,
    ENTRY=1
};

typedef struct element element_t;
typedef struct entry entry_t;
typedef struct snapshot snapshot_t;
typedef struct database database_t;
typedef struct key_list key_list_t;


/////////////////////////////////////////////
//STRUCTS
/////////////////////////////////////////////
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
  //size_t forward_max; 
  entry_t** forward;  // this entry depends on these
    
  size_t backward_size; 
  //size_t backward_max; 
  entry_t** backward; // these entries depend on this
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

struct key_list {
  char key[MAX_KEY];
  key_list_t* next;
  key_list_t* prev;
  bool is_empty;
};

/////////////////////////////////////////////
//GLOBALS
/////////////////////////////////////////////
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

/////////////////////////////////////////////
//FUNCTION DEFINITIONS
/////////////////////////////////////////////

/*
 *init_database
 *initialises a database
 *
 *returns new database
 */
database_t* init_database();


/*
 *general_dispatch
 *takes user input in line taken from stdin and calls function
 *
 *char* line:: user input taken from stdin
 *database_t* db:: main db struct passed around code
 *
 *returns bool which determines if main loop continues execution
 *
 */
bool general_dispatch(char* line, database_t* db);


/*
 *list_dispatch
 *calls one of the 3 list functions: keys, entries or snapshots
 *
 *char* line:: modified user input signalling which func to call
 *database_t* db:: main db
 *
 *returns nothing 
 */
void list_dispatch(char* line, database_t* db);

/*
 *list_keys
 *lists the keys present in the database
 *
 *database_t* db database to list keys in
 *
 *returns nothing
 */
void list_keys(database_t* db);


/*
 *list_entries
 *lists the keys and the entries for each present in the database
 *
 *database_t* db database to list entries in
 *
 *returns nothing
 */
void list_entries(database_t* db);


/*
 *list_snapshots
 *lists the snpashot ids for each present in the database
 *
 *database_t* db database to list sanpshots in
 *
 *returns nothing
 */
void list_snapshots(database_t* db);


/*
 *entry_get
 *displays the contents of an entry in the format [...]
 *
 *entry_t* entry:: entry to list contents of
 *
 *returns nothing
 */
void entry_get(entry_t* entry);


/*
 *entry_set
 *sets an entry based on string of values
 *
 *char* key:: name of the entry
 *char* values:: string of values of the entry
 *database_t* db:: database to add entry to
 *
 *returns the new entry
 */
entry_t* entry_set(char* key, char* values, database_t* db);


/*
 *check_values
 *checks if a string of values contains either characters or known keys
 *
 *char* values:: string to check
 *
 *returns true if valid otherwise false
 */
bool check_values(char* values, database_t* db);


/*
 *check_valid_key
 *checks if a given key is valid
 *
 *char* key:: key to check
 *database_t* db:: database to check for key
 *
 *returns:
 *    0 if the key is valid and does not exist in the db
 *    1 if the key is valid and already exists in the db
 *    2 if the key is not valid
 */
int check_valid_key(char* key, database_t* db);


/*
 *is_num
 *checks if a given string is a number (contains only digits)
 *
 *char* str:: string to check
 *
 *returns true if the string is a number otherwise false
 */
bool is_num(char* str);


/*
 *is_key
 *checks if a given string is a valid key
 *    starts with a letter and then alphanumerics
 *
 *char* str:: string to check
 *
 *returns true if the string is a valid key otherwise false
 */
bool is_key(char* str);


/*
 *retrieve_key
 *gets an entry with a specific key from the database
 *
 *char* key:: key of the entry to retrieve
 *database_t* db:: database to extract entry from
 *
 *returns the entry if the key exists in the db otherwise NULL
 */
entry_t* retrieve_key(char* key, database_t* db);


/*
 *link_elements
 *links the values and adds them to the end of entry
 *
 *char* values:: string of elements to link
 *entry_t* entry:: entry to add elements to
 *
 *returns true if successfully completed, otherwise false
 */
bool link_elements(char* values, entry_t* entry, database_t* db);


/*
 *entry_add
 *adds entry to database
 *
 *database_t* db:: database to add to
 *entry_t* entry:: entry to add
 *
 *returns number of items in the database
 */
int entry_add(database_t* db, entry_t* entry);


/*
 *add_reference
 *links reference as forward of original and original as backward of reference
 *
 *entry_t* original:: entry holding the reference as an element
 *entry_t* reference:: element of original entry
 *
 *returns nothing
 */
void add_reference(entry_t* original, entry_t* reference);


/*
 *list_forward
 *lists the forward references of an entry
 *
 *entry_t* entry:: entry to list forward references of
 *
 *returns nothing
 */
void list_forward(entry_t* entry);


/*
 *list_forward_keys
 *recursively finds unique keys for entry and forward references
 *
 *entry_t* entry:: entry to list keys of
 *
 *returns a key_list struct containing array of keys and size of array
 */
key_list_t* list_forward_keys(entry_t* entry);


/*
 *sort_keys
 *bubble sorts an array of pointers to keys
 *called by list_forward and list_backward
 *
 *key_list_t* key_list:: list of keys to sort
 *
 *returns nothing
 */
void sort_keys(key_list_t* key_list);


/*
 *clear_keys
 *frees the allocated memory for a key list
 *
 *key_list_t* head:: head of the list to free
 *
 *returns nothing
 */
void clear_keys(key_list_t* head);


/*
 *list_backward
 *lists the backward references of an entry
 *
 *entry_t* entry:: entry to list backward references of
 *
 *returns nothing
 */
void list_backward(entry_t* entry);


/*
 *list_backward_keys
 *recursively finds unique keys for entry and backward references
 *assumes at least 1 backward reference is present
 *
 *entry_t* entry:: entry to list keys of
 *
 *returns a linked list of unique keys
 */
key_list_t* list_backward_keys(entry_t* entry);


/*
 *entry_delete
 *attempts to delete entry from database
 *
 *char* key:: key of entry to delete
 *
 *database_t* db:: database to delete entry from
 *
 *returns a pointer to the deleted entry
 */
entry_t* entry_delete(char* key, database_t* db);


/*
 *delete_elements
 *clears elements from entry and frees memory
 *
 *entry_t* entry:: entry to clear
 *
 *returns nothing
 */
void delete_elements(entry_t* entry);


/*
 *delete_reference
 *removes reference as forward of original and original as backward of reference
 *
 *entry_t* original:: entry holding the reference as an element
 *entry_t* reference:: element of original entry
 *
 *returns nothing
 */
void delete_reference(entry_t* original, entry_t* reference);


/*
 *entry_append
 *appends the values to the end of the entry with specified key
 *
 *char* key:: key of entry
 *char* values:: values to append
 *database_t* db:: database with entry
 *
 *returns nothing
 */
void entry_append(char* key, char* values, database_t* db);



/*
 *display_links
 *used for debugging
 *displays the value and next and prev links for each element in an entry
 *returns nothing
 */
void display_links(entry_t* entry);

/*
 *entry_push
 *pushes values onto beginning of entry
 *
 *char* key:: key of entry to push values to
 *char* values:: values to push
 *database_t db:: database with entry to push to
 *
 *returns nothing
 */
void entry_push(char* key, char* values, database_t* db);


/*
 *push_elements
 *pushes values onto entry
 *
 *char* values:: values to push
 *entry_t* entry:: entry to push to
 *database_t* db:: database with entry
 *
 *returns true if successful otherwise false
 */
bool push_elements(char* values, entry_t* entry, database_t* db);


/*
 *entry_pluck
 *displays and removes entry at index
 *
 *char* key:: key of entry to pluck from
 *int index:: index of element to pluck
 *database_t* db:: database containing element
 *
 *returns nothing
 */
void entry_pluck(char* key, int index, database_t* db);


/*
 *entry_pick
 *displays entry at index
 *
 *char* key:: key of entry to pick from
 *int index:: index of element to pick
 *database_t* db:: database containing element
 *
 *returns nothing
 */
void entry_pick(char* key, int index, database_t* db);


/*
 *check_simple
 *checks if an entry has any general elements
 *
 *entry_t* entry:: entry to check
 *
 *returns true if entry is simple otherwise false
 */
bool check_simple(entry_t* entry);


/*
 *find_min
 *recursively finds the minimum for a given entry
 *
 *entry_t* entry:: entry to find min
 *
 *returns the min of the entry (or references)
 */
int find_min(entry_t* entry);


/*
 *find_max
 *recursively finds the max for a given entry
 *
 *entry_t* entry:: entry to find max
 *
 *returns the max of the entry (or references)
 */
int find_max(entry_t* entry);


/*
 *find_sum
 *finds the sum of an entry including references
 *
 *entry_t* entry:: entry to sum
 *
 *returns the sum of the entry (and references)
 */
int find_sum(entry_t* entry);


/*
 *find_length
 *finds the number of items in an entry and its references
 *
 *entry_t* entry:: entry to find number of elements
 *
 *returns the length
 */
int find_length(entry_t* entry);


/*
 *bubblesort
 *bubblesorts given simple entry
 *
 *entry_t* entry:: entry to be sorted
 *
 *returns nothing
 */
void bubblesort(entry_t* entry);


/*
 *entry_uniq
 *removes adjacent repeated values in simple entry
 *
 *entry_t* entry:: entry to modify
 *
 *returns nothing
 */
void entry_uniq(entry_t* entry);


/*
 *entry_reverse
 *reverses the order of a simple entry
 *
 *entry_t* entry:: entry to reverse
 *
 *returns nothing
 */
void entry_reverse(entry_t* entry);



/*
 *entry_type
 *prints the entry type
 *
 *entry_t* entry:: entry to get type of
 *
 *returns nothing
 */
void entry_type(entry_t* entry);


/*
 *save_snapshot
 *saves a snapshot of the database at a given time
 *
 *database_t* db:: database to take snapshot of
 *
 *returns nothing
 */
void save_snapshot(database_t* db);


/*
 *copy_entry
 *copies a given entry and allocates memory so none is shared
 *
 *entry_t* entry:: entry to be copied
 *
 *returns a copy of the entry
 */
entry_t* copy_entry(entry_t* entry);


/*
 *get_snapshot_entry
 *retrieves an entry with a given key from the snapshot
 *
 *char* key:: key of the entry to get
 *snapshot_t* snap:: snapshot to get key from
 *
 *returns the corresponding entry
 */
entry_t* get_snapshot_entry(char* key, snapshot_t* snap);


/*
 *snapshot_checkout
 *sets the db as the given snapshot
 *
 *database_t* db:: database to change
 *int id:: id of desired snapshot
 *
 *returns nothing
 */
void snapshot_checkout(database_t* db, int id);

/*
 *remove_entries
 *removes and frees entries from database
 *
 *database_t* db:: database to clear
 *
 *returns nothing
 */
void remove_entries(database_t* db);


/*
 *delete_snapshot_id
 *deletes snapshot with given id
 *
 *database_t*:: database containing snapshot
 *int id:: id of snapshot to delet
 *
 *returns nothing
 */
void delete_snapshot_id(database_t* db, int id);


/*
 *delete_snapshot
 *deletes snapshot from the database
 *
 *snapshot_t* snap; snapshot to delete
 *database_t* db:: database containing snapshot
 *
 *returns nothing
 */
void delete_snapshot(snapshot_t* snap, database_t* db);


/*
 *snapshot_rollback
 *restores to given snapshot and deletes newer ones
 *
 *database_t* db:: database containing snapshots
 *int id:: id of snapshot to revert to
 *
 *returns nothing
 */
void snapshot_rollback(database_t* db, int id);


/*
 *entry_purge
 *attempts to delete entry from db and all snapshot
 *
 *database_t* db:: database containing entry and snapshots
 *char* key:: key of entry to delete
 *
 *returns nothing
 */
void entry_purge(database_t* db, char* key);

/*
 *clear_database
 *frees all allocated memory
 *
 *database_t* db:: database to clear
 *
 *returns nothign
 */
void clear_database(database_t* db);


/*
 *entry_pop
 *deletes and prints the first element of an entry
 *
 *char* key:: key of entry to delete
 *database_t* db:: database containing entry
 *
 *returns nothing
 */
void entry_pop(char* key, database_t* db);


#endif
