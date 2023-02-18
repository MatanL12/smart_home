# Smart home managment platform - client
FROM ubuntu:20.04 AS builder

WORKDIR /app

COPY ./ ./

RUN apt-get update
RUN apt-get install make
RUN apt install g++ -y

WORKDIR /app/main/client
RUN make


FROM debian:unstable-20230109-slim AS runtime

WORKDIR /

COPY --from=builder /app/main/client .

EXPOSE 8080

ENTRYPOINT ["./main_client"]
