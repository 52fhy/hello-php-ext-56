# learn-php-ext-56

``` bash
cd /work/php-ext/php-5.6.33/ext/hello

phpize && ./configure && make && make install
```

then add `hello.so` to php.ini:
```
extension=hello.so
```
