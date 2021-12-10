# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 14:43:50 by namkyu            #+#    #+#              #
#    Updated: 2021/04/21 17:04:17 by namkyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

echo "Check autoindex..."
test $AUTOIDX -eq 0 && sed -i -e 's/; #index.nginx-debian./ index.nginx-debian./g' default && sed -i -e 's/autoindex on;/#autoindex on;/g' default

echo "Moving files in container..."
# NGINX DEFAULT FILE SETUP
mv default ../etc/nginx/sites-available

# WORDPRESS && PHPMYADMIN SETUP
mv wordpress ../var/www/html
mv phpMyAdmin ../var/www/html

# SET OWN & ACCESS
chown -R www-data:www-data ../var/www/*
chmod -R 755 ../var/www/*

echo "Generate SSC ..."
# GENERATE PERSONAL KEY && SSC
openssl req -newkey rsa:4096 -days 365 -nodes -x509 -subj "/C=KR/L=Seoul/O=42seoul/OU=nlee/CN=localhost" -keyout ../etc/ssl/private/ft_server.key -out ../etc/ssl/certs/ft_server.crt
chmod 600 ../etc/ssl/certs/ft_server.crt ../etc/ssl/private/ft_server.key

echo "Create wordpress admin"
# CREATE USER FOR WORDPRESS ADMIN
service mysql start
echo "CREATE DATABASE IF NOT EXISTS wordpress;" | mysql -u root --skip-password
echo "CREATE USER IF NOT EXISTS 'nlee'@'localhost' IDENTIFIED BY 'nlee';" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'nlee'@'localhost' WITH GRANT OPTION;" | mysql -u root --skip-password

# ENGINE START
service nginx start
service php7.3-fpm start

# CLEAN UP WORK DIR
cd ../
rm -rf ./setup
bash