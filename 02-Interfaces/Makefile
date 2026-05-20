.PHONY : run clean

run : TablasDeConversion
	./TablasDeConversion

test : ConversionTest
	./ConversionTest

Conversion.o : Conversion.c Conversion.h

ConversionTest : ConversionTest.o Conversion.o

ConversionTest.o : ConversionTest.c Conversion.h

TablasDeConversion : TablasDeConversion.o Conversion.o

TablasDeConversion.o : TablasDeConversion.c Conversion.c Conversion.h

clean:
	rm TablasDeConversion.o ConversionTest.o Conversion.o TablasDeConversion ConversionTest