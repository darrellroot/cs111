all:
	gcc -std=c11 hello.c -o hello
	gcc -std=c11 helloTest.c -o helloTest
test:
	chmod +x hello
	./helloTest
clean:
	$(RM) hello helloTest
