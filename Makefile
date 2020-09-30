
bin/samurai:
	mkdir bin
	gcc main.c -o bin/samurai
	chmod a+x bin/samurai

clean:
	rm -rf bin
