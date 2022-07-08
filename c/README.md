# c

```
clang -O0 -Wall -Wextra -Wno-logical-op-parentheses -lm -std=c11 "${file}" -o "${file_path}/${file_base_name}" && "${file_path}/${file_base_name}"
```

With sanitizers:

```
clang -O0 -Wall -Wextra -Wno-logical-op-parentheses -fsanitize=address,undefined -lm -std=c11 "${file}" -o "${file_path}/${file_base_name}" && "${file_path}/${file_base_name}"
```
