#ifndef __rod_buffer_rc_buffer_h__
#define __rod_buffer_rc_buffer_h__
#include <atomic>
namespace rod {
namespace buffer {

class rc_buffer{
public:
	explicit rc_buffer(std::size_t cap);
	rc_buffer(const rc_buffer& rhs);
	const rc_buffer& operator=(const rc_buffer& rhs);
	~rc_buffer(void);

	std::size_t capacity(void);
	void* ptr(void);

	int refrence_count(void);
private:
	int _add_refrence(void);
	int _remove_reference(void);
	std::atomic<int>* _refrence_counter(void);
private:
	void* _ptr;
	std::size_t _capacity;
};

}
}

#endif