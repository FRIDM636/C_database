#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include"../headers/database.h"


void Exit(const char * message){
	if(errno)
		perror(message);
	else
		printf("Message: %s\n",message);
	exit(1);
}

void Address_print(const struct Address * address){
	printf("****** ID: %d ******\nSET: %d\nNAME: %s\nMAIL: %s\n",address->id, address->set, address->name, address->mail);
}


void Database_load(const struct Connection *connection){

	if(fread(connection->db, sizeof(struct Database),1,connection->file) != 1)
		Exit("Error loading database");
}

struct Connection * Database_open(const char *file_name, const char mode){

		struct Connection * connection = malloc(sizeof(struct Connection));

		if(!connection)
			Exit("Memory allocation error for connection");

		connection->db = malloc(sizeof(struct Database));

		if(!connection)
			Exit("Memory allocation error for database");

		if(mode == 'c')
			connection->file = fopen(file_name, "w");
		else{
			connection->file = fopen(file_name, "r+");
			if(connection->file)
				Database_load(connection);
			}
		if(!connection->file)
			Exit("Error making a connection");

	return connection;
}

void Database_close(struct Connection *connection)
{
    if(connection){
        if(connection->file)
            fclose(connection->file);
        if(connection->db)
            free(connection->db);
        free(connection);
    }
}

void Database_write(struct Connection *connection){
    rewind(connection->file);
    if(fwrite(connection->db, sizeof(struct Database), 1, connection->file) != 1)
        Exit("Error writing to database");
    if(fflush(connection->file) == -1)
        Exit("Error flushing file");
}

void Database_create(struct Connection *connection){

    int i = 0;
    for(i = 0; i< MAX_ROWS; ++i){
        struct Address address = {.id=i, .set = 0};
        connection->db->rows[i] = address;
    }
}

void Database_set(struct Connection *connection, int id, char name[], char mail[]){
	
	struct Address *address = &connection->db->rows[id];
	if(address->set == 1)
		Exit("Already set");
	else
		address->set = 1;
	
	if(!strncpy(address->name, name, MAX_DATA))
		Exit("Failed to set name");
	
	if(!strncpy(address->mail, mail, MAX_DATA))
		Exit("Failed to set mail1");
}

void Database_get(struct Connection * connection, int id){
	
	struct Address * address = &connection->db->rows[id];
	if(address->set)
		Address_print(address);
	else
		Exit("Data doesn\'t exist");
}

void Database_delete(struct Connection * connection, int id){
	
	struct Address address = {.id=id, .set=0};
	connection->db->rows[id] = address;
}
	
void Database_list(struct Connection *connection){
		int id = 0;
		struct Database *database = connection->db;
		while(++id < MAX_ROWS)
			if(database->rows[id].set)
				Address_print(&database->rows[id]);
}



