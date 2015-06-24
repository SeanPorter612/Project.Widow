

#ifndef WI_OBJECT_ARRAY__
#define WI_OBJECT_ARRAY__

#define WI_USE_PLACEMENT_NEW 1
//#define WI_USE_MEMCPY 1 //disable, because it is cumbersome to find out for each platform where memcpy is defined. It can be in <memory.h> or <string.h> or otherwise...
#define WI_ALLOW_ARRAY_COPY_OPERATOR // enabling this can accidentally perform deep copies of data if you are not careful

#ifdef WI_USE_MEMCPY
#include <memory.h>
#include <string.h>
#endif //WI_USE_MEMCPY

#ifdef WI_USE_PLACEMENT_NEW
#include <new> //for placement new
#endif //WI_USE_PLACEMENT_NEW


///The WI_Array template class uses a subset of the stl::vector interface for its methods
///It is developed to replace stl::vector to avoid portability issues, including STL alignment issues to add SIMD/SSE data
template <typename T> 
class WI_Array
{
	WI_AlignedAllocator<T , 16>	m_allocator;

	int					m_size;
	int					m_capacity;
	T*					m_data;
	//PCK: added this line
	bool				m_ownsMemory;

#ifdef WI_ALLOW_ARRAY_COPY_OPERATOR
public:
	WI_FInline WI_Array<T>& operator=(const WI_Array<T> &other)
	{
		copyFromArray(other);
		return *this;
	}
#else//WI_ALLOW_ARRAY_COPY_OPERATOR
private:
		WI_FInline WI_Array<T>& operator=(const WI_Array<T> &other);
#endif//WI_ALLOW_ARRAY_COPY_OPERATOR

protected:
		WI_FInline	int	allocSize(int size)
		{
			return (size ? size*2 : 1);
		}
		WI_FInline	void	copy(int start,int end, T* dest) const
		{
			int i;
			for (i=start;i<end;++i)
#ifdef WI_USE_PLACEMENT_NEW
				new (&dest[i]) T(m_data[i]);
#else
				dest[i] = m_data[i];
#endif //WI_USE_PLACEMENT_NEW
		}

		WI_FInline	void	init()
		{
			//PCK: added this line
			m_ownsMemory = true;
			m_data = 0;
			m_size = 0;
			m_capacity = 0;
		}
		WI_FInline	void	destroy(int first,int last)
		{
			int i;
			for (i=first; i<last;i++)
			{
				m_data[i].~T();
			}
		}

		WI_FInline	void* allocate(int size)
		{
			if (size)
				return m_allocator.allocate(size);
			return 0;
		}

		WI_FInline	void	deallocate()
		{
			if(m_data)	{
				//PCK: enclosed the deallocation in this block
				if (m_ownsMemory)
				{
					m_allocator.deallocate(m_data);
				}
				m_data = 0;
			}
		}

	


	public:
		
		WI_Array()
		{
			init();
		}

		~WI_Array()
		{
			clear();
		}

		///Generally it is best to avoid using the copy constructor of an WI_Array, and use a (const) reference to the array instead.
		WI_Array(const WI_Array& otherArray)
		{
			init();

			int otherSize = otherArray.size();
			resize (otherSize);
			otherArray.copy(0, otherSize, m_data);
		}

		
		
		/// return the number of elements in the array
		WI_FInline	int size() const
		{	
			return m_size;
		}
		
		WI_FInline const T& at(int n) const
		{
			WI_Assert(n>=0);
			WI_Assert(n<size());
			return m_data[n];
		}

		WI_FInline T& at(int n)
		{
			WI_Assert(n>=0);
			WI_Assert(n<size());
			return m_data[n];
		}

		WI_FInline const T& operator[](int n) const
		{
			WI_Assert(n>=0);
			WI_Assert(n<size());
			return m_data[n];
		}

		WI_FInline T& operator[](int n)
		{
			WI_Assert(n>=0);
			WI_Assert(n<size());
			return m_data[n];
		}
		

		///clear the array, deallocated memory. Generally it is better to use array.resize(0), to reduce performance overhead of run-time memory (de)allocations.
		WI_FInline	void	clear()
		{
			destroy(0,size());
			
			deallocate();
			
			init();
		}

		WI_FInline	void	pop_back()
		{
			WI_Assert(m_size>0);
			m_size--;
			m_data[m_size].~T();
		}


		///resize changes the number of elements in the array. If the new size is larger, the new elements will be constructed using the optional second argument.
		///when the new number of elements is smaller, the destructor will be called, but memory will not be freed, to reduce performance overhead of run-time memory (de)allocations.
		WI_FInline	void	resizeNoInitialize(int newsize)
		{
			int curSize = size();

			if (newsize < curSize)
			{
			} else
			{
				if (newsize > size())
				{
					reserve(newsize);
				}
				//leave this uninitialized
			}
			m_size = newsize;
		}
	
		WI_FInline	void	resize(int newsize, const T& fillData=T())
		{
			int curSize = size();

			if (newsize < curSize)
			{
				for(int i = newsize; i < curSize; i++)
				{
					m_data[i].~T();
				}
			} else
			{
				if (newsize > size())
				{
					reserve(newsize);
				}
#ifdef WI_USE_PLACEMENT_NEW
				for (int i=curSize;i<newsize;i++)
				{
					new ( &m_data[i]) T(fillData);
				}
#endif //WI_USE_PLACEMENT_NEW

			}

			m_size = newsize;
		}
		WI_FInline	T&  expandNonInitializing( )
		{	
			int sz = size();
			if( sz == capacity() )
			{
				reserve( allocSize(size()) );
			}
			m_size++;

			return m_data[sz];		
		}


