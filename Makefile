all:
	g++ main.cpp project.cpp task.cpp -o pm

clean:
	rm -rf pm db.txt
