# Here is a C realisation of a bash func "ls", that currently support flags:
| flag| description                            |
|-----|----------------------------------------|
|  -R | list subdirectories recursively        |
|  -a | do not ignore entries starting with '.'|
|  -l | use long listing format                |
|  -i | print the index number of each file    |
 
# Realisation:
 First of all the file is opened with flags "O_RDONLY | O_DIRECTORY"
 
 info about file, such as inode and its type is got from struct "linux_dirent64" using func "getdents64"
 
 file size and permissions for user are known using "stat"
 
 info about the user, owner of file is got from struct "passwd" using func "getpwuid"
 
 # Make:
  Use "make ls" to compile programm
  
  Use "make clean" to delete all object object and executable files
  
  (for linux only)
 
# Run:
 To run use "make ls" and "./ls dir -flag" 
##### (You can combine flags together)


# Verson:
  lags in -R are fixed
  
## Plan:
In later updates i am going to add more flags
