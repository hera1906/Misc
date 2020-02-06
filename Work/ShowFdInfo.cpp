#include <unistd.h>
#include <fcntl.h>


bool ShowFdInfo( int fd )
{
    char buf[256];
    
    int fd_flags = fcntl( fd, F_GETFD ); 
    if ( fd_flags == -1 ) return false;
    
    int fl_flags = fcntl( fd, F_GETFL ); 
    if ( fl_flags == -1 ) return false;
    
    char path[256];
    sprintf( path, "/proc/self/fd/%d", fd );
    
    memset( &buf[0], 0, 256 );
    ssize_t s = readlink( path, &buf[0], 256 );
    if ( s == -1 )
    {
        cerr << " (" << path << "): " << "not available" << endl;
        return false;
    }
    cerr << fd << " (" << buf << "): ";
    
    if ( fd_flags & FD_CLOEXEC )  cerr << "cloexec ";
    
    // file status
    if ( fl_flags & O_APPEND   )  cerr << "append ";
    if ( fl_flags & O_NONBLOCK )  cerr << "nonblock ";
    
    // acc mode
    if ( fl_flags & O_RDONLY   )  cerr << "read-only ";
    if ( fl_flags & O_RDWR     )  cerr << "read-write ";
    if ( fl_flags & O_WRONLY   )  cerr << "write-only ";
    
    if ( fl_flags & O_DSYNC    )  cerr << "dsync ";
    if ( fl_flags & O_RSYNC    )  cerr << "rsync ";
    if ( fl_flags & O_SYNC     )  cerr << "sync ";
    
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = 0;
    fl.l_start = 0;
    fl.l_len = 0;
    fcntl( fd, F_GETLK, &fl );
    if ( fl.l_type != F_UNLCK )
    {
        if ( fl.l_type == F_WRLCK )
            cerr << "write-locked";
        else
            cerr << "read-locked";
        cerr << "(pid:" << fl.l_pid << ") ";
    }
    cerr << endl;
    return true;
}

void ShowFdInfo()
{
    int numHandles = getdtablesize();
    
    for ( int i = 0; i < numHandles; i++ )
    {
        int fd_flags = fcntl( i, F_GETFD ); 
        if ( fd_flags == -1 ) continue;
    
        ShowFdInfo( i );
    }
}
