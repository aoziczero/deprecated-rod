#ifndef __rod_buffer_byte_byffer_h__
#define __rod_buffer_byte_byffer_h__

#include <rod/buffer/rc_buffer.hpp>

namespace rod {
namespace buffer{

// refrence counted
class byte_buffer{
public:
	struct position {
		std::size_t rd_pos;
		std::size_t wr_pos;
	};
public:
	explicit byte_buffer( const std::size_t cap);
	byte_buffer(const byte_buffer& rhs);
	byte_buffer(byte_buffer&& rhs);

	const byte_buffer& operator=(const byte_buffer& rhs);
	const byte_buffer& operator=( byte_buffer&& rhs);

	~byte_buffer(void);

	// buffer size
	std::size_t capacity(void);

	void swap(byte_buffer& buffer);

	// writable pointer
	uint8_t* wr_ptr( void );
	int wr_ptr( const int move );

	// readable pointer
	uint8_t* rd_ptr( void );
	int rd_ptr( const int move );

	int reserve( const std::size_t newsz );

	// adjust data
	int adjust( void );

	// data size
	std::size_t length( void );
	
	// writable size
	std::size_t space( void );

	std::size_t read(void* dst , const std::size_t sz );
	std::size_t peak(void* dst , const std::size_t sz );
	std::size_t write( void* src , const std::size_t sz );


	position current_position( void ) const;
	void     seek_position( const position& p );
private:
	rod::buffer::rc_buffer _buffer;
	std::size_t _rd_pos;
	std::size_t _wr_pos;
};

}}

#endif