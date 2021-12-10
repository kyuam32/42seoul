#! /bin/bash

docker build -t ft_server ./
docker run -it --name test -e AUTOIDX=0 -p 80:80 -p 443:443 ft_server
