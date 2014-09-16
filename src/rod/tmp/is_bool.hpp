#ifndef __rod_tmp_is_bool_h__
#define __rod_tmp_is_bool_h__

namespace rod {
namespace tmp {

template < typename object_type > class is_bool {
public:
	enum {
		value = 0,
	};
};


template <> class is_bool<bool> {
public:
	enum {
		value = 1,
	};
};



}}

#endif