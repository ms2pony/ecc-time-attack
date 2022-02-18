../out/app: attack.c ../ecc-src/ecc.c ../util/bignum.c
	gcc -g -I../ecc-src -I../util $^ -o $@
test: attack.c ../ecc-src/ecc.c ../util/bignum.c
	gcc -g -I../ecc-src -I../util $^ -o app

clean:
	@rm ../out/temp/sign.log ../out/temp/nonces.log ../out/key.txt -rf
	@rm app -rf