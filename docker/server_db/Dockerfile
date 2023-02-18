# Smart home managment platform - server with database
FROM ubuntu:20.04 AS builder

WORKDIR /app

COPY ./ ./

RUN apt-get update
RUN apt-get install make
RUN apt install g++ -y
#RUN apt-get install -y mysql-server mysql-client

RUN apt-get install -y libmysqlcppconn-dev
RUN apt-get install -y libmysqlclient-dev
#RUN apt-get install -y libmysql++-dev


WORKDIR /app/main/server_db
RUN make

# FROM debian:unstable-20230109-slim AS runtime

# WORKDIR /

# COPY --from=builder /app .

ARG BUILDTIME_VARIABLE=$LD_LIBRARY_PATH:../../library/ 
ENV LD_LIBRARY_PATH=$BUILDTIME_VARIABLE
RUN export LD_LIBRARY_PATH

# WORKDIR /main/server_db

EXPOSE 8080

ENTRYPOINT ["./main_server_db"]

