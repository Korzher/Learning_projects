Для того чтобы запустить <br>
``docker compose up --build`` <br>
``docker compose up``

Для трека логов в реальном времени можно использовать
``docker logs -f techshop_nginx``

## Клиенты
<br>

```
Add client (POST)
``http://localhost:8080/api/v1/clients``
{
    "client_name": "Alice",
    "client_surname": "Charles",
    "gender" : "F",
    "birthday" : "1990-11-15T00:00:00Z",
    "country" : "Russia",
    "city" : "Moscow",
    "street" : "Koroleva"
}
```

Get client (GET)
```http://localhost:8080/api/v1/clients/search?name={name}&surname={surname}```
```
params
name     string
surname  string
```

Get all clients (GET)

``http://localhost:8080/api/v1/clients?offset={offset}&limit={limit}`` <br>
```
params 
offset   int
limit    int
```

Address change (PATCH)

``http://localhost:8080/api/v1/clients/{id}/address`` <br>
```
{
    "street": "Lenina",
    "city": "Saint-Peterburg",
    "country": "Russia"
}
```

Delete client (DELETE)

``http://localhost:8080/api/v1/clients/{id}``


## Поставщики
Add Supplier

``http://localhost:8080/api/v1/suppliers/add``
```
{
    "name": "Will & Co",
    "phone_number": "8-910-123-45-67",
    "city": "Saint-Peterburg",
    "country": "Russia",
    "street": "Alkov"
}
```

Delete Supplier

``http://localhost:8080/api/v1/suppliers/{id}``

Get All Suppliers

``http://localhost:8080/api/v1/suppliers``

Get Supplier

``http://localhost:8080/api/v1/suppliers/{id}``

Address Change

``http://localhost:8080/api/v1/suppliers/address``

```
{
    "ID": "10f2ad56-e91c-4ed7-acfe-1c777acb3b3a",
    "street": "Lenina",
    "city": "Saint-Peterburg",
    "country": "Russia"
}
```

## Товары

Добавить товар

Для получения imageBase64 нужно ввести команду
``base64 -w 0 {path/to/pic}``
и использовать полученную строку как {imageBase64}

Например:

``base64 -w 0 /home/desmonsu/Desktop/project/BE2_APIFromSpec.ID_1269320-1/src/pics/refrigirator.jpg``


``http://localhost:8080/api/v1/products/add``


```
{
    "name": "Refrigirator",
    "category": "Electronics",
    "price": 1999,
    "available_stock": 100,
    "supplier_id": "10f2ad56-e91c-4ed7-acfe-1c777acb3b3a",
    "image": "{{imageBase64}}"
}
```

Получение всех товаров

``http://localhost:8080/api/v1/products``

Получение отдельного товара

``http://localhost:8080/api/v1/products/{id}``

Вычитание товара

``http://localhost:8080/api/v1/products/subtract``

```
{
    "ID": "220eb9d1-425f-4018-92c5-4ad5d5e2d693",
    "amount" : 5
}
```

Удаление товара

``http://localhost:8080/api/v1/products/{id}``


Изображение

Получение изображения по id товара(GET)

``http://localhost:8080/api/v1/image/product/{id}``

Получение изображения по id картинки (GET)
``http://localhost:8080/api/v1/image/{id}``

Добавить изображение (POST)
``http://localhost:8080/api/v1/image``

```
{
    "product_id": "e48241ff-4741-4388-a729-1160c12cc970",
    "image" : "{{image}}"
}
```

Сменить изображение (PUt)

``http://localhost:8080/api/v1/image/{id}``

```
{
    "image" : "{{image}}"
}
```

Удалить изображение (DELETE)
``http://localhost:8080/api/v1/image/{id}``


Чтобы закрыть все контейнеры в докер
```
sudo docker ps
sudo docker inspect --format '{{.State.Pid}}' {id контейнера}
sudo kill -9 {результат прошлой команды}
```

Инициализация swagger
```
swag init -g cmd/ApiFromSpec/main.go --parseInternal --parseDependency
```