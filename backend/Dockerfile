FROM node:8

RUN mkdir -p /usr/opt/app
WORKDIR /usr/opt/app
COPY package.json /usr/opt/app
RUN npm install --silent

ADD . /usr/opt/app

EXPOSE 3000