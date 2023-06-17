#include "linked.h"

int main(){
	entry_t* entry;

	char* key = "a";

	int values[] = {1,2,3,4,5};

	entry = cmd_set(key, values, 5);
	printf("%s: ", entry->key);
	cmd_get(entry);

	return 0;

}


//sets a particular key value pair
//will return the new entry
entry_t* cmd_set(char* key, int* values, int size){
	
	//allocate memory in the heap to new entry
	entry_t* new_entry = malloc(sizeof(entry_t));

	if(NULL == new_entry){
		//raise error
		return NULL;
	}

	//check_valid_key(key);
	strcpy(new_entry->key, key);

	//assign values
	//for each value in values, make a new element and add it to the entry
	
	
	element_t* new_element;
	element_t* prev_element = NULL;
	for(int i = 0; i < size; i++){
		new_element = malloc(sizeof(element_t));
		if(0 == i){		//first element of entry, set head accordingly
			new_entry->head = new_element;
		}else{
			prev_element->next = new_element;
		}
		if(NULL == new_element){
			//raise error
			return NULL;
		}
		new_element->value = values[i];
		printf("%d: %d\n", i, new_element->value);
		new_element->prev = prev_element;
		prev_element = new_element;
	}
	
	new_element->next = NULL;
	return new_entry;
}

void cmd_get(entry_t* entry){
	element_t* cursor = entry->head;

	printf("[");
	while(NULL != cursor){
		if(NULL != cursor->prev){
			printf(" ");
		}
		printf("%d", cursor->value);
		cursor = cursor->next;
	}
	printf("]\n");
	return;
}