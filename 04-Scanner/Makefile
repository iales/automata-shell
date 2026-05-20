.PHONY: runScanner runParser clean

runScanner: ScannerTest
	./ScannerTest < TestScanner.c > Tokens.txt 

runMain: main
	./main < TestParser.c > output.txt 

ScannerTest: ScannerTest.c Scanner.c
	cc ScannerTest.c Scanner.c -o ScannerTest

main: main.c Parser.c Scanner.c
	cc main.c Parser.c Scanner.c -o main

clean:
	rm ScannerTest.exe Tokens.txt main.exe output.txt