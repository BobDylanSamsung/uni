/**
 * comp2017 - assignment 2
 * <your name>
 * <your unikey>
 */

#include "ymirdb.h"

int main(){
	database_t* db = init_database();

	char buf[MAX_LINE];
	bool cont = true;

	printf("> ");
	
	while(strcmp(fgets(buf, MAX_LINE, stdin), "\n")){
		
		//if last character of input is newline, remove it
		if('\n' == buf[strlen(buf) - 1]){
			buf[strlen(buf) - 1] = '\0';
		}

		cont = general_dispatch(buf, db);

		if(!cont){
			break;
		}
		printf("\n> ");
	}

	return 0;

}


bool general_dispatch(char* line, database_t* db){
	char* new_args = strdup(line);
	char* args = new_args;
	char* command = strsep(&args, " ");


	if(0 == strcasecmp(command, "HELP")){
		command_help();
	}

	else if(0 == strcasecmp(command, "LIST")){
		list_dispatch(args, db);
	}

	else if(0 == strcasecmp(command, "GET")){
		char* key = strsep(&args, " ");
		entry_t* entry = retrieve_key(key, db);
		if(NULL != entry)
			entry_get(entry);
		else
			printf("no such key\n");
	}

	else if(0 == strcasecmp(command, "SET")){
		char* key = strsep(&args, " ");
		entry_set(key, args, db);
	}

	else if(0 == strcasecmp(command, "PUSH")){
		char* key = strsep(&args, " ");
		entry_push(key, args, db);
	}

	else if(0 == strcasecmp(command, "APPEND")){
		char* key = strsep(&args, " ");
		entry_append(key, args, db);
	}

	else if(0 == strcasecmp(command, "PICK")){
		char* key = strsep(&args, " ");
		int index = atoi(strsep(&args, " "));
		entry_pick(key, index, db);
	}

	else if(0 == strcasecmp(command, "PLUCK")){
		char* key = strsep(&args, " ");
		int index = atoi(strsep(&args, " "));
		entry_pluck(key, index, db);
	}

	else if(0 == strcasecmp(command, "POP")){
		char* key = strsep(&args, " ");
		entry_pop(key, db);
	}

	else if(0 == strcasecmp(command, "BYE")){
		printf("bye\n");
		clear_database(db);
		free(new_args);
		return false;
	}

	else if(0 == strcasecmp(command, "DEL")){
		char* key = strsep(&args, " ");
		entry_delete(key, db);
	}

	else if(0 == strcasecmp(command, "MIN")){
		char* key = strsep(&args, " ");
		find_min(key, db);
	}

	else if(0 == strcasecmp(command, "MAX")){
		char* key = strsep(&args, " ");
		find_max(key, db);
	}

	else if(0 == strcasecmp(command, "SUM")){
		char* key = strsep(&args, " ");
		find_sum(key, db);
	}

	else if(0 == strcasecmp(command, "LEN")){
		char* key = strsep(&args, " ");
		find_length(key, db);
	}

	else if(0 == strcasecmp(command, "DEL")){
		char* key = strsep(&args, " ");
		free(entry_delete(key, db));
	}

	else if(0 == strcasecmp(command, "SORT")){
		char* key = strsep(&args, " ");
		bubblesort(retrieve_key(key, db));
	}

	else if(0 == strcasecmp(command, "UNIQ")){
		char* key = strsep(&args, " ");
		entry_uniq(retrieve_key(key, db));
	}

	else if(0 == strcasecmp(command, "REV")){
		char* key = strsep(&args, " ");
		entry_reverse(retrieve_key(key, db));
	}

	else if(0 == strcasecmp(command, "SNAPSHOT")){
		save_snapshot(db);
	}

	else if(0 == strcasecmp(command, "DROP")){
		int id = atoi(strsep(&args, " "));
		delete_snapshot_id(db, id);
	}

	else if(0 == strcasecmp(command, "CHECKOUT")){
		int id = atoi(strsep(&args, " "));
		snapshot_checkout(db, id);
	}

	else if(0 == strcasecmp(command, "ROLLBACK")){
		int id = atoi(strsep(&args, " "));
		snapshot_rollback(db, id);
	}

	else{
		printf("invalid command\n");
	}

	free(new_args);
	return true;
}

