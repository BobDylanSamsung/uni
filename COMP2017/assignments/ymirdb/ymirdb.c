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

	clear_database(db);

	return 0;

}

/*
 *init_database
 *initialises a database
 *
 *returns new database
 */
database_t* init_database(){
	database_t* db = malloc(sizeof(database_t));
	db->num_entries = 0;
	db->entry_head = NULL;
	db->snapshot_head = NULL;
	return db;
}


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
bool general_dispatch(char* line, database_t* db){
	char* new_args = strdup(line);
	char* args = new_args;
	char* command = strsep(&args, " ");


	if(0 == strcasecmp(command, "HELP")){
		printf("%s", HELP);
	}

	else if(0 == strcasecmp(command, "LIST")){
		list_dispatch(args, db);
	}

	else if(0 == strcasecmp(command, "SET")){
		char* key = strsep(&args, " ");
		entry_set(key, args, db);
	}

	else if(0 == strcasecmp(command, "GET")){
		char* key = strsep(&args, " ");
		entry_get(retrieve_key(key, db));
	}

	else if(0 == strcasecmp(command, "FORWARD")){
		char* key = strsep(&args, " ");
		list_forward(retrieve_key(key, db));
		printf("\n");
	}

	else if(0 == strcasecmp(command, "BACKWARD")){
		char* key = strsep(&args, " ");
		list_backward(retrieve_key(key, db));
		printf("\n");
	}

	else if(0 == strcasecmp(command, "DEL")){
		char* key = strsep(&args, " ");
		free(entry_delete(key, db));
	}

	else if(0 == strcasecmp(command, "APPEND")){
		char* key = strsep(&args, " ");
		entry_append(key, args, db);
	}

	else if(0 == strcasecmp(command, "PUSH")){
		char* key = strsep(&args, " ");
		entry_push(key, args, db);
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

	else if(0 == strcasecmp(command, "PICK")){
		char* key = strsep(&args, " ");
		int index = atoi(strsep(&args, " "));
		entry_pick(key, index, db);
	}

	else if(0 == strcasecmp(command, "MIN")){
		entry_t* entry = retrieve_key(strsep(&args, " "), db);
		if(NULL == entry){
			printf("no such key\n");
		}
		else{
			printf("%d\n", find_min(entry));	
		}
	}

	else if(0 == strcasecmp(command, "MAX")){
		entry_t* entry = retrieve_key(strsep(&args, " "), db);
		if(NULL == entry){
			printf("no such key\n");
		}
		else{
			printf("%d\n", find_max(entry));	
		}
	}

	else if(0 == strcasecmp(command, "SUM")){
		entry_t* entry = retrieve_key(strsep(&args, " "), db);
		if(NULL == entry){
			printf("no such key\n");
		}
		else{
			printf("%d\n", find_sum(entry));	
		}
	}

	else if(0 == strcasecmp(command, "LEN")){
		entry_t* entry = retrieve_key(strsep(&args, " "), db);
		if(NULL == entry){
			printf("no such key\n");
		}
		else{
			printf("%d\n", find_length(entry));	
		}
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

	else if(0 == strcasecmp(command, "TYPE")){
		char* key = strsep(&args, " ");
		entry_type(retrieve_key(key, db));
	}

	else if(0 == strcasecmp(command, "SNAPSHOT")){
		save_snapshot(db);
	}

	else if(0 == strcasecmp(command, "CHECKOUT")){
		int id = atoi(strsep(&args, " "));
		snapshot_checkout(db, id);
	}

	//debugging
	else if(0 == strcasecmp(command, "LINKS")){
		char* key = strsep(&args, " ");
		display_links(retrieve_key(key, db));
	}

	else if(0 == strcasecmp(command, "DROP")){
		int id = atoi(strsep(&args, " "));
		delete_snapshot_id(db, id);
	}

	else if(0 == strcasecmp(command, "ROLLBACK")){
		int id = atoi(strsep(&args, " "));
		snapshot_rollback(db, id);
	}

	else if(0 == strcasecmp(command, "PURGE")){
		char* key = strsep(&args, " ");
		entry_purge(db, key);
	}

	else if(0 == strcasecmp(command, "BYE")){
		printf("bye\n");
		free(new_args);
		return false;
	}

	else{
		printf("invalid command\n");
	}

	free(new_args);
	return true;
}


/*
 *list_dispatch
 *calls one of the 3 list functions: keys, entries or snapshots
 *
 *char* line:: modified user input signalling which func to call
 *database_t* db:: main db
 *
 *returns nothing 
 */
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

/*
 *list_keys
 *lists the keys present in the database
 *
 *database_t* db database to list keys in
 *
 *returns nothing
 */
void list_keys(database_t* db){
	entry_t* cursor = db->entry_head;

	if(NULL == cursor)
		printf("no keys\n");

	while(NULL != cursor){
		printf("%s\n", cursor->key);
		cursor = cursor->next;
	}
}

/*
 *list_entries
 *lists the keys and the entries for each present in the database
 *
 *database_t* db database to list entries in
 *
 *returns nothing
 */
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

/*
 *list_snapshots
 *lists the snpashot ids for each present in the database
 *
 *database_t* db database to list snapshots in
 *
 *returns nothing
 */
void list_snapshots(database_t* db){
	snapshot_t* cursor = db->snapshot_head;

	if(NULL == cursor){
		printf("no snapshots\n");
		return;
	}

	while(NULL != cursor->next){
		cursor = cursor->next;
	}

	while(NULL != cursor){
		printf("%d\n", cursor->id);
		// if(NULL != cursor->prev){
		// 	printf(" ");
		// }
		cursor = cursor->prev;
	}
}

/*
 *entry_get
 *displays the contents of an entry in the format [...]
 *
 *entry_t* entry:: entry to list contents of
 *
 *returns nothing
 */
void entry_get(entry_t* entry){

	if(NULL == entry){
		printf("no such key\n");
		return;
	}


	element_t* cursor = entry->head;

	printf("[");

	while(NULL != cursor){
		if(cursor->type == INTEGER)
			printf("%d", cursor->value);
		else
			printf("%s", cursor->entry->key);

		if(NULL != cursor->next){
			printf(" ");
		}
		cursor = cursor->next;
	}

	printf("]\n");
	return;
}


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
entry_t* entry_set(char* key, char* values, database_t* db){
	entry_t* new_entry = NULL;

	if(!check_values(values, db)){
		printf("no such key\n");
		return NULL;
	}

	switch(check_valid_key(key, db)){
		case 0:
			//valid key and does not exist
			//add entry to db

			new_entry = malloc(sizeof(entry_t));
			memset(new_entry->key, 0, MAX_KEY);
			
			// int i = 0;
			// while(i < strlen(key) & key[i] != '\0'){
			// 	new_entry->key[i] = key[i];
			// 	printf("letter is %c and %c\n", key[i], new_entry->key[i]);
			// 	i++;
			// }

			strncpy(new_entry->key, key, strlen(key));

			entry_add(db, new_entry);
			new_entry->backward_size = 0;
			break;

		case 1:
			new_entry = retrieve_key(key, db);
			//element_t* cursor = new_entry->head;

			// while(NULL != cursor){
			// 	element_t* next_element = cursor->next;
			// 	if(cursor->type == INTEGER){
			// 		free(cursor);
			// 	}
			// 	cursor = next_element;
			// }

			delete_elements(new_entry);

			new_entry->head = NULL;
			break;

		case 2:
			//key not valid
			printf("key not valid\n");
			return NULL;
		
		default:
			return NULL;
	}

	new_entry->is_simple = true;
	new_entry->head = NULL;
	new_entry->forward_size = 0;
	new_entry->length = 0;

	if(link_elements(values, new_entry, db)){
		printf("ok\n");
		return new_entry;
	}
	else{
		return NULL;
	}
}	


/*
 *check_values
 *checks if a string of values contains either characters or known keys
 *
 *char* values:: string to check
 *database_t* db:: database containing entries
 *
 *returns true if valid otherwise false
 */
bool check_values(char* values, database_t* db){
	char* new_vals = strdup(values);
	char* value_dup = new_vals;

	while(value_dup){
		char* val_str = strsep(&value_dup, " ");
		if(0 < strlen(val_str)){
			if(is_key(val_str)){
				if(NULL == retrieve_key(val_str, db)){
					free(new_vals);
					return false;
				}
			}
			else if(!is_num(val_str)){
				free(new_vals);
				return false;
			}
		}
	}
	free(new_vals);
	return true;
}


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
int check_valid_key(char* key, database_t* db){
	if(!is_key(key))
		return 2;

	entry_t* cursor = db->entry_head;

	while(NULL != cursor){
		if(!strcmp(cursor->key, key))
			return 1;
		cursor = cursor->next;
	}

	return 0;
}


/*
 *is_num
 *checks if a given string is a number (contains only digits or '-' as first char)
 *
 *char* str:: string to check
 *
 *returns true if the string is a number otherwise false
 */
bool is_num(char* str){
	int i = 0;
	while('\0' != str[i]){
		if((0 == i) & ('-' == str[i])){
			//do nothing
			i--;
			i++;
		}
		else if(!isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}	



/*
 *is_key
 *checks if a given string is a valid key
 *    starts with a letter and then alphanumerics
 *
 *char* str:: string to check
 *
 *returns true if the string is a valid key otherwise false
 */
bool is_key(char* str){
	if(MAX_KEY < strlen(str)){
		return false;
	}

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


/*
 *retrieve_key
 *gets an entry with a specific key from the database
 *
 *char* key:: key of the entry to retrieve
 *database_t* db:: database to extract entry from
 *
 *returns the entry if the key exists in the db otherwise NULL
 */
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


/*
 *link_elements
 *links the values and adds them to the end of entry
 *
 *char* values:: string of elements to link
 *entry_t* entry:: entry to add elements to
 *
 *returns true if successfully completed, otherwise false
 */
bool link_elements(char* values, entry_t* entry, database_t* db){
	element_t* head;
	element_t* new_element;
	element_t* prev_element;
	entry_t** forwards = NULL;
	int num_general = 0;
	bool is_simple = true;
	int i = 0;

	char* new_vals = strdup(values);
	char* value_dup = new_vals;

	while(value_dup){
		char* val_str = strsep(&value_dup, " ");
		if(0 < strlen(val_str)){
			new_element = malloc(sizeof(element_t));

			if(0 == i){
				//store head value
				head = new_element;
			}else{
				prev_element->next = new_element;
			}

			if(is_key(val_str)){
				//general entry
				is_simple = false;
				entry_t* link = retrieve_key(val_str, db);
				if(NULL == link){
					printf("no such key\n");
					free(new_vals);
					free(forwards);
					return false;
				}

				else if(0 == strcmp(link->key, entry->key)){
					printf("not permitted\n");
					free(new_element);
					free(new_vals);
					free(forwards);
					return false;
				}
				num_general++;

				forwards = realloc(forwards, num_general * sizeof(entry_t));
				forwards[num_general-1] = link;

				new_element->entry = link;
				new_element->type = ENTRY;
			}

			else{
				new_element->value = atoi(val_str);
				new_element->type = INTEGER;
			}

			new_element->prev = prev_element;
			prev_element = new_element;
			i++;
		}
	}

	new_element->next = NULL;
	free(new_vals);

	if(0 == i){
		head = NULL;
	}


	if(NULL == entry->head){
		entry->head = head;
	}

	else{
		element_t* cursor = entry->head;
		while(NULL != cursor->next){
			cursor = cursor->next;
		}
		cursor->next = head;
		if(NULL != head){
			head->prev = cursor;		
		}
	}

	entry->length += i;
	entry->forward = NULL;
	if(0 == entry->backward_size){
		entry->backward = NULL;	
	}
	

	//manage general entries
	if(!is_simple){
		for(int j = 0; j < num_general; j++){
			entry_t* reference = forwards[j];
			add_reference(entry, reference);
		}
	}
	entry->is_simple = is_simple && entry->is_simple;
	free(forwards);

	if(entry->head != NULL){
		entry->head->prev = NULL;
	}

	return true;
}


/*
 *entry_add
 *adds entry to database
 *
 *database_t* db:: database to add to
 *entry_t* entry:: entry to add
 *
 *returns number of items in the database
 */
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


/*
 *add_reference
 *links reference as forward of original and original as backward of reference
 *
 *entry_t* original:: entry holding the reference as an element
 *entry_t* reference:: element of original entry
 *
 *returns nothing
 */
void add_reference(entry_t* original, entry_t* reference){
	
	size_t f_size = original->forward_size;
	size_t b_size = reference->backward_size;

	original->forward = realloc(
		original->forward, 
		(f_size + 1) * sizeof(entry_t*));

	reference->backward = realloc(
		reference->backward, 
		(b_size + 1) * sizeof(entry_t*));

	original->forward[f_size] = reference;
    reference->backward[b_size] = original;

	original->forward_size++;
	reference->backward_size++;

}


/*
 *list_forward
 *lists the forward references of an entry
 *
 *entry_t* entry:: entry to list forward references of
 *
 *returns nothing
 */
void list_forward(entry_t* entry){
	if(NULL == entry){
		printf("no such key");
		return;
	}

	if(0 == entry->forward_size){
		printf("nil");
		return;
	}

	key_list_t* head = list_forward_keys(entry);

	sort_keys(head);

	key_list_t* cursor = head;
	while(NULL != cursor){
		if(NULL != cursor->prev){
			printf(", ");
		}
		printf("%s", cursor->key);
		cursor = cursor->next;
	}

	clear_keys(head);
}


/*
 *list_forward_keys
 *recursively finds unique keys for entry and forward references
 *assumes at least 1 forward reference is present
 *
 *entry_t* entry:: entry to list keys of
 *
 *returns a linked list of unique keys
 */
key_list_t* list_forward_keys(entry_t* entry){
	key_list_t* head = malloc(sizeof(key_list_t));
	head->prev = NULL;
	head->next = NULL;
	strcpy(head->key, "\0");

	for(int i = 0; i < entry->forward_size; i++){
		
		//check key is unique
		entry_t* reference = entry->forward[i];
		bool unique = true;
		key_list_t* cursor = head;
		while(unique){
			if(0 == strcmp(cursor->key, reference->key)){
				unique = false;
			}
			if(NULL == cursor->next)
				break;
			else
				cursor = cursor->next;
		}

		//if unique add key
		if(unique){
			//first entry
			if(0 == strlen(head->key)){
				strcpy(head->key, reference->key);
			}
			else{
				key_list_t* new_key = malloc(sizeof(key_list_t));
				strcpy(new_key->key, reference->key);
				new_key->next = NULL;
				new_key->prev = cursor;
				cursor->next = new_key;
			}
		}

		//recurse for more keys;
		if(0 < reference->forward_size){
			key_list_t* sub_list = list_forward_keys(reference);

			key_list_t* sub_cursor = sub_list;

			while(NULL != sub_cursor){
				cursor = head;
				unique = true;
				while(unique){
					if(0 == strcmp(cursor->key, sub_cursor->key)){
						unique = false;
					}

					if(NULL == cursor->next)
						break;
					else
						cursor = cursor->next;
				}

				//if unique add reference
				if(unique){
					key_list_t* sub_key = malloc(sizeof(key_list_t));
					strcpy(sub_key->key, sub_cursor->key);
					sub_key->next = NULL;
					sub_key->prev = cursor;
					cursor->next = sub_key;
				}
				sub_cursor = sub_cursor->next;
			}

			clear_keys(sub_list);

		}
	}

	return head;
}


/*
 *sort_keys
 *bubble sorts an array of pointers to keys
 *called by list_forward and list_backward
 *
 *key_list_t* key_list:: list of keys to sort
 *
 *returns nothing
 */
void sort_keys(key_list_t* head){
	int length = 0;

	key_list_t* cursor = head;

	while(NULL != cursor){
		length++;
		cursor = cursor->next;
	}

	for(int i = 0; i < length; i++){
		key_list_t* current = head;
		key_list_t* next = head->next;
		for(int j = 0; j < length - i - 1; j++){
			if(0 < strcmp(current->key, next->key)){
				char temp[MAX_KEY];
				strcpy(temp, current->key);
				strcpy(current->key, next->key);
				strcpy(next->key, temp);
			}
			current = next;
			next = next->next;
		}
	}
}


/*
 *clear_keys
 *frees the allocated memory for a key list
 *
 *key_list_t* head:: head of the list to free
 *
 *returns nothing
 */
void clear_keys(key_list_t* head){
	while(NULL != head){
		key_list_t* next = head->next;
		free(head);
		head = next;
	}
}


/*
 *list_backward
 *lists the backward references of an entry
 *
 *entry_t* entry:: entry to list backward references of
 *
 *returns nothing
 */
void list_backward(entry_t* entry){
	if(NULL == entry){
		printf("no such key");
		return;
	}

	if(0 == entry->backward_size){
		printf("nil");
		return;
	}

	key_list_t* head = list_backward_keys(entry);

	sort_keys(head);

	key_list_t* cursor = head;
	while(NULL != cursor){
		if(NULL != cursor->prev){
			printf(", ");
		}
		printf("%s", cursor->key);
		cursor = cursor->next;
	}

	clear_keys(head);
}


/*
 *list_backward_keys
 *recursively finds unique keys for entry and backward references
 *assumes at least 1 backward reference is present
 *
 *entry_t* entry:: entry to list keys of
 *
 *returns a linked list of unique keys
 */
key_list_t* list_backward_keys(entry_t* entry){
	key_list_t* head = malloc(sizeof(key_list_t));
	head->prev = NULL;
	head->next = NULL;
	strcpy(head->key, "\0");

	for(int i = 0; i < entry->backward_size; i++){
		
		//check key is unique
		entry_t* reference = entry->backward[i];
		bool unique = true;
		key_list_t* cursor = head;
		while(unique){
			if(0 == strcmp(cursor->key, reference->key)){
				unique = false;
			}
			if(NULL == cursor->next)
				break;
			else
				cursor = cursor->next;
		}

		//if unique add key
		if(unique){
			//first entry
			if(0 == strlen(head->key)){
				strcpy(head->key, reference->key);
			}
			else{
				key_list_t* new_key = malloc(sizeof(key_list_t));
				strcpy(new_key->key, reference->key);
				new_key->next = NULL;
				new_key->prev = cursor;
				cursor->next = new_key;
			}
		}

		//recurse for more keys;
		if(0 < reference->backward_size){
			key_list_t* sub_list = list_backward_keys(reference);

			key_list_t* sub_cursor = sub_list;

			while(NULL != sub_cursor){
				cursor = head;
				unique = true;
				while(unique){
					if(0 == strcmp(cursor->key, sub_cursor->key)){
						unique = false;
					}

					if(NULL == cursor->next)
						break;
					else
						cursor = cursor->next;
				}

				//if unique add reference
				if(unique){
					key_list_t* sub_key = malloc(sizeof(key_list_t));
					strcpy(sub_key->key, sub_cursor->key);
					sub_key->next = NULL;
					sub_key->prev = cursor;
					cursor->next = sub_key;
				}
				sub_cursor = sub_cursor->next;
			}

			clear_keys(sub_list);

		}
	}

	return head;
}


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
entry_t* entry_delete(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(NULL == entry){
		printf("no such key\n");
		return NULL;
	}

	else if(0 < entry->backward_size){
		printf("not permitted\n");
		return NULL;
	}

	else{
		//check first entry (no previous entry)
		delete_elements(entry);
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
	}
}

/*
 *delete_elements
 *clears elements from entry and frees memory
 *
 *entry_t* entry:: entry to clear
 *
 *returns nothing
 */
void delete_elements(entry_t* entry){
	if(NULL == entry){
		return;
	}

	element_t* cursor = entry->head;

	while(NULL != cursor){
		element_t* next = cursor->next;

		if(cursor->type == ENTRY){
			delete_reference(entry, cursor->entry);
		}

		free(cursor);

		cursor = next;
	}
}

/*
 *delete_reference
 *removes reference as forward of original and original as backward of reference
 *
 *entry_t* original:: entry holding the reference as an element
 *entry_t* reference:: element of original entry
 *
 *returns nothing
 */
void delete_reference(entry_t* original, entry_t* reference){
	entry_t* forward_cursor = original->forward[0];
	entry_t* backward_cursor = reference->backward[0];
	size_t f_count = 0;
	size_t b_count = 0;


	//get forward reference and offset
	while((NULL != forward_cursor) & (reference != forward_cursor)){
		forward_cursor = original->forward[f_count + 1];
		f_count++;
	}


	//get backwards reference and offset
	while((NULL != backward_cursor) & (original != backward_cursor)){
		backward_cursor = reference->backward[b_count + 1];
		b_count++;
	}


	//check references exist for both
	if((NULL == backward_cursor) | (NULL == forward_cursor)){
		//they are not forward / backward references
		return;
	}


	//edit forward references
	if(1 == original->forward_size){
		free(original->forward);
		original->forward_size = 0;
		original->forward = NULL;
		original->is_simple = true;
	}

	else{

		for(int i = f_count; i < original->forward_size - 1; i++){
			original->forward[i] = original->forward[i+1];
		}


		
		original->forward_size--;
		entry_t** new_back = realloc(original->forward, 
			sizeof(entry_t*) * (original->forward_size));
		original->forward = new_back;
	}
	
	//edit backward references
	if(1 == reference->backward_size){
		free(reference->backward);
		reference->backward_size = 0;
		reference->backward = NULL;
	}

	else{


		for(int i = b_count; i < reference->backward_size - 1; i++){
			reference->backward[i] = reference->backward[i+1];
		}

		reference->backward_size--;
		reference->backward = realloc(reference->backward, 
			sizeof(entry_t*) * (reference->backward_size));
	}
}	


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
void entry_append(char* key, char* values, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(NULL == entry){
		printf("no such key\n");
		return;
	}

	if(!check_values(values, db)){
		printf("no such key\n");
		return;
	}

	link_elements(values, entry, db);
	printf("ok\n");
}


/*
 *display_links
 *used for debugging
 *displays the value and next and prev links for each element in an entry
 *returns nothing
 */
void display_links(entry_t* entry){
	element_t* cursor = entry->head;

	while(NULL != cursor){

		if(cursor->type == ENTRY){
			printf("Value: %s\t", cursor->entry->key);
		}else{
			printf("Value: %d\t", cursor->value);
		}

		printf("Next: ");
		if(cursor->next == NULL){
			printf("NULL\t");
		}
		else if(cursor->next->type == ENTRY){
			printf("%s", cursor->next->entry->key);
		}
		else{
			printf("%d", cursor->next->value);
		}

		printf("\t\tPrev: ");
		if(cursor->prev == NULL){
			printf("NULL\n");
		}
		else if(cursor->prev->type == ENTRY){
			printf("%s\n", cursor->prev->entry->key);
		}
		else{
			printf("%d\n", cursor->prev->value);
		}

		cursor = cursor->next;
	}
}

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
void entry_push(char* key, char* values, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(NULL == entry){
		printf("no such key\n");
		return;
	}

	if(!check_values(values, db)){
		printf("no such key\n");
		return;
	}

	push_elements(values, entry, db);
	printf("ok\n");
}

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
bool push_elements(char* values, entry_t* entry, database_t* db){
	element_t* new_element;
	element_t* prev_element = entry->head;
	entry_t** forwards = NULL;
	int num_general = 0;
	bool is_simple = true;
	int i = 0;

	char* new_vals = strdup(values);
	char* value_dup = new_vals;
	while(value_dup){
		char* val_str = strsep(&value_dup, " ");
		if(0 < strlen(val_str)){
			new_element = malloc(sizeof(element_t));

			if(is_key(val_str)){
				//general entry
				is_simple = false;
				entry_t* link = retrieve_key(val_str, db);
				if(NULL == link){
					printf("no such key\n");
					free(new_vals);
					free(forwards);
					return false;
				}
				num_general++;

				forwards = realloc(forwards, num_general * sizeof(entry_t));
				forwards[num_general-1] = link;

				new_element->entry = link;
				new_element->type = ENTRY;
			}

			else{
				new_element->value = atoi(val_str);
				new_element->type = INTEGER;
			}

			if(NULL != prev_element){
				prev_element->prev = new_element;
			}

			new_element->next = prev_element;
			prev_element = new_element;
			i++;
		}
	}




	free(new_vals);
	entry->length += i;

	if(0 == i){
		return true;
	}

	entry->head = new_element;

	new_element->prev = NULL;





	//manage general entries
	if(!is_simple){
		entry->forward = realloc(entry->forward, 
			sizeof(entry_t) * (entry->forward_size + num_general));

		for(int j = 0; j < num_general; j++){
			entry_t* reference = forwards[j];
			add_reference(entry, reference);
		}
	}
	entry->is_simple = is_simple && entry->is_simple;
	free(forwards);

	entry->head->prev = NULL;

	return true;
}


/*
 *entry_pop
 *deletes and prints the first element of an entry
 *
 *char* key:: key of entry to delete
 *database_t* db:: database containing entry
 *
 *returns nothing
 */
void entry_pop(char* key, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(NULL == entry){
		printf("no such key\n");
		return;
	}

	else if(0 == entry->length){
		printf("nil\n");
		return;
	}

	if(entry->head->type == INTEGER){
		printf("%d\n", entry->head->value);
	}

	else{
		printf("%s\n", entry->head->entry->key);
		delete_reference(entry, entry->head->entry);
	}

	if(1 == entry->length){
		free(entry->head);
		entry->head = NULL;
	}

	else{
		entry->head = entry->head->next;
		free(entry->head->prev);
		entry->head->prev = NULL;
	}

	entry->length--;

}


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
void entry_pluck(char* key, int index, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(NULL == entry){
		printf("no such key\n");
		return;
	}


	else if(entry->length < index || 1 > index){
		printf("index out of range\n");
	}

	else if(1 == entry->length){
		if(entry->head->type == INTEGER){
			printf("%d\n", entry->head->value);
		}

		else{
			printf("%s\n", entry->head->entry->key);
			delete_reference(entry, entry->head->entry);
		}
		entry->length--;

		free(entry->head);
		entry->head = NULL;
	}

	else{

		element_t* cursor = entry->head;
		for(int i = 1; i < index; i++){
			cursor = cursor->next;
		}


		if(cursor->type == INTEGER){
			printf("%d\n", cursor->value);
		}
		else{
			printf("%s\n", cursor->entry->key);
			delete_reference(entry, cursor->entry);
		}


		if(1 == index){
			if(NULL == cursor->next){
				entry->head = NULL;		
			}
			else{
				cursor->next->prev = NULL;
				entry->head = cursor->next;	
			}
			
		}else if(entry->length == index){
			cursor->prev->next = NULL;
		}else{
			cursor->prev->next = cursor->next;
			cursor->next->prev = cursor->prev;
		}
		free(cursor);
		entry->length--;
	}
}


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
void entry_pick(char* key, int index, database_t* db){
	entry_t* entry = retrieve_key(key, db);

	if(NULL == entry){
		printf("no such key\n");
	}

	else if(entry->length < index || 1 > index){
		printf("index out of range\n");
	}

	else{
		element_t* cursor = entry->head;
		for(int i = 1; i < index; i++){
			cursor = cursor->next;
		}


		if(cursor->type == INTEGER){
			printf("%d\n", cursor->value);
		}
		else{
			printf("%s\n", cursor->entry->key);
		}
	}
}


/*
 *check_simple
 *checks if an entry has any general elements
 *
 *entry_t* entry:: entry to check
 *
 *returns true if entry is simple otherwise false
 */
bool check_simple(entry_t* entry){
	if(NULL == entry){
		return true;
	}

	element_t* cursor = entry->head;
	while(NULL != cursor){
		if(cursor->type == ENTRY){
			return false;
		}
	}
	return true;
}


/*
 *find_min
 *recursively finds the minimum for a given entry
 *
 *entry_t* entry:: entry to find min
 *
 *returns the min of the entry (or references)
 */
int find_min(entry_t* entry){
	// if(NULL == entry){
	// 	return NAN;
	// }

	element_t* cursor = entry->head;
	//float min = INFINITY;
	int min;
	// if(NULL == cursor){
	// 	return NAN;
	// }
	if(cursor->type == INTEGER){
		min = cursor->value;
	}
	else{
		min = find_min(cursor->entry);
	}
	cursor = cursor->next;


	while(NULL != cursor){
		if(cursor->type == INTEGER){
			if(min > cursor->value){
				min = cursor->value;
			}
		}

		else if(0 < cursor->entry->length){
			int reference_min = find_min(cursor->entry);
			if((min > reference_min) /* & (NAN != reference_min) & */){
				min = reference_min;
			}
		}
		
		cursor = cursor->next;
	}

	return min;
}


/*
 *find_max
 *recursively finds the max for a given entry
 *
 *entry_t* entry:: entry to find max
 *
 *returns the max of the entry (or references)
 */
int find_max(entry_t* entry){
	// if(NULL == entry){
	// 	return NAN;
	// }

	element_t* cursor = entry->head;
	//float max = -INFINITY;
	int max;
	if(cursor->type == INTEGER){
		max = cursor->value;
	}
	else{
		max = find_max(cursor->entry);
	}
	cursor = cursor->next;

	while(NULL != cursor){
		if(cursor->type == INTEGER){
			if(max < cursor->value){
				max = cursor->value;
			}
		}
		
		else if(0 < cursor->entry->length){
			int reference_max = find_max(cursor->entry);
			if((max < reference_max) /* & (NAN != reference_max)*/){
				max = reference_max;
			}
		}
		
		cursor = cursor->next;
	}

	return max;
}


/*
 *find_sum
 *finds the sum of an entry including references
 *
 *entry_t* entry:: entry to sum
 *
 *returns the sum of the entry (and references)
 */
int find_sum(entry_t* entry){
	if(NULL == entry){
		return 0;
	}

	element_t* cursor = entry->head;
	int sum = 0;

	while(NULL != cursor){
		if(cursor->type == INTEGER){
			sum += cursor->value;
		}
		
		else{
			sum += find_sum(cursor->entry);
		}
		
		cursor = cursor->next;
	}

	return sum;
}


/*
 *find_length
 *finds the number of items in an entry and its references
 *
 *entry_t* entry:: entry to find number of elements
 *
 *returns the length
 */
int find_length(entry_t* entry){
	if(NULL == entry){
		return 0;
	}

	element_t* cursor = entry->head;
	int length = 0;

	while(NULL != cursor){
		if(cursor->type == INTEGER){
			length += 1;
		}
		
		else{
			length += find_length(cursor->entry);
		}
		
		cursor = cursor->next;
	}

	return length;
}


/*
 *bubblesort
 *bubblesorts given simple entry
 *
 *entry_t* entry:: entry to be sorted
 *
 *returns nothing
 */
void bubblesort(entry_t* entry){

	if(NULL == entry){
		printf("no such key\n");
		return;
	}

	if(!entry->is_simple){
		printf("not permitted\n");
		return;
	}

	if(0 == entry->length){
		printf("ok\n");
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

/*
 *entry_uniq
 *removes adjacent repeated values in simple entry
 *
 *entry_t* entry:: entry to modify
 *
 *returns nothing
 */
void entry_uniq(entry_t* entry){
	if(NULL == entry){
		printf("no such key\n");
		return;
	}

	if(!entry->is_simple){
		printf("not permitted\n");
		return;
	}

	if(0 == entry->length){
		printf("ok\n");
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

/*
 *entry_reverse
 *reverses the order of a simple entry
 *
 *entry_t* entry:: entry to reverse
 *
 *returns nothing
 */
void entry_reverse(entry_t* entry){

	if(NULL == entry){
		printf("no such key\n");
		return;
	}

	if(!entry->is_simple){
		printf("not permitted\n");
		return;
	}

	if(0 == entry->length){
		printf("ok\n");
		return;
	}

	element_t* cursor = entry->head;
	cursor->prev = NULL;

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


/*
 *entry_type
 *prints the entry type
 *
 *entry_t* entry:: entry to get type of
 *
 *returns nothing
 */
void entry_type(entry_t* entry){
	if(NULL == entry){
		printf("no such key\n");
	}
	else if(entry->is_simple){
		printf("simple\n");
	}else{
		printf("general\n");
	}
}


/*
 *save_snapshot
 *saves a snapshot of the database at a given time
 *
 *database_t* db:: database to take snapshot of
 *
 *returns nothing
 */
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
	if(NULL == entry_cursor){
		snap->head = NULL;
		return;
	}

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
		
		entry_cursor = entry_cursor->next;
	}

	prev_copy->next = NULL;


	//set forwards and backward references
	entry_t* original_cursor = db->entry_head;
	entry_t* copy_cursor = snap->head;

	while((NULL != original_cursor) & (NULL != copy_cursor)){
		if(!original_cursor->is_simple){
			element_t* original_element_cursor = original_cursor->head;
			element_t* copy_element_cursor = copy_cursor->head;

			while(NULL != original_element_cursor){
				if(original_element_cursor->type == ENTRY){
					char* key = original_element_cursor->entry->key;
					entry_t* reference = get_snapshot_entry(key, snap);
					copy_element_cursor->entry  = reference;
					copy_element_cursor->type = ENTRY;

					add_reference(copy_cursor, reference);
				}
				original_element_cursor = original_element_cursor->next;
				copy_element_cursor = copy_element_cursor->next;
			}
		}
		original_cursor = original_cursor->next;
		copy_cursor = copy_cursor->next;
	}

	return;
}


/*
 *copy_entry
 *copies a given entry and allocates memory so none is shared
 *
 *entry_t* entry:: entry to be copied
 *
 *returns a copy of the entry
 */
entry_t* copy_entry(entry_t* entry){
	if(NULL == entry)
		return NULL;

	entry_t* copy = malloc(sizeof(entry_t));

	strcpy(copy->key, entry->key);
	copy->length = entry->length;
	copy->is_simple = entry->is_simple;
	copy->forward_size = 0;
	copy->backward_size = 0;
	copy->forward = NULL;
	copy->backward = NULL;

	element_t* cursor = entry->head;
	if(NULL == cursor){
		copy->head = NULL;
		return copy;
	}

	element_t* prev_element = NULL;
	while(NULL != cursor){
		element_t* new_element = malloc(sizeof(element_t));
		
		if(cursor->type == INTEGER){
			new_element->type = INTEGER;
			new_element->value = cursor->value;
		}
		else{
			new_element->type = ENTRY;
		}

		new_element->prev = prev_element;
		if(NULL != prev_element){
			prev_element->next = new_element;
		}else{
			copy->head = new_element;
		}
		new_element->next = NULL;
		prev_element = new_element;
		cursor = cursor->next;
	}
	return copy;
}


/*
 *get_snapshot_entry
 *retrieves an entry with a given key from the snapshot
 *
 *char* key:: key of the entry to get
 *snapshot_t* snap:: snapshot to get key from
 *
 *returns the corresponding entry
 */
entry_t* get_snapshot_entry(char* key, snapshot_t* snap){
	entry_t* cursor = snap->head;

	while(cursor != NULL){
		if(0 == strcmp(key, cursor->key)){
			return cursor;
		}
		cursor = cursor->next;
	}

	return NULL;
}


/*
 *snapshot_checkout
 *sets the db as the given snapshot
 *
 *database_t* db:: database to change
 *int id:: id of desired snapshot
 *
 *returns nothing
 */
void snapshot_checkout(database_t* db, int id){
	snapshot_t* cursor = db->snapshot_head;

	while(NULL != cursor){
		if(id == cursor->id){

			//get rid of old entries
			remove_entries(db);

			//init cursors and new db entry head
 			entry_t* snap_entry_cursor = cursor->head;

 			if(NULL == snap_entry_cursor){
 				db->entry_head = NULL;
 				printf("ok\n");
 				return;
 			}

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

			//set forwards and backward references

			entry_t* original_cursor = cursor->head;
			entry_t* copy_cursor = db->entry_head;

			while((NULL != original_cursor) & (NULL != copy_cursor)){
				if(!original_cursor->is_simple){
					element_t* original_element_cursor = original_cursor->head;
					element_t* copy_element_cursor = copy_cursor->head;

					while(NULL != original_element_cursor){
						if(original_element_cursor->type == ENTRY){
							char* key = original_element_cursor->entry->key;
							entry_t* reference = retrieve_key(key, db);
							copy_element_cursor->entry  = reference;
							copy_element_cursor->type = ENTRY;

							add_reference(copy_cursor, reference);
						}
						original_element_cursor = original_element_cursor->next;
						copy_element_cursor = copy_element_cursor->next;
					}
				}
				original_cursor = original_cursor->next;
				copy_cursor = copy_cursor->next;
			}
			return;
		}

		cursor = cursor->next;
	}

	printf("no such snapshot\n");
}


/*
 *remove_entries
 *removes and frees entries from database
 *
 *database_t* db:: database to clear
 *
 *returns nothing
 */
void remove_entries(database_t* db){
	entry_t* entry_cursor = db->entry_head;

	//delete elements from each entry
	while(NULL != entry_cursor){
		delete_elements(entry_cursor);
		entry_cursor = entry_cursor->next;
	}

	//delete the entries
	entry_cursor= db->entry_head;
	while(NULL != entry_cursor){
		entry_t* next = entry_cursor->next;

		free(entry_cursor);

		entry_cursor = next;
	}
}

/*
 *delete_snapshot_id
 *deletes snapshot with given id
 *
 *database_t*:: database containing snapshot
 *int id:: id of snapshot to delet
 *
 *returns nothing
 */
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


/*
 *delete_snapshot
 *deletes snapshot from the database
 *
 *snapshot_t* snap; snapshot to delete
 *database_t* db:: database containing snapshot
 *
 *returns nothing
 */
void delete_snapshot(snapshot_t* snap, database_t* db){
	entry_t* entry_cursor = snap->head;

	//delete elements from each entry
	while(NULL != entry_cursor){
		delete_elements(entry_cursor);
		entry_cursor = entry_cursor->next;
	}

	//delete the entries
	entry_cursor = snap->head;
	while(NULL != entry_cursor){
		entry_t* next = entry_cursor->next;

		free(entry_cursor);

		entry_cursor = next;
	}


	//set links for linked list
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


/*
 *snapshot_rollback
 *restores to given snapshot and deletes newer ones
 *
 *database_t* db:: database containing snapshots
 *int id:: id of snapshot to revert to
 *
 *returns nothing
 */
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

			//set forwards and backward references
			entry_t* original_cursor = cursor->head;
			entry_t* copy_cursor = db->entry_head;
			while((NULL != original_cursor) & (NULL != copy_cursor)){
				if(!original_cursor->is_simple){
					element_t* original_element_cursor = original_cursor->head;
					element_t* copy_element_cursor = copy_cursor->head;

					while(NULL != original_element_cursor){
						if(original_element_cursor->type == ENTRY){
							char* key = original_element_cursor->entry->key;
							entry_t* reference = retrieve_key(key, db);
							copy_element_cursor->entry  = reference;
							copy_element_cursor->type = ENTRY;

							add_reference(copy_cursor, reference);
						}
						original_element_cursor = original_element_cursor->next;
						copy_element_cursor = copy_element_cursor->next;
					}
				}
				original_cursor = original_cursor->next;
				copy_cursor = copy_cursor->next;
			}
		}

		else
			cursor = cursor->next;

	}

	if(!found){
		printf("no such snapshot\n");
		return;
	}

	//delete snapshots afterwards
	else if(cursor->next != NULL){
		cursor = cursor->next;
		cursor->prev->next = NULL;
		while(NULL != cursor){
			snapshot_t* next_snap = cursor->next;
			delete_snapshot(cursor, db);
			cursor = next_snap;
		}
	}
}



/*
 *entry_purge
 *attempts to delete entry from db and all snapshot
 *
 *database_t* db:: database containing entry and snapshots
 *char* key:: key of entry to delete
 *
 *returns nothing
 */
void entry_purge(database_t* db, char* key){
	bool found = false;

	//check for entry and if purge can occur
	
	//check entries
	entry_t* entry_cursor = db->entry_head;
	while(NULL != entry_cursor){
		if(0 == strcmp(key, entry_cursor->key)){
			found = true;
			if(0 != entry_cursor->backward_size){
				printf("not permitted\n");
				return;
			}
		}
		entry_cursor = entry_cursor->next;
	}

	snapshot_t* snap_cursor = db->snapshot_head;
	while(snap_cursor != NULL){
		entry_t* snap_entry_cursor = snap_cursor->head;
		while (NULL != snap_entry_cursor){
			if(0 == strcmp(key, snap_entry_cursor->key)){
				found = true;
				if(0 != snap_entry_cursor->backward_size){
					printf("not permitted\n");
					//printf("snapshot: %d\n", snap_cursor->id);
					return;
				}
			}
			snap_entry_cursor = snap_entry_cursor->next;
		}
		snap_cursor = snap_cursor->next;
	}

	if(!found){
		printf("ok\n");
		return;
	}

	entry_cursor = db->entry_head;
	bool printed = false;
	while(NULL != entry_cursor){
		if(0 == strcmp(key, entry_cursor->key)){
			entry_t* next_entry = entry_cursor->next;
			//supress output
			//int old_stdout = dup(1);
			//freopen("/dev/null", "w", stdout);
			free(entry_delete(key, db));
			printed = true;
			//fclose(stdout);

			// //reset stdout
			// stdout = fdopen(old_stdout, "w");
			entry_cursor = next_entry;
		}
		else
			entry_cursor = entry_cursor->next;
	}


	snap_cursor = db->snapshot_head;
	while(snap_cursor != NULL){
		entry_t* snap_entry_cursor = snap_cursor->head;
		while (NULL != snap_entry_cursor){
			entry_t* next = snap_entry_cursor->next;
			if(0 == strcmp(key, snap_entry_cursor->key)){
				//delete entry from snapshot
				if((NULL != snap_entry_cursor->next) & 
					(NULL != snap_entry_cursor->prev)){
					//middle case
					snap_entry_cursor->next->prev = snap_entry_cursor->prev;
					snap_entry_cursor->prev->next = snap_entry_cursor->next;
				}
				else if(NULL != snap_entry_cursor->next){
					//first case
					snap_cursor->head = snap_entry_cursor->next;
					snap_entry_cursor->next->prev = NULL;
				}
				else if(NULL != snap_entry_cursor->prev){
					//last case
					snap_entry_cursor->prev->next = NULL;
				}
				else{
					//only case
					snap_cursor->head = NULL;
				}

				delete_elements(snap_entry_cursor);
				free(snap_entry_cursor);
			}
			snap_entry_cursor = next;
		}
		snap_cursor = snap_cursor->next;
	}

	if(!printed)
		printf("ok\n");
}


/*
 *clear_database
 *frees all allocated memory
 *
 *database_t* db:: database to clear
 *
 *returns nothign
 */
void clear_database(database_t* db){
	entry_t* entry_cursor = db->entry_head;

	while(NULL != entry_cursor){
		entry_t* next_entry = entry_cursor->next;

		//free elements from each entry
		delete_elements(entry_cursor);

		entry_cursor = next_entry;
	}

	entry_cursor = db->entry_head;

	while(NULL != entry_cursor){
		entry_t* next_entry = entry_cursor->next;
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