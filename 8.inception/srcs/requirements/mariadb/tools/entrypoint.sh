#! /bin/bash

./run.sh
service mysql start
mysql -u root -p$MY_SQL_ROOT_PWD < setup.sql
chown -R mysql:mysql /var/lib/mysql
kill -9 `ps -ef | grep mysql | awk '{print $2}'`

mysqld_safe --user=root
