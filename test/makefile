UTILDIR=../util/
UTILOBJ=convert.o str_op.o

app: test_attack.c ../ecc-src/ecc.c $(UTILOBJ)
	gcc -g -I../ecc-src -I../util $^ -o $@

convert.o: $(UTILDIR)convert.c
	gcc -g -c $^ -o $@

str_op.o: $(UTILDIR)str_op.c
	gcc -g -c $^ -o $@

.PHONY: clean
clean:
	@rm -rf app sign.log nonces.log key.txt $(UTILOBJ)