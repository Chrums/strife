#!/bin/bash

docker container kill $(docker ps -q)
docker container rm $(docker ps -a -q)

docker image build -t strife .
docker run -it --rm -v "$(pwd):/project" -p 8080:8080 strife /bin/bash --login