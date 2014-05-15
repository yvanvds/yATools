yATools
=======

yvan's Admin Tools

prequisites
===========
apt-get install libmysql++-dev
apt-get install libmysqlcppconn-dev
apt-get install libldap2-dev

gcc
===
needs at least version 4.8. Check with 
gcc --version

boost-process
=============
is not part of boost. Copy from dependencies to boost include dir
cp -fr dependencies/boost_process/boost/* /usr/include/boost

Wt
== 
look for installation instructions on webtoolkit.eu

