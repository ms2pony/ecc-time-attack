UTILDIR=../util/
UTILOBJ=convert.o str_op.o

../out/app: attack.c ../ecc-src/ecc.c $(UTILOBJ)
	gcc -g -I../ecc-src -I../util $^ -o $@

test: attack.c ../ecc-src/ecc.c $(UTILOBJ)
	gcc -g -I../ecc-src -I../util $^ -o app

convert.o: $(UTILDIR)convert.c
	gcc -g -c $^ -o $@

str_op.o: $(UTILDIR)str_op.c
	gcc -g -c $^ -o $@

.PHONY: clean
clean:
	@rm -rf ../out/app ../out/temp/sign.log ../out/temp/nonces.log ../out/key.txt $(UTILOBJ)
	@rm -rf app attack.sage.py