void list_dispatch(char* line, database_t* db){
	char* new_args = strdup(line);
	char* args = new_args;
	char* command = strsep(&args, " ");
	if(0 == strcasecmp(command, "KEYS")){
		list_keys(db);
	}

	else if(0 == strcasecmp(command, "ENTRIES")){
		list_entries(db);
	}

	else if(0 == strcasecmp(command, "SNAPSHOTS")){
		list_snapshots(db);
	}

	else{
		printf("invalid command\n");
	}

	free(new_args);
}

database_t* init_database(){
	database_t* db = malloc(sizeof(database_t));
	db->num_entries = 0;
	db->entry_head = NULL;
	db->snapshot_head = NULL;
	return db;
}


//sets a particular key value pair
//will return the new entry
entry_t* entry_set(char* key, char* values, database_t* db){

	entry_t* new_entry = NULL;

	switch(check_valid_key(key, db)){
		case 0:
			//key doesnt exist allocate memory in the heap to new entry
			new_entry = malloc(sizeof(entry_t));
			strcpy(new_entry->key, key);
			entry_add(db, new_entry);
			break;

		case 1:
			//key already exists as entry clear entries in the key
			new_entry = retrieve_key(key, db);
			element_t* cursor = new_entry->head;
			while(NULL != cursor){
				element_t* next_element = cursor->next;
				free(cursor);
				cursor = next_element;
			}
			new_entry->head = NULL;
			break;

		case 2:
			//key is not valid
			printf("key is not valid\n");
			return NULL;
			break;

		default:
			break;
	}

	if(NULL == new_entry){
		//raise error
		return NULL;
	}



	//assign values
	//for each value in values, make a new element and add it to the entry
	new_entry->head = link_elements(values, db);

	new_entry->length = num_elements(values);
	printf("ok\n");
	return new_entry;
}

element_t* link_elements(char* values, database_t* db){
	element_t* new_element;
	element_t* prev_element = NULL;
	element_t* head;
	int i = 0;
	char* new_vals = strdup(values);
	char* value_dup = new_vals;
	while(value_dup){

		char* val_str = strsep(&value_dup, " ");
		
		if(is_num(val_str)){
			//simple entry
			new_element = malloc(sizeof(element_t));
			new_element->value = atoi(val_str);
			new_element->type = INTEGER;	
		}

		else if(is_key(val_str)){
			entry_t* link = retrieve_key(val_str, db);
			if(NULL == link){
				printf("no such key\n");
				new_element = NULL;
			}else{
				new_element = malloc(sizeof(element_t));
				new_element->entry = link;
				new_element->type = ENTRY;
			}
		}

		else{
			printf("invalid key\n");
			new_element = NULL;
		}
		

		if(0 == i){		//first element of entry, set head accordingly
			head = new_element;
		}else{
			prev_element->next = new_element;
		}
		if(NULL == new_element){
			//raise error
			free(new_vals);
			return NULL;
		}
		new_element->prev = prev_element;
		prev_element = new_element;
		i++;
	}

	new_element->next = NULL;
	free(new_vals);
	return head;
}

element_t* link_push(char* values, database_t* db){
	element_t* new_element;
	element_t* prev_element = NULL;
	char* new_vals = strdup(values);
	char* value_dup = new_vals;
	while(value_dup){

		char* val_str = strsep(&value_dup, " ");
		
		if(is_num(val_str)){
			//simple entry
			new_element = malloc(sizeof(element_t));
			new_element->value = atoi(val_str);
			new_element->type = INTEGER;	
		}

		else if(is_key(val_str)){
			entry_t* link = retrieve_key(val_str, db);
			if(NULL == link){
				printf("no such key\n");
				new_element = NULL;
			}else{
				new_element = malloc(sizeof(element_t));
				new_element->entry = link;
				new_element->type = ENTRY;
			}
		}

		else{
			printf("invalid key\n");
			new_element = NULL;
		}

		if(NULL == new_element){
			//raise error
			free(new_vals);
			return NULL;
		}

		new_element->next = prev_element;

		if(NULL != prev_element)
			prev_element->prev = new_element;

		prev_element = new_element;
	}

	new_element->prev = NULL;
	free(new_vals);
	return new_element;
}


