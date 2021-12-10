#!bin/sh

docker build -t test ./
docker run -it --name test test
