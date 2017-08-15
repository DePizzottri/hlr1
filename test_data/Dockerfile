FROM ubuntu:16.10

WORKDIR /root

RUN apt-get update
RUN apt-get install -y apt-utils g++ cmake git postgresql libpq-dev postgresql-server-dev-9.5 \
    libboost-dev libboost-system-dev libboost-filesystem-dev

RUN git clone https://github.com/nlohmann/json.git
RUN git clone https://github.com/rbock/sqlpp11.git
RUN git clone https://github.com/HowardHinnant/date.git

RUN git clone --recursive https://github.com/Corvusoft/restbed.git
RUN cd restbed && mkdir build && cd ./build && cmake -DBUILD_SSL=NO .. && make && make install

RUN git clone https://github.com/matthijs/sqlpp11-connector-postgresql.git
RUN cd sqlpp11-connector-postgresql && mkdir build && cd ./build && cmake .. && make \
    && LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/src

RUN echo daas

RUN git clone https://github.com/DePizzottri/highload_r1.git
RUN cd highload_r1 && mkdir build && cd ./build && cmake .. && make VERBOSE=1


RUN echo 'host postgres postgres ::1/128 md5' > /etc/postgresql/9.5/main/pg_hba.conf
RUN echo 'local all all trust' >> /etc/postgresql/9.5/main/pg_hba.conf
RUN echo "listen_addresses = '*'" >> /etc/postgresql/9.5/main/postgresql.conf
#RUN /etc/init.d/postgresql start && psql -U postgres -a -f ./highload_r1/src/postgres.sql

EXPOSE 80
EXPOSE 5432

COPY start start

CMD ./start