void entry_get(entry_t* entry){
	//printf("getting %s\n", entry->key);		//debug
	element_t* cursor = entry->head;

	printf("[");
	while(NULL != cursor){
		if(NULL != cursor->prev){
			printf(" ");
		}
		if(cursor->type == INTEGER)
			printf("%d", cursor->value);
		else
			printf("%s", cursor->entry->key);
		cursor = cursor->next;
	}
	printf("]\n");
	return;
}

bool entry_push(char* key, char* values, database_t* db){
	//check key exists
	entry_t* entry = retrieve_key(key, db);

	if(NULL != entry){
		//make new linked list with values
		element_t* new_head = link_push(values, db);
		if(NULL != new_head){
			entry->length = entry->length + num_elements(values);
		}

		if(NULL != entry->head){
			//set prev for old head
			element_t* cursor = new_head;
			while(NULL != cursor->next){
				cursor = cursor->next;
			}

			entry->head->prev = cursor;
			cursor->next = entry->head;
		}

		entry->head = new_head;
		printf("ok\n");
		return true;

	}else{
		printf("no such key\n");
		return false;
	}
}

bool entry_append(char* key, char* values, database_t* db){
	//check key exists
	entry_t* entry = retrieve_key(key, db);
	if(NULL != entry){
		//make new linked list with values
		element_t* new_head = link_elements(values, db);
		if(NULL != new_head){
			entry->length = entry->length + num_elements(values);
		}

		if(NULL != entry->head){
			element_t* cursor = entry->head;
			while(NULL != cursor->next){
				cursor = cursor->next;
			}
			cursor->next = new_head;
			new_head->prev = cursor;	
		}

		else{
			entry->head = new_head;
		}
		printf("ok\n");
		return true;
	}else{
		printf("no such entry\n");
		return false;
	}
}


