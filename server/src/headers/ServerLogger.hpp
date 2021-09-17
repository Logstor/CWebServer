#include <memory>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

class ServerLogger : public Logger
{
public:
    void stop( void )
    {
        cout << "Stopping" << endl;
    }

    void start( const shared_ptr< const Settings > &settings )
    {
        cout << "Starting Server on " << settings->get_bind_address() << ":" << settings->get_port() << endl;
    }

    void log( const Level, const char* format, ... )
    {
        va_list arguments;
        va_start( arguments, format );

        vfprintf( stderr, format, arguments );
        fprintf( stderr, "\n" );

        va_end( arguments );
    }

    void log_if( bool expression, const Level level, const char* format, ... )
    {
        if ( expression )
        {
            va_list arguments;
            va_start( arguments, format );
            log( level, format, arguments );
            va_end( arguments );
        }
    }
};