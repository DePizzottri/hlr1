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

RUN echo edds

RUN git clone https://github.com/DePizzottri/highload_r1.git \
&&  cd highload_r1 && mkdir build && cd ./build && cmake .. && make


RUN echo 'host postgres postgres all  md5' > /etc/postgresql/9.5/main/pg_hba.conf
#RUN echo 'host all all 127.0.0.1 md5' > /etc/postgresql/9.5/main/pg_hba.conf
RUN echo 'local all all trust' >> /etc/postgresql/9.5/main/pg_hba.conf
RUN echo "listen_addresses = '*'" >> /etc/postgresql/9.5/main/postgresql.conf
#RUN /etc/init.d/postgresql start && psql -U postgres -a -f ./highload_r1/src/postgres.sql

RUN apt-get install -y unzip

EXPOSE 80

COPY start start

#ADD *.json /tmp/data/

CMD ./start
