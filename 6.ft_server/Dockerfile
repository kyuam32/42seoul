# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 14:11:29 by namkyu            #+#    #+#              #
#    Updated: 2021/04/21 17:40:29 by namkyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster

# APT UPDATE
RUN apt-get -y update
RUN apt-get -y upgrade

# NGINX
RUN apt-get -y install nginx

# OPENSSL
RUN apt-get -y install openssl

# PHP
RUN apt-get -y install php7.3-fpm
RUN apt-get -y install php-mysql
RUN apt-get -y install php-mbstring

# MARIA DB
RUN apt-get -y install mariadb-server

# UTLIS
RUN apt-get -y install vim

# AUTOINDEX FLAG
ENV AUTOIDX 1

WORKDIR /setup
COPY ./srcs/wordpress wordpress
COPY ./srcs/phpMyAdmin phpMyAdmin
COPY ./srcs/default default
COPY ./srcs/run.sh run.sh

CMD bash run.sh