		WI_FInline	T&  expand( const T& fillValue=T())
		{	
			int sz = size();
			if( sz == capacity() )
			{
				reserve( allocSize(size()) );
			}
			m_size++;
#ifdef WI_USE_PLACEMENT_NEW
			new (&m_data[sz]) T(fillValue); //use the in-place new (not really allocating heap memory)
#endif

			return m_data[sz];		
		}


		WI_FInline	void push_back(const T& _Val)
		{	
			int sz = size();
			if( sz == capacity() )
			{
				reserve( allocSize(size()) );
			}
			
#ifdef WI_USE_PLACEMENT_NEW
			new ( &m_data[m_size] ) T(_Val);
#else
			m_data[size()] = _Val;			
#endif //WI_USE_PLACEMENT_NEW

			m_size++;
		}

	
		/// return the pre-allocated (reserved) elements, this is at least as large as the total number of elements, see size() and reserve()
		WI_FInline	int capacity() const
		{	
			return m_capacity;
		}
		
		WI_FInline	void reserve(int _Count)
		{	// determine new minimum length of allocated storage
			if (capacity() < _Count)
			{	// not enough room, reallocate
				T*	s = (T*)allocate(_Count);

				copy(0, size(), s);

				destroy(0,size());

				deallocate();
				
				//PCK: added this line
				m_ownsMemory = true;

				m_data = s;
				
				m_capacity = _Count;

			}
		}


		class less
		{
			public:

				bool operator() ( const T& a, const T& b )
				{
					return ( a < b );
				}
		};
	

		template <typename L>
		void quickSortInternal(const L& CompareFunc,int lo, int hi)
		{
		//  lo is the lower index, hi is the upper index
		//  of the region of array a that is to be sorted
			int i=lo, j=hi;
			T x=m_data[(lo+hi)/2];

			//  partition
			do
			{    
				while (CompareFunc(m_data[i],x)) 
					i++; 
				while (CompareFunc(x,m_data[j])) 
					j--;
				if (i<=j)
				{
					swap(i,j);
					i++; j--;
				}
			} while (i<=j);

			//  recursion
			if (lo<j) 
				quickSortInternal( CompareFunc, lo, j);
			if (i<hi) 
				quickSortInternal( CompareFunc, i, hi);
		}


		template <typename L>
		void quickSort(const L& CompareFunc)
		{
			//don't sort 0 or 1 elements
			if (size()>1)
			{
				quickSortInternal(CompareFunc,0,size()-1);
			}
		}


		///heap sort from http://www.csse.monash.edu.au/~lloyd/tildeAlgDS/Sort/Heap/
		template <typename L>
		void downHeap(T *pArr, int k, int n, const L& CompareFunc)
		{
			/*  PRE: a[k+1..N] is a heap */
			/* POST:  a[k..N]  is a heap */
			
			T temp = pArr[k - 1];
			/* k has child(s) */
			while (k <= n/2) 
			{
				int child = 2*k;
				
				if ((child < n) && CompareFunc(pArr[child - 1] , pArr[child]))
				{
					child++;
				}
				/* pick larger child */
				if (CompareFunc(temp , pArr[child - 1]))
				{
					/* move child up */
					pArr[k - 1] = pArr[child - 1];
					k = child;
				}
				else
				{
					break;
				}
			}
			pArr[k - 1] = temp;
		} /*downHeap*/

		void	swap(int index0,int index1)
		{
#ifdef WI_USE_MEMCPY
			char	temp[sizeof(T)];
			memcpy(temp,&m_data[index0],sizeof(T));
			memcpy(&m_data[index0],&m_data[index1],sizeof(T));
			memcpy(&m_data[index1],temp,sizeof(T));
#else
			T temp = m_data[index0];
			m_data[index0] = m_data[index1];
			m_data[index1] = temp;
#endif //WI_USE_PLACEMENT_NEW

		}

	template <typename L>
	void heapSort(const L& CompareFunc)
	{
		/* sort a[0..N-1],  N.B. 0 to N-1 */
		int k;
		int n = m_size;
		for (k = n/2; k > 0; k--) 
		{
			downHeap(m_data, k, n, CompareFunc);
		}

		/* a[1..N] is now a heap */
		while ( n>=1 ) 
		{
			swap(0,n-1); /* largest of a[0..n-1] */


			n = n - 1;
			/* restore a[1..i-1] heap */
			downHeap(m_data, 1, n, CompareFunc);
		} 
	}

	///non-recursive binary search, assumes sorted array
	int	findBinarySearch(const T& key) const
	{
		int first = 0;
		int last = size()-1;

		//assume sorted array
		while (first <= last) {
			int mid = (first + last) / 2;  // compute mid point.
			if (key > m_data[mid]) 
				first = mid + 1;  // repeat search in top half.
			else if (key < m_data[mid]) 
				last = mid - 1; // repeat search in bottom half.
			else
				return mid;     // found it. return position /////
		}
		return size();    // failed to find key
	}


	int	findLinearSearch(const T& key) const
	{
		int index=size();
		int i;

		for (i=0;i<size();i++)
		{
			if (m_data[i] == key)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	void	remove(const T& key)
	{

		int findIndex = findLinearSearch(key);
		if (findIndex<size())
		{
			swap( findIndex,size()-1);
			pop_back();
		}
	}

	//PCK: whole function
	void initializeFromBuffer(void *buffer, int size, int capacity)
	{
		clear();
		m_ownsMemory = false;
		m_data = (T*)buffer;
		m_size = size;
		m_capacity = capacity;
	}

	void copyFromArray(const WI_Array& otherArray)
	{
		int otherSize = otherArray.size();
		resize (otherSize);
		otherArray.copy(0, otherSize, m_data);
	}

};

#endif //WI_OBJECT_ARRAY__
