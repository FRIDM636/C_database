#define MAX_DATA 512
#define MAX_ROWS 1000

struct Address {
        int id;
        int set;
        char name[MAX_DATA];
        char mail[MAX_DATA];
};

struct Database {
	struct Address rows[MAX_ROWS];
};

struct Connection{
	FILE * file;
	struct Database *db;
};

void Exit(const char *);
void Address_print(const struct Address *);
void Database_load(const struct Connection *);
struct Connection * Database_open(const char *, const char);
void Database_close(struct Connection *);
void Database_write(struct Connection *);
void Database_create(struct Connection *);
void Database_set(struct Connection *, int , char *, char *);
void Database_get(struct Connection *, int);
void Database_delete(struct Connection *, int);
void Database_list(struct Connection *);
