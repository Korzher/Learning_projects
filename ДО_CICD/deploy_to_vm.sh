#!/bin/bash
set -e

REMOTE_USER="cicd"
REMOTE_HOST="10.31.170.203"
REMOTE_DEST="/usr/local/bin"
CAT="src/SimpleBashUtils/cat/s21_cat"
GREP="src/SimpleBashUtils/grep/s21_grep"
DEPLOY_KEY="./deploy_key"

if [[ ! -f "$DEPLOY_KEY" ]]; then
  echo "Файл deploy_key не найден!"
  exit 2
fi
chmod 600 "$DEPLOY_KEY"

if [[ ! -f "$CAT" ]]; then
  echo "Файл не найден: $CAT"
  exit 1
fi

if [[ ! -f "$GREP" ]]; then
  echo "Файл не найден: $GREP"
  exit 1
fi

scp -i "$DEPLOY_KEY" -o StrictHostKeyChecking=accept-new "$CAT" "$REMOTE_USER@$REMOTE_HOST:/tmp/"
scp -i "$DEPLOY_KEY" -o StrictHostKeyChecking=accept-new "$GREP" "$REMOTE_USER@$REMOTE_HOST:/tmp/"
ssh -i "$DEPLOY_KEY" -o StrictHostKeyChecking=accept-new "$REMOTE_USER@$REMOTE_HOST" \
  "sudo /usr/bin/mv /tmp/* $REMOTE_DEST/"
