#!/bin/bash

service php7.3-fpm start

curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
./wp-cli.phar core install --path=/var/www/wordpress --url=${MY_URL}  --title=${MSQL_TITLE} --admin_user=${MYSQL_USER} --admin_password=${MYSQL_PASSWORD} --admin_email=${MY_EMAIL} --allow-root

./wp-cli.phar plugin install redis-cache --path=/var/www/wordpress --allow-root
./wp-cli.phar plugin activate redis-cache --path=/var/www/wordpress --allow-root
./wp-cli.phar redis enable --path=/var/www/wordpress --allow-root

service php7.3-fpm stop
php-fpm7.3 -F