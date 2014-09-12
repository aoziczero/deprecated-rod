#ifndef __rod_buffer_byte_byffer_ref_h__
#define __rod_buffer_byte_byffer_ref_h__

namespace rod {
namespace buffer{

// provide byte buffer interface for user allocated memory
class byte_buffer_ref {
public:
	byte_buffer_ref( void* ptr , const std::size_t cap );
	byte_buffer_ref(byte_buffer_ref&& rhs);
	const byte_buffer_ref& operator=(byte_buffer_ref&& rhs);
	~byte_buffer_ref(void);

	std::size_t capacity(void);
	uint8_t* wr_ptr(void);
	int wr_ptr(const int move);

	uint8_t* rd_ptr(void);
	int rd_ptr(const int move);

	std::size_t length(void);

	std::size_t space(void);

	std::size_t read(void* dst, const std::size_t sz);
	std::size_t peak(void* dst, const std::size_t sz);
	std::size_t write(void* src, const std::size_t sz);
private:
	byte_buffer_ref(const byte_buffer_ref& rhs);
	const byte_buffer_ref& operator=(const byte_buffer_ref& rhs);
	void swap(byte_buffer_ref& buffer);

private:
	void* _ptr;
	std::size_t _capacity;
	std::size_t _rd_pos;
	std::size_t _wr_pos;
};

}
}

#endif