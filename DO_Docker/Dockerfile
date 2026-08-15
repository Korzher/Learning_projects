FROM ubuntu:24.04
RUN apt-get update && \
    apt-get install -y gcc libfcgi-dev spawn-fcgi nginx adduser && \
    adduser --system --no-create-home --disabled-password --disabled-login --shell /bin/false --group nginx
COPY server/simple_server.c /app/simple_server.c
RUN gcc /app/simple_server.c -o /app/server.fcgi -lfcgi
COPY nginx/nginx.conf /etc/nginx/nginx.conf
COPY start.sh /start.sh
RUN chmod +x /app/server.fcgi /start.sh

CMD ["/start.sh"]