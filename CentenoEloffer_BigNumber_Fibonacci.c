/* ========================================START======================================== */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* DEFINITIONS */
#define BASE10	10

/* STRUCTURES */
typedef struct bignumber{
	unsigned int digit;	
	struct bignumber *frontNode;
	struct bignumber *backNode;
}BIGNUMBER;

/* FUNCTION PROTOTYPES */
void initializeBigNumber(BIGNUMBER **bigNumber, BIGNUMBER *backNode);
void printBigNumber(BIGNUMBER *bigNumber);
void addBigFibonacciNumber(BIGNUMBER *previous, BIGNUMBER *current, BIGNUMBER *sum);
void copyBigNumber(BIGNUMBER *destination, BIGNUMBER *source);
void freeMemory(BIGNUMBER **bigNumber);

/* MAIN FUNCTION */
void main() {
	unsigned int n, i;
	BIGNUMBER *previous, *current, *next;
	
	/* Initialization */
	initializeBigNumber(&previous, NULL);
	initializeBigNumber(&current, NULL);
	current->digit = 1;
	initializeBigNumber(&next, NULL);
			
	do {
		printf("Compute for nth Fibonacci Number \nn = ");
		scanf("%d", &n);
		if (n < 0) {
			printf("Please enter n > 0 \n");
		}
	} while (n < 0);

	switch (n) {
		case 0: 	/* f(0) = 0 */
			printBigNumber(previous);
			break;
			
		case 1:		/* f(1) = 1 */
			printBigNumber(current);
			break;
			
		default:	/* f(n) = f(n-1) + f(n-2) */
			for (i = 2; i <= n; i++) {
				addBigFibonacciNumber(previous, current, next);
				copyBigNumber(previous, current);
				copyBigNumber(current, next);
			}
			printf("f(n) = f(n-1) + f(n-2) is\n\n");
			printBigNumber(next);
			printf("\n");
			break;
	}
	freeMemory(&previous);
	freeMemory(&current);
	freeMemory(&next);
}

/* USER-DEFINED FUNCTIONS */
/* Allocates memory to a node and sets up the value of its members */
void initializeBigNumber(BIGNUMBER **bigNumber, BIGNUMBER *backNode) {
	*bigNumber = (BIGNUMBER*)malloc(sizeof(BIGNUMBER));
	(*bigNumber)->backNode = backNode;
	(*bigNumber)->frontNode = NULL;
	(*bigNumber)->digit = 0;
}

/* Prints the digits of Big Numbers from end */
void printBigNumber(BIGNUMBER *bigNumber) {
	BIGNUMBER *temp = bigNumber;
	FILE *fp;
	
	fp = fopen("Question1_Output.txt", "w+");
	while (temp != NULL) {
		bigNumber = temp;
		temp = temp->frontNode;
	}	
	while (bigNumber != NULL) {
		/* print to console */
		printf("%d", bigNumber->digit);
		/* print to console */
   		fprintf(fp, "%d", bigNumber->digit);

		bigNumber = bigNumber->backNode;
	}
}

/* Add previous and current Fibonacci Big Number using arithmetic addition */
void addBigFibonacciNumber(BIGNUMBER *previous, BIGNUMBER *current, BIGNUMBER *sum) {
	unsigned short carry = 0;
	
	while (current != NULL) {		
		sum->digit = previous->digit + current->digit;
		if (carry > 0) {
			sum->digit += carry;
			carry = 0;
		}
		if (sum->digit >= BASE10) {
			sum->digit %= BASE10 ;
			carry++;
		}
		if ((current->frontNode != NULL) && (previous->frontNode == NULL)) {
			(sum->frontNode)->digit = (current->frontNode)->digit + carry;
			break;					
		}
		if ((carry > 0) && (sum->frontNode == NULL)) {
			initializeBigNumber(&sum->frontNode, sum);		
			(sum->frontNode)->digit += carry;
			break;
		}		
		sum = sum->frontNode;	
		previous = previous->frontNode;	
		current = current->frontNode;	
	}
}

/* Copy list of digits of a Big Numnber */
void copyBigNumber(BIGNUMBER *destination, BIGNUMBER *source) {
	while (source != NULL) {
		destination->digit = source->digit;
		if ((source->frontNode != NULL) && (destination->frontNode == NULL)) {
			initializeBigNumber(&destination->frontNode, destination);		
		}		
		source = source->frontNode;
		destination = destination->frontNode;
	}
}

/* Free allocated memory */
void freeMemory(BIGNUMBER **bigNumber) {
	BIGNUMBER *temp;
	temp = *bigNumber;
	while(*bigNumber != NULL) {
		temp = (*bigNumber)->frontNode;
		free(*bigNumber);
		*bigNumber = temp;
	}
}
/* ========================================END======================================== */