entry_t* retrieve_key(char* key, database_t* db){
	entry_t* cursor = db->entry_head;
	while(NULL != cursor){
		if(!strcmp(cursor->key, key)){
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

//adds entry to the database, returns number of entries after the addition
int entry_add(database_t* db, entry_t* entry){
	entry->prev = NULL;
	if(0 == db->num_entries){
		entry->next = NULL;
	}else{
		db->entry_head->prev = entry;
		entry->next = db->entry_head;
	}
	db->entry_head = entry;
	db->num_entries++;
	return(db->num_entries);
}

bool entry_pick(char* key, int index, database_t* db){
	entry_t* entry = retrieve_key(key, db);
	if(NULL == entry){
		printf("no such key\n");
		return false;
	}else if(entry->length < index || 1 > index){
		printf("index out of range\n");
		return false;
	}else{
		element_t* cursor = entry->head;
		for(int i = 1; i < index; i++){
			cursor = cursor->next;
		}
		if(cursor->type == INTEGER)
			printf("%d\n", cursor->value);
		else
			printf("%s\n", cursor->entry->key);
		return true;
	}
}

bool entry_pluck(char* key, int index, database_t* db){
	entry_t* entry = retrieve_key(key, db);
	//printf("len is: %ld\t accessing %d\n", entry->length, index);		//debug
	if(NULL == entry){
		printf("no such key\n");
		return false;
	}

	else if(entry->length < index || 1 > index){
		printf("index out of range\n");
		return false;
	}

	else if(1 == entry->length){
		printf("%d\n", entry->head->value);
		free(entry->head);
		entry->head = NULL;
		entry->length = 0;
		return true;
	}

	else{
		element_t* cursor = entry->head;
		for(int i = 1; i < index; i++){
			cursor = cursor->next;
		}


		if(cursor->type == INTEGER)
			printf("%d\n", cursor->value);
		else
			printf("%s\n", cursor->entry->key);


		if(1 == index){
			cursor->next->prev = NULL;
			entry->head = cursor->next;
		}else if(entry->length == index){
			cursor->prev->next = NULL;
		}else{
			cursor->prev->next = cursor->next;
			cursor->next->prev = cursor->prev;
		}
		free(cursor);
		entry->length--;
		return true;
	}
}

bool entry_pop(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);
	if(NULL == entry){
		printf("no such key\n");
		return false;
	}else if(entry->length == 0){
		printf("nil\n");
		return false;
	}else if(entry->length == 1){
		printf("%d\n", entry->head->value);
		free(entry->head);
		entry->head = NULL;
		entry->length = 0;
		return true;
	}else{
		element_t* cursor = entry->head;
		
		if(cursor->type == INTEGER)
			printf("%d\n", cursor->value);
		else
			printf("%s\n", cursor->entry->key);
		
		entry->head = cursor->next;
		cursor->next->prev = NULL;
		free(cursor);
		entry->length--;
		return true;
	}
}

void command_help() {
	printf("%s", HELP);
}

int num_elements(char* values){
	int size = 0;

	char* new_vals = strdup(values);
	char* value_dup = new_vals;

	while(value_dup){
		strsep(&value_dup, " ");
		size += 1;
	}

	free(new_vals);

	return size;
}

void clear_database(database_t* db){
	entry_t* entry_cursor = db->entry_head;

	while(NULL != entry_cursor){
		entry_t* next_entry = entry_cursor->next;

		//free elements from each entry
		element_t* element_cursor = entry_cursor->head;
		while(NULL != element_cursor){
			element_t* next_element = element_cursor->next;
			free(element_cursor);
			element_cursor = next_element;
		}

		free(entry_cursor);

		entry_cursor = next_entry;
	}

	snapshot_t* snap_cursor = db->snapshot_head;

	while(NULL != snap_cursor){
		snapshot_t* next_snap = snap_cursor->next;
		delete_snapshot(snap_cursor,db);
		snap_cursor = next_snap;
	}

	free(db);
}

void remove_entries(database_t* db){
	entry_t* entry_cursor = db->entry_head;

	while(NULL != entry_cursor){
		entry_t* next_entry = entry_cursor->next;

		//free elements from each entry
		element_t* element_cursor = entry_cursor->head;
		while(NULL != element_cursor){
			element_t* next_element = element_cursor->next;
			free(element_cursor);
			element_cursor = next_element;
		}

		free(entry_cursor);

		entry_cursor = next_entry;
	}
	db->entry_head = NULL;
}

void list_entries(database_t* db){
	entry_t* cursor = db->entry_head;

	if(NULL == cursor)
		printf("no entries\n");

	while(NULL != cursor){
		printf("%s ", cursor->key);
		entry_get(cursor);
		cursor = cursor->next;
	}
}

void list_keys(database_t* db){
	entry_t* cursor = db->entry_head;

	if(NULL == cursor)
		printf("no keys\n");

	while(NULL != cursor){
		printf("%s\n", cursor->key);
		cursor = cursor->next;
	}
}


//0 - valid
//1 - key exists
//2 - key string not valid
int check_valid_key(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(!is_key(key))
		return 2;
	if(NULL == entry)
		return 0;
	else
		return 1;
}

entry_t* entry_delete(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);
	if (NULL != entry){
		//check first entry (no previous entry)
		if(entry == db->entry_head){
			db->entry_head = entry->next;
			if(NULL != entry->next){
				entry->next->prev = NULL;
			}
		}

		//previous entry exists
		else{
			if(NULL != entry->next){
				entry->next->prev = entry->prev;
				entry->prev->next = entry->next;
			}
			else{
				entry->prev->next = NULL;
			}
		}

		
		printf("ok\n");
		db->num_entries--;
		return entry;
	}else{
		printf("no such key\n");
		return NULL;
	}
}

void find_min(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);
	printf("FINDING MIN\n");

	if(NULL != entry){
		element_t* cursor = entry->head;
		int min = cursor->value;
		while(NULL != cursor){
			if(cursor->value < min)
				min = cursor->value;
			cursor = cursor->next;
		}
		printf("%d\n", min);


	}else{
		printf("no such entry\n");
	}
}

void find_max(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);
	if(NULL != entry){
		element_t* cursor = entry->head;
		int max = cursor->value;
		while(NULL != cursor){
			if(cursor->value > max)
				max = cursor->value;
			cursor = cursor->next;
		}
		printf("%d\n", max);

	}else{
		printf("no such entry\n");
	}
}

void find_sum(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(NULL != entry){
		element_t* cursor = entry->head;
		int sum = 0;
		while(NULL != cursor){
			sum += cursor->value;
			cursor = cursor->next;
		}
		printf("%d\n", sum);


	}else{
		printf("no such entry\n");
	}
}

void find_length(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(NULL != entry){
		printf("%ld\n", entry->length);


	}else{
		printf("no such entry\n");
	}
}

