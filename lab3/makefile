CC = gcc -std=c11 -Wall
FLAGS = -lgslcblas -lgsl -lm
FILE0 = resultO0.csv
FILE1 = resultO1.csv
FILE2 = resultO2.csv
FILE3 = resultO3.csv

compile:
	$(CC) $(FLAGS) -o main0 main.c -O0
	$(CC) $(FLAGS) -o main1 main.c -O1
	$(CC) $(FLAGS) -o main2 main.c -O2
	$(CC) $(FLAGS) -o main3 main.c -O3

tests:
	./main0 $(FILE0)
	./main1 $(FILE1)
	./main2 $(FILE2)
	./main3 $(FILE3)

clean:
	rm -rf main0 main1 main2 main3
