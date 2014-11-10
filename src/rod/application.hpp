#ifndef __rod_application_h__
#define __rod_application_h__

namespace rod {

class application {
public:
	rod::tstring name( void ) const;


private:
	rod::tstring _name( void );
};

}


#endif