MAIN1 = echo
MAIN2 = pwd
MAIN3 = ls

GROUP1 = cp
GROUP2 = wc
GROUP3 = cat

CC = gcc

g$(MAIN1): $(MAIN1).c
	$(CC) $(MAIN1).c -o $(MAIN1)
	
val$(MAIN1): $(MAIN1)
	valgrind --leak-check=full ./$(MAIN1)
	
g$(MAIN2): $(MAIN2).c
	$(CC) $(MAIN2).c -o $(MAIN2)
	
val$(MAIN2): $(MAIN2)
	valgrind --leak-check=full ./$(MAIN2)

g$(MAIN3): $(MAIN3).c
	$(CC) $(MAIN3).c -o $(MAIN3)
	
val$(MAIN3): $(MAIN3)
	valgrind --leak-check=full ./$(MAIN3)
	
g$(GROUP1): $(GROUP1).c
	$(CC) $(GROUP1).c -o $(GROUP1)
	
val$(GROUP1): $(GROUP1)
	valgrind --leak-check=full ./$(GROUP1)
	
g$(GROUP2): $(GROUP2).c
	$(CC) $(GROUP2).c -o $(GROUP2)
	
val$(GROUP2): $(GROUP2)
	valgrind --leak-check=full ./$(GROUP2)
	
g$(GROUP3): $(GROUP3).c
	$(CC) $(GROUP3).c -o $(GROUP3)
	
val$(GROUP3): $(GROUP3)
	valgrind --leak-check=full ./$(GROUP3)
