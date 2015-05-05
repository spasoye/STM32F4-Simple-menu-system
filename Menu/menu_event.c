#include "menu_event.h"

char menu_event_key;
char menu_key_read = 0;


////Not used
char get_event(char* event){
	if (*event != 0){
		*event = 0;
		return 1;
	}
	else return 0;
}

char get_key(char a){
	if(menu_key_read == 0){
		if( menu_event_key == a){
			menu_key_read = 1;
			return 1;
		}
		return 0;
	}
	else return 0;
}

char read_key(){
	if(menu_key_read == 0){
		menu_key_read = 1;
		return menu_event_key;
	}
}