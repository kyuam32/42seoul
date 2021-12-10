# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/18 19:06:46 by namkyu            #+#    #+#              #
#    Updated: 2021/06/17 18:49:57 by namkyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster

# APT UPDATE
RUN apt-get -y update
RUN apt-get -y upgrade

RUN apt-get -y install nginx
RUN apt-get -y install openssl
RUN mkdir -p /var/www/wordpress

COPY ./tools/run.sh run.sh
COPY ./config/default ./etc/nginx/sites-available/default

CMD bash run.sh
