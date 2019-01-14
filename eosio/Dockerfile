FROM eosio/eos-dev:v1.5.2

RUN apt-get update && apt-get install curl -y

ADD . /opt/app

VOLUME /opt/app
WORKDIR /opt/eosio/bin

ENV DATA_DIR /root/.local/share
ENV CONFIG_DIR /opt/app/config

EXPOSE 8888
EXPOSE 9876

CMD /opt/app/scripts/start.sh
