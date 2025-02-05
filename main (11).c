#include <stdio.h>
#include <stdlib.h>
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};
// Fill out this structure
struct HashType
{
    struct RecordType data;
    struct HashType* next;
};
#define HashSize 10
// Compute the hash function
int hash(int x)
{
    return x % HashSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
		
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("Index %d -> ", i);
        struct HashType* current = &pHashArray[i];
        while (current != NULL) {
            printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
	}
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Your hash implementation
    struct HashType hashTable[HashSize]; 
    // Initialize hash table
    for (int i = 0; i < HashSize; i++) 
    {
    hashTable[i].data.id = -1; // Initialize id to a value that won't conflict with actual data
    hashTable[i].next = NULL;
}

    // Insert records into hash table
    for (int i = 0; i < recordSz; i++) 
    {
        int index = hash(pRecords[i].id); // Compute hash
        struct HashType* newNode = (struct HashType*)malloc(sizeof(struct HashType));
        newNode -> next = hashTable[index].next;
        newNode -> data = pRecords[i];
        hashTable[index].next = newNode;
    }

    // Display records in the hash table
    displayRecordsInHash(hashTable, HashSize);

    return 0;
}