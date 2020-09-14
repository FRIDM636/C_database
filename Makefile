app: src/library.c src/database.c 
	gcc -o bin/prog src/library.c src/database.c
clean:
	rm -rf bin/*
