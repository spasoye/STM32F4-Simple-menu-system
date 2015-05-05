#ifndef MENU_EVENT_H
#define	 MENU_EVENT_H

//These event can be set from anywhere in the program
//You can create your own events here

extern char menu_event_key;
extern char menu_key_read;

//Function to read an event. Pointer to an event is passed, and it return 0 or 1
char get_event(char* event);

char get_key(char a);

char read_key();
#endif