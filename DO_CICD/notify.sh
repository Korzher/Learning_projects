#!/bin/bash

BOT_TOKEN="-"
CHAT_ID="1413181387"
STAGE="$1"
STATUS="$2"
TEXT=""

if [[ "$STAGE" == "CI start" ]]; then
     TEXT="Запуск процесса CI
Автор: $CI_COMMIT_AUTHOR
Коммит: $CI_COMMIT_MESSAGE
CI_SERVER_NAME - $CI_SERVER_NAME"
elif [[ "$STAGE" == "CI finish" ]]; then
     if [[ "$STATUS" == "success" ]]; then
       TEXT="Интеграция завершена успешно"
     else
       TEXT="Ошибка интеграции"
     fi
elif [[ "$STAGE" == "CD start" ]]; then
     TEXT="Запуск процесса CD
Автор: $CI_COMMIT_AUTHOR
Коммит: $CI_COMMIT_MESSAGE"
elif [[ "$STAGE" == "CD finish" ]]; then
     if [[ "$STATUS" == "success" ]]; then
       TEXT="Деплой завершен успешно"
     else
       TEXT="Ошибка деплоя"
     fi
else
     TEXT="Неизвестная стадия: $STAGE"
fi

curl -s -X POST "https://api.telegram.org/bot${BOT_TOKEN}/sendMessage" \
     -d "chat_id=${CHAT_ID}" \
     -d "text=${TEXT}"