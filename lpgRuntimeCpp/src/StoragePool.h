#pragma once
#include <cassert>
#include <cstring>


namespace Jikes { // Open namespace Jikes block


	//
	// This Storage pool is similar to dynamic arrays (class Tuple). The
	// difference is that instead of a Next() function we have an Alloc(size_t)
	// function. The value of the size_t argument represents the size of the
	// object to allocate. The allocated memory is guaranteed to be
	// zero-initialized.
	//
	// All AST nodes for a given parse should be allocated from the same storage
	// pool, so they have a placement new operator that requires a StoragePool.
	// You should never delete an AST object, as all resources they allocate come
	// from the same pool. Instead, to reclaim memory when processing is complete,
	// simply delete the underlying storage pool.
	//
	class StoragePool
	{
	public:
		typedef void* Cell;

		inline size_t Blksize() { return 1U << log_blksize; }
		bool IsCloneForStruct() const
		{
			return clone_for_struct;
		}
		void SetCloneForStruct(bool _b)
		{
			clone_for_struct = _b;
		}
	private:
		bool clone_for_struct = false;
		Cell** base;
		unsigned base_size; // number of segment slots in base
		unsigned base_index; // index of current non-full segment
		unsigned offset; // offset to next free pointer in base[base_index]

		unsigned log_blksize; // log2(words per segment)
		unsigned base_increment; // number of segment slots to add when growing

								 //
								 // Allocate another block of storage for the storage pool. block_size
								 // allows the creation of larger than normal segments, which are rare,
								 // but are sometimes requested by AstArray.
								 //
		void AllocateMoreSpace(size_t block_size = 0)
		{
			//
			// This advances base_index to the next slot unless this is the first
			// allocation. Then it allocates a segment to live in that slot.
			// The offset field should only be 0 after construction or after a
			// reset, when base_index should stay at 0.  All other times, offset
			// is nonzero, so we allocate advance base_index.
			//
			assert(offset ? base != NULL : !base_index);
			if (offset)
				base_index++;
			if (base_index == base_size)
			{
				unsigned old_base_size = base_size;
				Cell** old_base = base;
				base_size += base_increment;
				base = new Cell * [base_size];
				if (old_base)
				{
					memcpy(base, old_base, old_base_size * sizeof(Cell*));
					delete[] old_base;
				}
				memset(base + old_base_size, 0, base_increment * sizeof(Cell*));
			}
			if (block_size)
			{
				assert(block_size > Blksize());
				delete[] base[base_index];
				base[base_index] = new Cell[block_size];
			}
			else if (!base[base_index])
			{
				block_size = Blksize();
				base[base_index] = new Cell[block_size];
			}
			memset(base[base_index], 0, block_size * sizeof(Cell));
		}

	public:
		//
		// Constructor of a storage pool. The parameter is the number of tokens
		// which the AST tree will contain.
		//
		StoragePool(unsigned num_tokens)
			: base(NULL)
			, base_size(0)
			, base_index(0)
			, offset(0)
		{
			//
			// Make a guess on the size that will be required for the ast
			// based on the number of tokens. On average, we have about 1 node
			// to 2 tokens, but about 10 words (40 bytes) per node. We add some
			// fudge factor to avoid reallocations, resulting in num_tokens * 8.
			//
			unsigned estimate = num_tokens << 3;

			//
			// Find a block of size 2**log_blksize that is large enough
			// to satisfy our estimate.
			//
			for (log_blksize = 8;
				(1U << log_blksize) < estimate && log_blksize < 31;
				log_blksize++)
				;

			if (log_blksize < 13) // estimate is < 2**(13+2) == 32k
			{
				base_increment = 1U << (log_blksize - 8);
				log_blksize = 8; // fragment in 2**(8+2) == 1k chunks
			}
			else if (log_blksize < 17) // estimate is < 2**(17+2) == 512k
			{
				base_increment = 1U << (log_blksize - 10);
				log_blksize = 10; // fragment in 2**(10+2) == 4k chunks
			}
			else // estimate is >= 512k, which is rare
			{
				base_increment = 1U << (log_blksize - 12);
				log_blksize = 12; // fragment in 2**(12+2) == 16k chunks
			}

			//
			// Double the size of the base and add an extra margin to avoid
			// reallocating the base, especially for things like Cloning.
			//
			base_increment += base_increment + 3;
		}

		//
		// Destructor of a storage pool. This frees the memory of all of the AST
		// nodes allocated in this pool.
		//
		virtual ~StoragePool()
		{
			if (base)
				for (unsigned i = 0; i <= base_index; i++)
					delete[] base[i];
			delete[] base;
		}

		//
		// Alloc allocates an object of size n in the pool and returns a pointer
		// to it. The memory will be zero-initialized.
		//
		inline void* Alloc(size_t n)
		{
			unsigned chunk_size = (n + sizeof(Cell) - 1) / sizeof(Cell);
			if (chunk_size > Blksize())
			{
				//
				// Handle large requests separately. These are rare, when an
				// AstArray is requested that is larger than a segment. In this
				// case, we allocate the extra large segment in the next free
				// slot, and swap it with the previous segment if that one still
				// had room.
				//
				AllocateMoreSpace(chunk_size);
				Cell result = base[base_index];
				if (base_index)
				{
					Cell* temp = base[base_index];
					base[base_index] = base[base_index - 1];
					base[base_index - 1] = temp;
				}
				return result;
			}
			if (!base || offset + chunk_size > Blksize())
			{
				//
				// Here, we overflow the current segment, but fit in a normal
				// next segment.
				//
				AllocateMoreSpace();
				offset = 0;
			}
			Cell result = base[base_index] + offset;
			offset += chunk_size;
			return result;
		}

		//
		// This function is used to reset the Storage pool. This action
		// automatically invalidates all objects that had been allocated in the
		// pool. At least, YOU should assume it does!!!
		//
		inline void Reset()
		{
			base_index = 0;
			offset = 0;
		}


	};






} // Close namespace Jikes block


