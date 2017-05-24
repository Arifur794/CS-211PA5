#include "c-sim.h"
#define Max_file_Size 150

/* Arifur Rahman PA5- ******
******
CACHE SIMULATION*/





/* with main the implementation layed out can be utilized*/
int main(int argc, char* argv[]){
	
	FILE *fp;
	char file_line[Max_file_Size];


	/*This cache size will be one argument */
	int size_of_cache = atoi(argv[1]);



	int setNum = 0;
	int blockSize = 0;
	int setSize = 0;
	

	int bitsBlock = 0;
	int setBits = 0;

	char write_or_read;
	
	int MissTotal = 0;
	int HitTotal = 0;
	int ReadTotal = 0;
	int WriteTotal = 0;


	if(strcmp(argv[2],"direct")==0){
		setSize = 1;
		blockSize = atoi(argv[3]);
		setNum = size_of_cache / (setSize*blockSize);
		bitsBlock = log(blockSize)/log(2);
		setBits = log(setNum)/log(2);
		fp = fopen(argv[argc-1], "r");


		/*implementaion for creating direct cache*/
		unsigned int** cache = create_direct_cache(setNum);
		
		
		while(fgets(file_line, Max_file_Size, fp)!=NULL){
			if(file_line[0]!='0'){
				continue;
			}

			write_or_read = strip_RW_char(file_line);
			char * binaryString = hexstring_to_binary(hexString_stripper(file_line));
			int set_index  = set_Index(binaryString, bitsBlock, setBits);
			unsigned int tag = tag_getter(binaryString, bitsBlock, setBits);
		
			if(write_or_read == 'R'){
				if(cache[set_index][0]==0){
					MissTotal++;
					ReadTotal++;
					cache[set_index][0] = 1;
					cache[set_index][1] = tag;
					continue;
				}

				if(cache[set_index][1]==tag){
					HitTotal++;
					continue;
				}else{
					MissTotal++;
					ReadTotal++;
					cache[set_index][0] = 1;
					cache[set_index][1] = tag;
					continue;
				}
			}
			if(write_or_read == 'W'){
				if(cache[set_index][0]==0){
					MissTotal++;
					ReadTotal++;
					WriteTotal++;
					cache[set_index][0] = 1;
					cache[set_index][1] = tag;
					continue;
				}
				if(cache[set_index][1]==tag){
					HitTotal++;
					WriteTotal++;
					continue;
				}else{
					MissTotal++;
					ReadTotal++;
					WriteTotal++;
					cache[set_index][0] = 1;
					cache[set_index][1] = tag;
					continue;
				}
			}


		}//end of reading file and doing operations

		resultsPrinted(ReadTotal,WriteTotal,HitTotal,MissTotal);
		return 0;
	}/*finish direct cache*/

	//start fully associative cache implementation

	if(strcmp(argv[2],"assoc")==0){
		
		setNum = 1;
		
		//get blockSize
		blockSize = atoi(argv[3]);

		
		setSize = size_of_cache / (setNum*blockSize);
		
		bitsBlock = log(blockSize)/log(2);
		
		setBits = log(setNum)/log(2);
	
		fp = fopen(argv[argc-1], "r");


		struct hash *cache=NULL;

		cache = hash_creator(setNum);

		
		while(fgets(file_line, Max_file_Size, fp)!=NULL){
		
			if(file_line[0]!='0'){
				continue;
			}
			
			//get whether R or W
			write_or_read = strip_RW_char(file_line);
	
			char * binaryString = hexstring_to_binary(hexString_stripper(file_line));
			
			//get index
			int set_index  = set_Index(binaryString, bitsBlock, setBits);
		
			unsigned int tag = tag_getter(binaryString, bitsBlock, setBits);
			//printf("Your tag is: %u\n", tag );

			if(cache_searcher(cache, set_index, tag) == 1){
				HitTotal++;
				if(write_or_read=='W'){
						WriteTotal++;
					}
				continue;
			}
			
			// then insert if not full
			if(cache[set_index].valid < setSize){
				MissTotal++;
				ReadTotal++;
				if(write_or_read=='W'){
						WriteTotal++;
					}
				struct node *newerNode = node_creator(tag);
				newerNode->next = cache[set_index].head;
				cache[set_index].head = newerNode;
				cache[set_index].valid++;
				continue;

			}
			
			else{
				int i;
				MissTotal++;
				ReadTotal++;
				if(write_or_read=='W'){
						WriteTotal++;
					}
				//this is to get rid of last item  
				struct node *ptr;
				ptr = cache[set_index].head;//point ptr at indexed head
				for(i=1;i<setSize-1;i++){
					
					ptr = ptr->next;//advance ptr
				}
				ptr->next = NULL;
				//now insert
				struct node *newerNode = node_creator(tag);
				newerNode->next = cache[set_index].head;
				cache[set_index].head = newerNode;


			}//end else


		}//end reading file and doing operations

		

resultsPrinted(ReadTotal,WriteTotal,HitTotal,MissTotal);

return 0;




	}

	setSize = strip_n(argv[2]);

	blockSize = atoi(argv[3]);

		setNum = size_of_cache / (setSize*blockSize);

		bitsBlock = log(blockSize)/log(2);
	
		setBits = log(setNum)/log(2);
		

		fp = fopen(argv[argc-1], "r");


		
		struct hash *cache=NULL;

		cache = hash_creator(setNum);

		//start reading file and doing operations
		while(fgets(file_line, Max_file_Size, fp)!=NULL){
			//
			if(file_line[0]!='0'){
				continue;
			}
			//
			//get whether R or W
			write_or_read = strip_RW_char(file_line);
			//
			//get binary string
			char * binaryString = hexstring_to_binary(hexString_stripper(file_line));
			//
			//get index
			int set_index  = set_Index(binaryString, bitsBlock, setBits);
			
			unsigned int tag = tag_getter(binaryString, bitsBlock, setBits);
			//printf("Your tag is: %u\n", tag );

			if(cache_searcher(cache, set_index, tag) == 1){
				HitTotal++;
				if(write_or_read=='W'){
						WriteTotal++;
					}
				continue;
			}
			
			//if not full, insert
			if(cache[set_index].valid < setSize){
				MissTotal++;
				ReadTotal++;
				if(write_or_read=='W'){
						WriteTotal++;
					}
				struct node *newerNode = node_creator(tag);
				newerNode->next = cache[set_index].head;
				cache[set_index].head = newerNode;
				cache[set_index].valid++;
				continue;

			}else{
				int i;
				MissTotal++;
				ReadTotal++;
				if(write_or_read=='W'){
						WriteTotal++;
					}
				//get rid of last item . . .. 
				struct node *ptr;//create ptr
				ptr = cache[set_index].head;//point ptr at indexed head
				for(i=1;i<setSize-1;i++){
					
					ptr = ptr->next;//advance ptr
				}
				ptr->next = NULL;
				//now insert
				struct node *newerNode = node_creator(tag);
				newerNode->next = cache[set_index].head;
				cache[set_index].head = newerNode;


			}


		}

		

resultsPrinted(ReadTotal,WriteTotal,HitTotal,MissTotal);

return 0;

}