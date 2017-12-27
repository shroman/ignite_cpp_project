## Building Ignite

```
echo "export IGNITE_HOME=/home/xxx/apache-ignite-fabric-2.3.0-bin" >> ~/.bashrc
echo "export JAVA_HOME=/home/x/libexec64/jdk64-1.8.0" >> ~/.bashrc
. ~/.bashrc
cd platforms/cpp/
// update autoconf
vi configure.ac
    #AC_PROG_CPP
    #AM_PROG_AR
    AC_PROG_CXX
// remove all "c++03" from Makefile.am

libtoolize && aclocal && autoheader && automake --add-missing && autoreconf
./configure --disable-odbc

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/x/libexec64/jdk64-1.8.0/jre/lib/amd64/server/:.
make
sudo make install
```

## Building project

```
cmake .
make
```
