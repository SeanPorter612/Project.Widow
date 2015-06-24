#include "LyteGlobals.h"	

WI_Int g_iAlignedAllocs = 0;
WI_Int g_iAlignedFree = 0;
WI_Int g_iTotalBytesAlignedAllocs = 0;//detect memory leaks

static void *WI_AllocDefault ( size_t size )
{
	return malloc ( size );
}

static void WI_FreeDefault ( void *ptr )
{
	free ( ptr );
}

static WI_AllocFunc *sAllocFunc = WI_AllocDefault;
static WI_FreeFunc *sFreeFunc = WI_FreeDefault;



#if defined (WI_HAS_ALIGNED_ALLOCATOR)
#include <malloc.h>
static void *WI_AlignedAllocDefault(size_t size, int alignment)
{
	return _aligned_malloc(size, (size_t)alignment);
}

static void WI_AlignedFreeDefault(void *ptr)
{
	_aligned_free(ptr);
}
#elif defined(__CELLOS_LV2__)
#include <stdlib.h>

static WI_Inline void *WI_AlignedAllocDefault(size_t size, int alignment)
{
	return memalign(alignment, size);
}

static WI_Inline void WI_AlignedFreeDefault(void *ptr)
{
	free(ptr);
}
#else





static inline void *WI_AlignedAllocDefault ( size_t size , int alignment )
{
	void *ret;
	char *real;
	real = ( char * ) sAllocFunc ( size + sizeof ( void * ) + ( alignment - 1 ) );
	if ( real ) {
		ret = WI_AlignPointer ( real + sizeof ( void * ) , alignment );
		*( ( void ** ) ( ret ) -1 ) = ( void * ) ( real );
	}
	else {
		ret = ( void * ) ( real );
	}
	return ( ret );
}

static inline void WI_AlignedFreeDefault ( void *ptr )
{
	void* real;

	if ( ptr ) {
		real = *( ( void ** ) ( ptr ) -1 );
		sFreeFunc ( real );
	}
}
#endif


static WI_AlignedAllocFunc *sAlignedAllocFunc = WI_AlignedAllocDefault;
static WI_AlignedFreeFunc *sAlignedFreeFunc = WI_AlignedFreeDefault;

void WI_AlignedAllocSetCustomAligned ( WI_AlignedAllocFunc *allocFunc , WI_AlignedFreeFunc *freeFunc )
{
	sAlignedAllocFunc = allocFunc ? allocFunc : WI_AlignedAllocDefault;
	sAlignedFreeFunc = freeFunc ? freeFunc : WI_AlignedFreeDefault;
}

void WI_AlignedAllocSetCustom ( WI_AllocFunc *allocFunc , WI_FreeFunc *freeFunc )
{
	sAllocFunc = allocFunc ? allocFunc : WI_AllocDefault;
	sFreeFunc = freeFunc ? freeFunc : WI_FreeDefault;
}

#ifdef BT_DEBUG_MEMORY_ALLOCATIONS
//this generic allocator provides the total allocated number of bytes
#include <stdio.h>

void*   WI_AlignedAllocInternal  (size_t size, int alignment,int line,char* filename)
{
	void *ret;
	char *real;

	gTotalBytesAlignedAllocs += size;
	g_iAlignedAllocs++;


	real = (char *)sAllocFunc(size + 2*sizeof(void *) + (alignment-1));
	if (real) {
		ret = (void*) WI_AlignPointer(real + 2*sizeof(void *), alignment);
		*((void **)(ret)-1) = (void *)(real);
		*((int*)(ret)-2) = size;

	} else {
		ret = (void *)(real);//??
	}

	printf("allocation#%d at address %x, from %s,line %d, size %d\n",g_iAlignedAllocs,real, filename,line,size);

	int* ptr = (int*)ret;
	*ptr = 12;
	return (ret);
}

void    WI_AlignedFreeInternal   (void* ptr,int line,char* filename)
{

	void* real;
	g_iAlignedFree++;

	if (ptr) {
		real = *((void **)(ptr)-1);
		int size = *((int*)(ptr)-2);
		gTotalBytesAlignedAllocs -= size;

		printf("free #%d at address %x, from %s,line %d, size %d\n",g_iAlignedFree,real, filename,line,size);

		sFreeFunc(real);
	} else
	{
		printf("NULL ptr\n");
	}
}

#else //BT_DEBUG_MEMORY_ALLOCATIONS

void*	WI_AlignedAllocInternal ( size_t size , int alignment )
{
	g_iAlignedAllocs++;
	void* ptr;
	ptr = sAlignedAllocFunc ( size , alignment );
	//	printf("WI_AlignedAllocInternal %d, %x\n",size,ptr);
	return ptr;
}

void	WI_AlignedFreeInternal ( void* ptr )
{
	if ( !ptr )
	{
		return;
	}

	g_iAlignedFree++;
	//	printf("WI_AlignedFreeInternal %x\n",ptr);
	sAlignedFreeFunc ( ptr );
}

#endif //BT_DEBUG_MEMORY_ALLOCATIONS



