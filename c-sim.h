#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>






char * hexstring_to_binary(char hexstring[])
{
   unsigned int n = (int)strtol(hexstring, NULL, 0);
   int c, d, counter;
   char *pointer;
 
   counter = 0;
   pointer = (char*)malloc(32+1);
 
   if ( pointer == NULL )
      exit(EXIT_FAILURE);
 
   for ( c = 31 ; c >= 0 ; c-- )
   {
      d = n >> c;
 
      if ( d & 1 )
         *(pointer+counter) = 1 + '0';
      else
         *(pointer+counter) = 0 + '0';
 
      counter++;
   }
   *(pointer+counter) = '\0';
 
   return  pointer;
}


unsigned int hexstring_to_decimal(char hexstring[]){

	unsigned int number = (int)strtol(hexstring, NULL, 0);

	return number;
}


unsigned int binary_to_decimal(char binaryString[]){
	int i, n, binDigit;
	unsigned int total = 0;
	n = 0;
	for(i=strlen(binaryString)-1;i>=0;i--){
		binDigit = 0;
		if(binaryString[i]=='1'){
			binDigit = 1;
		}
		/*note: pow is evidenlty double, so cast to unsigned long*/
		total = total + (binDigit*((unsigned int)(pow(2, n))));
		/*printf("charat %d was %c, n is %d and total is %u\n",i,binaryString[i], n, total);*/
		n++;
	}

	return total;
}


char strip_RW_char(char rawInput[]){
	char rwchar;
	int i =0;
	while(rawInput[i]!=' '){
		i++;
	}

	i++;
	rwchar = rawInput[i];

	return rwchar;
}

char * hexString_stripper(char rawInput[]){
	char *pointer;
	pointer = (char*)malloc(32+1);
	int i= 0;
	while(rawInput[i]!=' '){
		i++;
	}
	i = i+3;
	int counter = 0;


	while(rawInput[i]!='\n'){

		*(pointer+counter) = rawInput[i];
		i++;
		counter++;
	}
	

	*(pointer+counter) = '\0';

	return pointer;

}

int set_Index(char binaryString[], int bitsBlock, int setBits){
	char *pointer;
	int index;
	pointer = (char*)malloc(setBits+1);
	int i, counter=0;

	for(i=strlen(binaryString) - bitsBlock - setBits;i<strlen(binaryString)- bitsBlock;i++){
		*(pointer+counter) = binaryString[i];
		counter++;
	}
	*(pointer+counter) = '\0';
	index = binary_to_decimal(pointer);
	return index;
}

unsigned int tag_getter(char binaryString[], int bitsBlock, int setBits){
	char *pointer;
	unsigned int tag;
	pointer = (char*)malloc(strlen(binaryString) - bitsBlock - setBits);
	int i;

	for(i=0;i<strlen(binaryString) - bitsBlock - setBits;i++){
		*(pointer+i) = binaryString[i];
		
	}
	
	*(pointer+i) = '\0';
	tag = binary_to_decimal(pointer);
	return tag;/*change to tag . . . .. */
}

unsigned int** create_direct_cache(int setNum){
	unsigned int** cache;
	int i;
	cache = (unsigned int**)malloc(setNum*sizeof(unsigned int*));
	for(i=0;i<setNum;i++){
		cache[i] = (unsigned int*)malloc(2*sizeof(unsigned int));
	}

	for(i=0;i<setNum;i++){
		cache[i][0]=0;
		cache[i][1]=0;
	}
	/*print for testing purposes only. . . . 
	//for(i=0;i<setNum;i++){
	//	printf("%d :  [%u] [%u] \n",i, cache[i][0],cache[i][1]);
		
	//}*/

	return cache;
}

void resultsPrinted(int totalRead, int totalWrite, int totalHit, int totalMiss){
	printf("Memory reads: %d\n",totalRead );printf("Memory writes: %d\n", totalWrite );
	printf("Cache hits: %d\n", totalHit );printf("Cache misses: %d\n", totalMiss );
}

unsigned int** create_fully_assoc_cache(int setSize){
	unsigned int** cache;
	int i;
	cache = (unsigned int**)malloc(setSize*sizeof(unsigned int*));
	for(i=0;i<setSize;i++){
		cache[i] = (unsigned int*)malloc(2*sizeof(unsigned int));
	}

	for(i=0;i<setSize;i++){
		cache[i][0]=0;	cache[i][1]=0;
	}
	return cache;
}/*end create_fully_assoc_cache*/

int find_empty_line(unsigned int **cache, int setSize){
	int i;
	int lineRep = -1;
	for(i=0;i<setSize;i++){
		if(cache[i][0] == 0){
			lineRep = i;
			return lineRep;
		}
	}


	return lineRep;
}

int line_replacer(unsigned int **cache, int setSize){
	int i;
	int replacedLine = 0;
	for(i=0;i<setSize;i++){
		
		if(cache[i][0]>replacedLine){
			
			replacedLine = i;
			
		}

	}
		return replacedLine;

}

unsigned int** create_deerect_cache(int setNum, int blockSize){
	unsigned int** cache;
	int i, j;
	cache = (unsigned int**)malloc(setNum*sizeof(unsigned int*));
	for(i=0;i<setNum;i++){
		cache[i] = (unsigned int*)malloc((2+blockSize)*sizeof(unsigned int));
	}

	for(i=0;i<setNum;i++){
		for(j=0;j<(2+blockSize);j++){
			cache[i][j]=0;
		}
	}
	

	return cache;

}
int block_num(char binaryString[], int bitsBlock){
	char *pointer;
	pointer = (char*)malloc(bitsBlock+1);
	int numBlock, i, counter=0;

	for(i=strlen(binaryString) - bitsBlock;i<strlen(binaryString);i++){
		*(pointer+counter) = binaryString[i];
		counter++;

	}
	*(pointer+counter) = '\0';
	numBlock = binary_to_decimal(pointer);


return numBlock;
}/*end get_blocknum*/


int strip_n(char str[]){
	char *pointer;
	int returnValue;
	int i, counter = 0;
	/*int beginIndex = 6;*/
	pointer = (char*)malloc((strlen(str) - 6)+1);

	for(i=6;i<strlen(str);i++){
		*(pointer+counter) = str[i];
		counter++;
	}
	*(pointer+counter) = '\0';

	returnValue = atoi(pointer);
	/*atoi the char . . */

	return returnValue;
}


struct node{
	unsigned int dat;
	struct node *next;
};

struct hash{
	struct node *head;
	int valid;
};

struct node * node_creator(unsigned int num){
	struct node *ptr;
	ptr = (struct node *) malloc(sizeof(struct node));
	if(ptr == NULL){
		return(struct node *) NULL;
	}else{
		ptr->dat = num;
		ptr->next = NULL;
		return ptr;
	}
}/*end node_creator*/





int cache_searcher(struct hash *cache, int set_index, unsigned int tag){
	if(cache[set_index].valid == 0){
		return 0;
	}

	struct node *ptr;
	ptr = cache[set_index].head;/* indexed head gets pointed at*/
	
	
	
	
	
	while(ptr!= NULL){
		
		if(ptr->dat == tag){
			return 1;
		}
		ptr = ptr->next;/* going to next ptr*/
	}
	
	return 0;
}



struct hash* hash_creator(int setNum){
	struct hash *hashTable;
	hashTable = (struct hash*)calloc(setNum, sizeof(struct hash));
	int i;
	for(i=0;i<setNum;i++){
		hashTable[i].head = NULL;
		
	}

	return hashTable;
}