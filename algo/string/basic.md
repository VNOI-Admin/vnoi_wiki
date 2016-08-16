# Xử lý xâu

**Xâu** (**string**) xuất hiện rất nhiều trong các bài toán. Bài viết này giới thiệu sơ qua một số thuật ngữ cũng như thuật toán về xâu.

# Thuật ngữ

- Một xâu $X$ là **xâu con** (**substring**) của một xâu $Y$ nếu $X$ là một chuỗi các ký tự liên tiếp của $Y$. Ví dụ: `ab` và `bc` là 2 xâu con của `abcd`. Nhưng `ac` thì không phải là xâu con của `abcd`.
- Một xâu $X$ là **tiền tố** (**prefix**) của một xâu $Y$ nếu $X$ là xâu con của $Y$ và $X$ xuất hiện ở đầu của xâu $Y$. Ví dụ: `ab` là tiền tố của `abcd`, nhưng `bc` **không** phải là tiền tố của `abcd`.
  Một xâu $X$ là một **tiền tố không tầm thường** (**proper prefix**) của xâu $Y$ nếu nó là tiền tố của xâu $Y$ và khác xâu $Y$.
- Một xâu $X$ là **hậu tố** (**hậu tố**) của một xâu $Y$ nếu $X$ là xâu con của $Y$ và $X$ xuất hiện ở cuối của xâu $Y$. Ví dụ: `cd` là hậu tố của `abcd`, nhưng `bc` **không** phải là hậu tố của `abcd`.
  Một xâu $X$ là một **hậu tố không tầm thường** (**proper suffix**) của xâu $Y$ nếu nó là hậu tố của xâu $Y$ và khác xâu $Y$.

# Các dạng bài

## So khớp xâu