void bubblesort(entry_t* entry){

	if(NULL == entry){
		printf("no such key\n");
		return;
	}
	
	if(2 == entry->length){
		if(entry->head->value > entry->head->next->value){
			int temp = entry->head->value;
			entry->head->value = entry->head->next->value;
			entry->head->next->value = temp;
		}
		printf("ok\n");
		return;
	}

	if(2 > entry->length){
		printf("ok\n");
		return;
	}

	for(int i = 0; i < entry->length; i++){
		element_t* current = entry->head;
		element_t* next = entry->head->next;
		for(int j = 0; j < entry->length - i - 1; j++){
			if(current->value > next->value){
				int temp = current->value;
				current->value = next->value;
				next->value = temp;
			}
			current = next;
			next = next->next;
		}
	}
	printf("ok\n");
}

void entry_uniq(entry_t* entry){
	if(NULL == entry){
		printf("no such key\n");
		return;
	}

	element_t* cursor = entry->head;

	while(NULL != cursor->next){
		while(cursor->next->value == cursor->value){
			//remove cursor->next

			element_t* temp = cursor->next;
			cursor->next = cursor->next->next;
			if(NULL != cursor->next){
				cursor->next->prev = cursor;
			}

			free(temp);
			entry->length--;
			if(NULL == cursor->next){
				break;
			}
		}
		if(NULL == cursor->next){
			break;
		}
		cursor = cursor->next;
	} 
	printf("ok\n");
}

void display_links(entry_t* entry){
	element_t* cursor = entry->head;

	while(NULL != cursor){
		int val = cursor->value;
		int next = (cursor->next == NULL) ? 0 : cursor->next->value;
		int prev = (cursor->prev == NULL) ? 0 : cursor->prev->value;
		printf("Value: %d\t Prev: %d\t Next: %d\n", val, prev, next);
		cursor = cursor->next;
	}
}

void entry_reverse(entry_t* entry){
	element_t* cursor = entry->head;

	if(NULL == entry){
		printf("no such key\n");
		return;
	}

	while(NULL != cursor->next){
		element_t* temp = cursor->next;
		cursor->next = cursor->prev;
		cursor->prev = temp;
		cursor = cursor->prev;
	}

	cursor->next = cursor->prev;
	cursor->prev = NULL;


	entry->head = cursor;

	printf("ok\n");
}

void save_snapshot(database_t* db){
	//for each entry
		//make a copy of the entry
		//for each element
			//make a copy of the element and link accordingly

	snapshot_t* snap = malloc(sizeof(snapshot_t));
	snapshot_t* snap_cursor = db->snapshot_head;

	if(NULL == snap_cursor){
		snap->id = 1;
		db->snapshot_head = snap;
		snap->prev = NULL;
		snap->next = NULL;
	}

	else{
		while(NULL != snap_cursor->next){
			snap_cursor = snap_cursor->next;
		}

		snap->id = snap_cursor->id+1;
		snap->prev = snap_cursor;
		snap->next = NULL;
		snap_cursor->next = snap;
	}

	printf("saved as snapshot %d\n", snap->id);

	//set entries for the snapshot

	entry_t* entry_cursor = db->entry_head;
	entry_t* prev_copy = NULL;
	while(NULL != entry_cursor){
		entry_t* entry_copy = copy_entry(entry_cursor);

		if(NULL == prev_copy){
			snap->head = entry_copy;
			entry_copy->prev = NULL;
		}else{
			prev_copy->next = entry_copy;
			entry_copy->prev = prev_copy;
		}

		prev_copy = entry_copy;

		// printf("\n\n///////////////////\nORIGINAL\n////////////////////\n");
		// display_links(entry_cursor);

		// printf("///////////////////\nCOPY\n////////////////////\n");
		// display_links(entry_copy);
		
		entry_cursor = entry_cursor->next;
	}

	prev_copy->next = NULL;

	return;
}

entry_t* copy_entry(entry_t* entry){
	if(NULL == entry)
		return NULL;

	entry_t* copy = malloc(sizeof(entry_t));

	strcpy(copy->key, entry->key);
	copy->length = entry->length;

	element_t* cursor = entry->head;
	if(NULL == cursor){
		copy->head = NULL;
		return NULL;
	}

	element_t* prev_element = NULL;
	while(NULL != cursor){
		element_t* new_element = malloc(sizeof(element_t));
		new_element->value = cursor->value;
		new_element->prev = prev_element;
		if(NULL != prev_element){
			prev_element->next = new_element;
		}else{
			copy->head = new_element;
		}

		prev_element = new_element;
		cursor = cursor->next;
	}
	prev_element->next = NULL;
	return copy;
}

