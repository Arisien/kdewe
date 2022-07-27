# KDEWE
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

KDEWE is a CLI utility for the KDE Wallpaper Engine plugin

## Todo

### JSON

* Implement JSONValue(null)

```c++
class _Null {};

#define null _Null();
```

* fully implement JSON_UNDEFINED into serializer and parser

* Parser: handle whitespace at every possible position (not just some like currently)

* JSON constructor to support: 
```c++
JSON json({ {"pi", JSONValue(3.14)}, {"e", JSONValue(2.7)} });
```

## Contributors

* [Arisien](https://github.com/Arisien) - Main developer

## License
KDEWE is licensed under the [MIT](LICENSE) license. Feel free to fork the repository or modify the code as you see fit.
