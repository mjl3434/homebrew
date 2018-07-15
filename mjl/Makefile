# Philisophy: Be extremely literal and keep everything super simple until that approach no longer scales

PROGRAM_NAME=testDataStructures
GXX=g++ -g -O0 -Wall
CFLAGS=-std=c++14
LDFLAGS=-std=c++14

OBJECTS=\
	main.o \
	DynamicArray.o \
	DynamicArray_test.o \
	Queue_test.o \
	SinglyLinkedList.o \
	SinglyLinkedList_test.o \
	Stack_test.o \
	HashTable.o \
	HashTable_test.o

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJECTS)
	$(GXX) $(LDFLAGS) $(OBJECTS) -o $(PROGRAM_NAME)

main.o: main.cpp
	$(GXX) $(CFLAGS) -c main.cpp

DynamicArray.o: DynamicArray.cpp DynamicArray.h
	$(GXX) $(CFLAGS) -c DynamicArray.cpp

HashTable.o: HashTable.cpp HashTable.h
	$(GXX) $(CFLAGS) -c HashTable.cpp

SinglyLinkedList.o: SinglyLinkedList.cpp SinglyLinkedList.h
	$(GXX) $(CFLAGS) -c SinglyLinkedList.cpp

DynamicArray_test.o: DynamicArray_test.cpp DynamicArray.o
	$(GXX) $(CFLAGS) -c DynamicArray_test.cpp
	
HashTable_test.o: HashTable_test.cpp HashTable.o
	$(GXX) $(CFLAGS) -c HashTable.cpp
	
Queue_test.o: Queue_test.cpp SinglyLinkedList.o
	$(GXX) $(CFLAGS) -c Queue_test.cpp

SinglyLinkedList_test.o: SinglyLinkedList_test.cpp SinglyLinkedList.o
	$(GXX) $(CFLAGS) -c SinglyLinkedList_test.cpp

Stack_test.o: Stack_test.cpp SinglyLinkedList.o
	$(GXX) $(CFLAGS) -c Stack_test.cpp

