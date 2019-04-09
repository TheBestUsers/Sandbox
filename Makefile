build:sandbox detour.o libdetour.so test



sandbox:sandbox.c
	gcc  -O0 -o $@ $< -g 

detour.o:detour.c
	gcc -O0 -c -fPIC -o $@ $<

libdetour.so:detour.o
	gcc -O0 -shared -o $@ $< -ldl  

test:test.c
	gcc -O0 -o $@ $< -g

clean:
	rm  sandbox libdetour.so test detour.o
