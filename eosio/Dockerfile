FROM eosio/eos-dev:v1.5.2

RUN apt-get update && apt-get install curl -y
RUN wget https://github.com/EOSIO/eosio.cdt/releases/download/v1.5.0/eosio.cdt_1.5.0-1_amd64.deb
RUN apt install ./eosio.cdt_1.5.0-1_amd64.deb

ADD . /opt/app

VOLUME /opt/app
WORKDIR /opt/eosio/bin

ENV DATA_DIR /root/.local/share
ENV CONFIG_DIR /opt/app/config

EXPOSE 8888
EXPOSE 9876

CMD /opt/app/scripts/start.sh
