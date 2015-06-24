
#ifndef __WI_ALLOCATOR__
#define __WI_ALLOCATOR__

///we probably replace this with our own aligned memory allocator
///so we replace _aligned_malloc and _aligned_free with our own
///that is more portable and more predictable


///rudimentary class to provide type info
struct WI_TypedObject
{
	WI_TypedObject(int objectType)
		:m_objectType(objectType)
	{
	}
	int	m_objectType;

	inline int getObjectType() const
	{
		return m_objectType;
	}
};



///align a pointer to the provided alignment, upwards
template <typename T>T* 
WI_AlignPointer(T* unalignedPtr, size_t alignment)
{

	struct WI_ConvertPointerSizeT
	{
		union 
		{
			T* ptr;
			size_t integer;
		};
	};
	WI_ConvertPointerSizeT converter;


	const size_t bit_mask = ~(alignment - 1);
	converter.ptr = unalignedPtr;
	converter.integer += alignment-1;
	converter.integer &= bit_mask;
	return converter.ptr;
}

//#define WI_DEBUG_MEMORY_ALLOCATIONS 1
#ifdef WI_DEBUG_MEMORY_ALLOCATIONS

#define WI_AlignedAlloc(a,b) \
		WI_AlignedAllocInternal(a,b,__LINE__,__FILE__)

#define WI_AlignedFree(ptr) \
		WI_AlignedFreeInternal(ptr,__LINE__,__FILE__)

void*	WI_AlignedAllocInternal	(size_t size, int alignment,int line,char* filename);

void	WI_AlignedFreeInternal	(void* ptr,int line,char* filename);

#else
	void*	WI_AlignedAllocInternal	(size_t size, int alignment);
	void	WI_AlignedFreeInternal	(void* ptr);

	#define WI_AlignedAlloc(size,alignment) WI_AlignedAllocInternal(size,alignment)
	#define WI_AlignedFree(ptr) WI_AlignedFreeInternal(ptr)

#endif
typedef int	size_type;

typedef void *(WI_AlignedAllocFunc)(size_t size, int alignment);
typedef void (WI_AlignedFreeFunc)(void *memblock);

typedef void *(WI_AllocFunc)(size_t size);
typedef void (WI_FreeFunc)(void *memblock);

///The developer can let all Bullet memory allocations go through a custom memory allocator, using WI_AlignedAllocSetCustom
void WI_AlignedAllocSetCustom(WI_AllocFunc *allocFunc, WI_FreeFunc *freeFunc);

///If the developer already has a custom aligned allocator, then WI_AlignedAllocSetCustomAligned can be used. The default aligned allocator pre-allocates extra memory using the non-aligned allocator, and instruments it.
void WI_AlignedAllocSetCustomAligned(WI_AlignedAllocFunc *allocFunc, WI_AlignedFreeFunc *freeFunc);


#define WI_DECLARE_ALIGNED_ALLOCATOR() \
			WI_FInline void* operator new(size_t sizeInBytes)		{ return WI_AlignedAlloc(sizeInBytes,16); }		\
			WI_FInline void  operator delete(void* ptr)			{ WI_AlignedFree(ptr); }						\
			WI_FInline void* operator new(size_t, void* ptr)		{ return ptr; }									\
			WI_FInline void  operator delete(void*, void*)			{ }												\
			WI_FInline void* operator new[](size_t sizeInBytes)	{ return WI_AlignedAlloc(sizeInBytes,16); }		\
			WI_FInline void  operator delete[](void* ptr)			{ WI_AlignedFree(ptr); }						\
			WI_FInline void* operator new[](size_t, void* ptr)		{ return ptr; }									\
			WI_FInline void  operator delete[](void*, void*)		{ }												\

///The WI_AlignedAllocator is a portable class for aligned memory allocations.
///Default implementations for unaligned and aligned allocations can be overridden by a custom allocator using WI_AlignedAllocSetCustom and WI_AlignedAllocSetCustomAligned.
template < typename T , unsigned Alignment >
class WI_AlignedAllocator {
	
	typedef WI_AlignedAllocator< T , Alignment > self_type;
	
public:

	//just going down a list:
	WI_AlignedAllocator() {}

	WI_AlignedAllocator( const self_type & );

	//template < typename T , unsigned Alignment >
	//WI_AlignedAllocator<T, Alignment>::WI_AlignedAllocator(const self_type &)  { }

	template < typename Other >
	WI_AlignedAllocator( const WI_AlignedAllocator< Other , Alignment > & ) {}

	typedef const T*         const_pointer;
	typedef const T&         const_reference;
	typedef T*               pointer;
	typedef T&               reference;
	typedef T                value_type;

	pointer address ( reference ref ) const                          
	{ return &ref; }

	const_pointer address ( const_reference  ref ) const
	{ return &ref; }

	pointer allocate ( size_type n, const_pointer* hint = 0 ) 
	{
		(void)hint;
		return reinterpret_cast< pointer >(WI_AlignedAlloc( sizeof(value_type) * n , Alignment ));
	}

	void construct ( pointer ptr , const value_type & value ) 
	{ new (ptr) value_type( value ); }

	void deallocate( pointer ptr )
	{
		WI_AlignedFree( reinterpret_cast< void * >( ptr ) );
	}

	void          destroy   ( pointer          ptr )                                 { ptr->~value_type(); }
	

	template < typename O > struct rebind {
		typedef WI_AlignedAllocator< O , Alignment > other;
	};
	template < typename O >
	self_type & operator=( const WI_AlignedAllocator< O , Alignment > & ) { return *this; }

	friend bool operator==( const self_type & , const self_type & ) { return true; }
};



#endif //WI_ALIGNED_ALLOCATOR
