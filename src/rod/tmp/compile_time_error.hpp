#ifndef __rod_tmp_compile_time_error_h__
#define __rod_tmp_compile_time_error_h__

namespace rod {
namespace tmp {

template < bool > class compile_time_error;
template <> class compile_time_error< true >{};


}}

#endif