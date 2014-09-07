#ifndef __rod_buffer_rc_buffer_h__
#define __rod_buffer_rc_buffer_h__

namespace rod {
namespace buffer {

class rc_buffer{
public:
	explicit rc_buffer(std::size_t cap);
	~rc_buffer(void);

private:
	int add_refrence(void);
	int remove_reference(void);
private:
	void* _ptr;
	std::size_t _capacity;
};

}
}

#endif