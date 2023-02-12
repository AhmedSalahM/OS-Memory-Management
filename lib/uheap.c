#include <inc/lib.h>

// malloc()
//	This function use FIRST FIT strategy to allocate space in heap
//  with the given size and return void pointer to the start of the allocated space

//	To do this, we need to switch to the kernel, allocate the required space
//	in Page File then switch back to the user again.
//
//	We can use sys_allocateMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls allocateMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the allocateMem function is empty, make sure to implement it.

//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//

struct add{
	uint32 start;
	uint32 end;
};


int count=0;

struct add arr_add[10000];

uint32 base_add=USER_HEAP_START;

struct best_fit{
			uint32 start;
			uint32 end;
			int space;
		};
struct best_fit arr[10000];
void* malloc(uint32 size)
{



	//cprintf("count is %d: \n",count);


	//TODO: [PROJECT 2021 - [2] User Heap] malloc() [User Side]
	// Write your code here, remove the panic and write your code
	//panic("malloc() is not implemented yet...!!");

	//This function should find the space of the required range
	//using the BEST FIT strategy

	//refer to the project presentation and documentation for details



	///cprintf("size is : %d",size);
//	while(size%PAGE_SIZE!=0){
	//			size++;
		//	}

	size=ROUNDUP(size,PAGE_SIZE);

	//cprintf("sizeeeeeeeeeeee %d \n",size);

	int count2=0;

	int flag1=0;

	int ni= PAGE_SIZE;

	for(int i=0;i<count;i++){

		cprintf("arr %d start is: %x\n",i,arr_add[i].start);
		cprintf("arr %d end is: %x\n",i,arr_add[i].end);
	}

	for(int i=USER_HEAP_START;i<(int)base_add;i+=ni){
		int flag0=1;
		for(int j=i;j<i+size;j+=PAGE_SIZE){
			for(int k=0;k<count;k++){
				if(j>=arr_add[k].start&&j<arr_add[k].end){
					ni=arr_add[k].end-i;
					flag1=1;
					break;
				}
			}
			if(flag1){
				flag0=0;
				break;
			}
		}
		if(flag0){

			int f=1;

			arr[count2].start=i;
			arr[count2].end = i+size;
			arr[count2].space=0;
			count2++;

			for(int l=0;l<count;l++){
				if(i+size<arr_add[l].start){
					ni=arr_add[l].end-i;
					f=0;
					break;

				}
			}

			if(f){
				break;
			}

		}

		flag1=0;


	}

	if(count2==0){
		//cprintf("hellllllllOOlooo");
		if((int)(base_add+size-1)>=(int)USER_HEAP_MAX)
			return NULL;
		else{
			uint32 s=base_add;
			//cprintf("s: %x",s);
			arr_add[count].start=s;
		    sys_allocateMem(s,size);
			base_add+=size;
			arr_add[count].end=base_add;
			count++;

			return (void*)s;

		}

	}
	else{



	for(int i=0;i<count2;i++){
		for(int j=arr[i].end;j<base_add;j+=PAGE_SIZE){
			int flag=0;
			for(int k=0;k<count;k++){
				if(j>=arr_add[k].start&&j<arr_add[k].end){
								flag=1;
								break;}
			arr[i].space++;
			}
			if(flag)
				break;
		}
	}

	int index=0;
	int min=9999999;
	for(int i=0;i<count2;i++){
		//cprintf("arr %d size is: %x\n",i,arr[i].space);
		if(arr[i].space<min){
			//cprintf("arr %d size is: %x\n",i,min);
			min=arr[i].space;
			index=i;
			//cprintf("arr %d size is: %x\n",i,min);
			//printf("arr %d start is: %x\n",i,arr[i].start);
		}
	}

	arr_add[count].start=arr[index].start;
	arr_add[count].end=arr[index].end;
	count++;


		sys_allocateMem(arr[index].start,size);

		for(int i=0;i<count2;i++){

			cprintf("arr %d start is: %x\n",i,arr[i].start);
			cprintf("arr %d end is: %x\n",i,arr[i].end);
			cprintf("arr %d size is: %d\n",i,arr[i].space);
			}

		cprintf("addddddddddddddddddresss %x",arr[index].start);



		return (void*)arr[index].start;

	}



		//struct best_fit arr[10000];

		//int count2=0;

		//int flag1=0;

		//int ni= PAGE_SIZE;

/*int count2=0;

if(count2==0){
	if((int)(base_add+size-1)>=(int)USER_HEAP_MAX)
				return NULL;
            	uint32 s=base_add;
				cprintf("s: %x",s);
				arr_add[count].start=s;
			    sys_allocateMem(s,size);
				base_add+=size;
				arr_add[count].end=base_add;
				count++;

				return (void*)s;
}*/

	return NULL;
}

// free():
//	This function frees the allocation of the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from page file and main memory then switch back to the user again.
//
//	We can use sys_freeMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls freeMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the freeMem function is empty, make sure to implement it.

void free(void* virtual_address)
{

	//cprintf("vvvvvvvvvvvvvvvvvvv %x \n",virtual_address);

	    uint32 start;
		uint32 end;

		uint32 v = (uint32)virtual_address;

		int index;

		for(int i=0;i<count;i++){
			if((int)v>=(int)arr_add[i].start&&(int)v<(int)arr_add[i].end){
				start=arr_add[i].start;
				end=arr_add[i].end;
				index=i;
				break;
			}
		}


			sys_freeMem(start,arr_add[index].end-arr_add[index].start);



		for(int i=index;i<count-1;i++){
			arr_add[i].start=arr_add[i+1].start;
			arr_add[i].end=arr_add[i+1].end;
		}

		count--;


	//TODO: [PROJECT 2021 - [2] User Heap] free() [User Side]
	// Write your code here, remove the panic and write your code
	///panic("free() is not implemented yet...!!");

	//you should get the size of the given allocation using its address

	//refer to the project presentation and documentation for details
}

//==================================================================================//
//================================ OTHER FUNCTIONS =================================//
//==================================================================================//

void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable)
{
	panic("this function is not required...!!");
	return 0;
}

void* sget(int32 ownerEnvID, char *sharedVarName)
{
	panic("this function is not required...!!");
	return 0;
}

void sfree(void* virtual_address)
{
	panic("this function is not required...!!");
}

void *realloc(void *virtual_address, uint32 new_size)
{
	panic("this function is not required...!!");
	return 0;
}

void expand(uint32 newSize)
{
	panic("this function is not required...!!");
}
void shrink(uint32 newSize)
{
	panic("this function is not required...!!");
}

void freeHeap(void* virtual_address)
{
	panic("this function is not required...!!");
}
