build:sandbox detour.o libdetour.so test



sandbox:sandbox.c
	gcc  -o $@ $< -g 

detour.o:detour.c
	gcc -c -fPIC -o $@ $<

libdetour.so:detour.o
	gcc -shared -o $@ $< -ldl  

test:test.c
	gcc -o $@ $< -g

clean:
	rm  sandbox libdetour.so test detour.o