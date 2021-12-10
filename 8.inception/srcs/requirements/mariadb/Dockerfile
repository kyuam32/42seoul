# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/18 19:06:46 by namkyu            #+#    #+#              #
#    Updated: 2021/06/15 21:46:44 by namkyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get install -y mariadb-server procps

COPY ./mariadb.conf.d/50-server.cnf /etc/mysql/my.cnf
COPY ./tools/run.sh ./run.sh
COPY ./tools/entrypoint.sh ./entrypoint.sh
RUN chmod 775 ./entrypoint.sh

CMD ./entrypoint.sh

