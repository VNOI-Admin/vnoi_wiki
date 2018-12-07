# Aho Corasick

[[_TOC_]]

**Nguồn**: [emaxx](https://cp-algorithms.com/string/aho_corasick.html#toc-tgt-3)

**Người dịch**: Nguyễn *RR* Thành Trung

## Lưu ý

Trước khi đọc bài viết này bạn cần nắm được các kiến thức sau:

- [[Xử lý xâu|algo/string/basic]]
- [[KMP|translate/wcipeg/kmp]]
- [[Trie|algo/data-structures/trie]]

## Giới thiệu

Như các bạn đã biết:

- Thuật toán [[KMP|translate/wcipeg/kmp]] giúp tìm kiếm 1 xâu con (pattern) trong 1 xâu lớn với độ phức tạp $O(M + N)$ với $M$ và $N$ là độ dài 2 xâu.
- Cấu trúc dữ liệu [[Trie|algo/data-structures/trie]] giúp chúng ta lưu trữ và tìm kiếm $N$.

Cấu trúc dữ liệu **Aho-Corasick** có thể hình dung như 1 sự kết hợp giữa trie và KMP:


// IN PROGRESS