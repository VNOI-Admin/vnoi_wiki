# Xử lý xâu

**Xâu** (**string**) xuất hiện rất nhiều trong các bài toán. Bài viết này giới thiệu sơ qua một số thuật ngữ cũng như thuật toán về xâu.

# Thuật ngữ

- Một xâu $X$ là **xâu con** (**substring**) của một xâu $Y$ nếu $X$ là một chuỗi các ký tự liên tiếp của $Y$. Ví dụ: `ab` và `bc` là 2 xâu con của `abcd`. Nhưng `ac` thì không phải là xâu con của `abcd`.
- Một xâu $X$ là **tiền tố** (**prefix**) của một xâu $Y$ nếu $X$ là xâu con của $Y$ và $X$ xuất hiện ở đầu của xâu $Y$. Ví dụ: `ab` là tiền tố của `abcd`, nhưng `bc` **không** phải là tiền tố của `abcd`.
  Một xâu $X$ là một **tiền tố không tầm thường** (**proper prefix**) của xâu $Y$ nếu nó là tiền tố của xâu $Y$ và khác xâu $Y$.
- Một xâu $X$ là **hậu tố** (**hậu tố**) của một xâu $Y$ nếu $X$ là xâu con của $Y$ và $X$ xuất hiện ở cuối của xâu $Y$. Ví dụ: `cd` là hậu tố của `abcd`, nhưng `bc` **không** phải là hậu tố của `abcd`.
  Một xâu $X$ là một **hậu tố không tầm thường** (**proper suffix**) của xâu $Y$ nếu nó là hậu tố của xâu $Y$ và khác xâu $Y$.

# Các dạng bài

## So khớp chuỗi (string matching)

Cho một xâu $T$ và xâu $S$. Tìm tất cả các lần xuất hiện của xâu $S$ trong xâu $T$.

Ví dụ:

```
S = abc
T = abcabcabc

Các lần xuất hiện: 1, 4, 7.
```

Bài toán này còn được gọi là tìm kiếm **cây kim** (**needle**) trong **đống rơm** (**haystack**), vì nó xuất hiện trong thực tế khi ta cần tìm một xâu rất nhỏ trong một lượng dữ liệu rất lớn (ví dụ Google cần tìm từ khóa trong hàng tỉ tỉ trang web).

Có 3 thuật toán chính để giải quyết bài này, đó là:

- [[Thuật toán KMP|translate/wcipeg/kmp]]
- [[Hash|algo/string/hash]]
- [[Z Algorithm|translate/codeforces/z-algo]]


## Xâu đối xứng (Palindrome)

Palindrome hay còn gọi là xâu đối xứng, xâu đối gương là tên gọi của những xâu kí tự mà khi viết từ phải qua trái hay từ trái qua phải thì xâu đó không thay đổi. VD: MADAM, IOI,...

Có rất nhiều bài tập liên quan đến xâu đối xứng. Các bạn có thể tìm đọc ở trong các bài viết:

- [[Một vài bài tập QHD về Palindrome|algo/dp/palindrome-problems]]
- [[Hash|algo/string/hash]]
- [[Palindrome Tree|translate/codeforces/palindrome-tree]]

## Suffix Structures

Có một lớp CTDL được gọi chung là Suffix Structures gồm:

- [[Suffix Array|algo/data-structures/suffix-array]]
- Suffix Automaton
- Suffix Tree
- Aho Corasick

Gọi chung như vậy vì các CTDL này có thể dùng thay thế nhau để giải quyết cùng một lớp bài toán liên quan đến các suffix của cây.
