#!/bin/bash
spawn-fcgi -p 8080 /app/server.fcgi
exec nginx -g "daemon off;"

e4bf78f303f1