void list_snapshots(database_t* db){
	snapshot_t* cursor = db->snapshot_head;

	if(NULL == cursor){
		printf("no snapshots\n");
		return;
	}

	while(NULL != cursor){
		printf("%d", cursor->id);
		if(NULL != cursor->next){
			printf(" ");
		}
		cursor = cursor->next;
	}

	printf("\n");
}

void delete_snapshot_id(database_t* db, int id){
	snapshot_t* cursor = db->snapshot_head;

	while(NULL != cursor){
		if(id == cursor->id){
			delete_snapshot(cursor, db);
			printf("ok\n");
			return;
		}

		cursor = cursor->next;
	}

	printf("no such snapshot\n");
}

void delete_snapshot(snapshot_t* snap, database_t* db){
	entry_t* entry_cursor = snap->head;

	while(NULL != entry_cursor){
		entry_t* next_entry = entry_cursor->next;

		//free elements from each entry
		element_t* element_cursor = entry_cursor->head;
		while(NULL != element_cursor){
			element_t* next_element = element_cursor->next;
			free(element_cursor);
			element_cursor = next_element;
		}

		free(entry_cursor);

		entry_cursor = next_entry;
	}

	if((NULL == snap->prev) & (NULL == snap->next)){
		db->snapshot_head = NULL;
	}

	else if(NULL == snap->prev){
		db->snapshot_head = snap->next;
		snap->next->prev = NULL;
	}

	else if(NULL == snap->next){
		snap->prev->next = NULL;
	}

	else{
		snap->prev->next = snap->next;
		snap->next->prev = snap->prev;
	}

	free(snap);
}

void snapshot_checkout(database_t* db, int id){
	snapshot_t* cursor = db->snapshot_head;

	while(NULL != cursor){
		if(id == cursor->id){
			
			//get rid of old entries
			remove_entries(db);

			//init cursors and new db entry head
 			entry_t* snap_entry_cursor = cursor->head;
			db->entry_head = copy_entry(snap_entry_cursor);
			entry_t* db_entry_cursor = db->entry_head;

			snap_entry_cursor = snap_entry_cursor->next;
			db_entry_cursor->prev = NULL;

			while(NULL != snap_entry_cursor){
				db_entry_cursor->next = copy_entry(snap_entry_cursor);
				db_entry_cursor->next->prev = db_entry_cursor;
				db_entry_cursor = db_entry_cursor->next;
				snap_entry_cursor = snap_entry_cursor->next;
			}

			db_entry_cursor->next = NULL;

			printf("ok\n");
			return;
		}

		cursor = cursor->next;
	}

	printf("no such snapshot\n");
}

void snapshot_rollback(database_t* db, int id){
	snapshot_t* cursor = db->snapshot_head;
	bool found = false;
	while((NULL != cursor) & (!found)){
		if(id == cursor->id){
			
			//get rid of old entries
			remove_entries(db);

			//init cursors and new db entry head
 			entry_t* snap_entry_cursor = cursor->head;
			db->entry_head = copy_entry(snap_entry_cursor);
			entry_t* db_entry_cursor = db->entry_head;

			snap_entry_cursor = snap_entry_cursor->next;
			db_entry_cursor->prev = NULL;

			while(NULL != snap_entry_cursor){
				db_entry_cursor->next = copy_entry(snap_entry_cursor);
				db_entry_cursor->next->prev = db_entry_cursor;
				db_entry_cursor = db_entry_cursor->next;
				snap_entry_cursor = snap_entry_cursor->next;
			}

			db_entry_cursor->next = NULL;

			printf("ok\n");
			found = true;
		}
		

		cursor = cursor->next;

	}

	if(!found)
		printf("no such snapshot\n");

	else{
		cursor->prev->next = NULL;
		while(NULL != cursor){
			snapshot_t* next_snap = cursor->next;
			delete_snapshot(cursor, db);
			cursor = next_snap;
		}
	}
}

bool is_num(char* str){
	int i = 0;
	while('\0' != str[i]){
		if(!isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}	

bool is_key(char* str){
	if(!isalpha(str[0]))
		return false;

	int i = 1;
	while('\0' != str[i]){
		if(!isalnum(str[i]))
			return false;
		i++;
	}
	return true;
}