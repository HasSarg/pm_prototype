all:
	g++ main.cpp project.cpp task.cpp -o pm

run:
	./pm

clean:
	rm -rf pm db.txt
