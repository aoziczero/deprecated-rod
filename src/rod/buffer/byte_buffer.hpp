#ifndef __rod_buffer_byte_byffer_h__
#define __rod_buffer_byte_byffer_h__

namespace rod {
namespace buffer{

// refrence counted
class byte_buffer{
public:
	byte_buffer(void);
	byte_buffer(std::size_t cap);
	~byte_buffer(void);

	std::size_t capacity(void);
private:
	std::size_t _capacity;
};

}}

#endif