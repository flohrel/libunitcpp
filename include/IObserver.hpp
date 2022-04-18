#ifndef __IOBSERVER__H__
# define __IOBSERVER__H__

class IObserver
{
	public:
		IObserver( void );
		IObserver( const IObserver& src );
		~IObserver( void );

		IObserver&
		operator=( const IObserver& rhs );

};

#endif