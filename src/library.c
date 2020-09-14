#include<stdio.h>
#include<stdlib.h>
#include"../headers/database.h"

int main(int argc, char ** argv)
{
	if(argc < 3)
		Exit("Usage app filename action [options]");
	char action = argv[2][0];
	char * file_name = argv[1];
	struct Connection * connection = Database_open(file_name, action);
	int id = 0;


	if(argc > 3)
		id = atoi(argv[3]);
	if(id >=MAX_ROWS)
		Exit("Database is FULL!");

	switch(action){
		case 'c':
			Database_create(connection);
			Database_write(connection);
			break;
		case 'g':
			if(argc != 4)
				Exit("Need an ID");
			Database_get(connection,id);
			break;
		case 's':
			if(argc != 6)
				Exit("Need ID, Name and Mail to set");
			Database_set(connection,id,argv[4],argv[5]);
			Database_write(connection);
			break;
		case 'd':
			if(argc != 4)
				Exit("Need ID to delete");
			Database_delete(connection,id);
			Database_write(connection);
			break;
		case 'l':
			Database_list(connection);
			break;
		default:
			Exit("Invalid action c: create, s: set, g:get, d: delete, l:list");
			break;
	}

	Database_close(connection);

    return 0;
}
