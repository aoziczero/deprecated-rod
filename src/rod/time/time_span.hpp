#ifndef __rod_time_time_span_h__
#define __rod_time_time_span_h__

namespace rod {

class time_span {
public:
	time_span( void );
	explicit time_span( const int64_t delta );
	time_span( const time_span& rhs );

	time_span( const int days
			 , const int hours
			 , const int minutes
			 , const int seconds
			 , const int milliseconds 
			 , const int microseconds );

	const time_span& operator=( const time_span& rhs );

	~time_span( void );
	
	const int64_t delta( void ) const;
public:
	int64_t total_micro_seconds( void ) const ;
    int64_t total_milli_seconds( void ) const ;
    int64_t total_seconds( void ) const ;
    int64_t total_minutes( void ) const ;
    int64_t total_hours( void ) const ;
    int64_t total_days( void ) const ;
public:
	bool operator==( const time_span& rhs ) const;
    bool operator!=( const time_span& rhs ) const;
    bool operator> ( const time_span& rhs ) const;
    bool operator>=( const time_span& rhs ) const;
    bool operator< ( const time_span& rhs ) const;
    bool operator<=( const time_span& rhs ) const;
public:
	time_span  operator+ ( const time_span& rhs ) const;
    time_span  operator- ( const time_span& rhs ) const;
	time_span  operator* (const int times ) const;
	time_span  operator/ (const int times ) const;

	time_span& operator+=( const time_span& rhs );
    time_span& operator-=( const time_span& rhs );
	time_span& operator*=(const int times ) ;
	time_span& operator/=(const int times ) ;
    
	time_span  operator-( void ) const;
public:
    static time_span from_micro_seconds( const int64_t v );
    static time_span from_milli_seconds( const int64_t v );
    static time_span from_seconds( const int32_t v );
    static time_span from_minutes( const int32_t v );
    static time_span from_hours( const int32_t v );
    static time_span from_days( const int32_t v );
private:
	int64_t _delta;
public:
	static const time_span infinite;
};

}

#endif