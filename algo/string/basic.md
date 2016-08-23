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

## Cấu trúc dữ liệu

- [[Trie|algo/data-structures/trie]] là CTDL cơ bản nhất trong xử lý xâu. Nó giúp giải quyết các bài toán về tìm kiếm xâu.
- Lớp CTDL được gọi chung là Suffix Structures gồm:
    - [[Suffix Array|algo/data-structures/suffix-array]]
    - Suffix Automaton
    - Suffix Tree
    - Aho Corasick

    Gọi chung như vậy vì các CTDL này có thể dùng thay thế nhau để giải quyết cùng một lớp bài toán liên quan đến các suffix của cây.

## Các bài Ad-hoc

Trong xử lý xâu còn một vài thuật toán chỉ áp dụng được cho 1 bài toán (ad-hoc).

### Thuật toán Manacher

**Bài toán**

Cho xâu $S$.

- Với mỗi vị trí $i$ của xâu $S$, tìm xâu đối xứng dài nhất nhận $i$ là tâm.
- Với mỗi cặp $i$, $i+1$ của xâu $S$, tìm xâu đối xứng dài nhất nhận $i$ và $i+1$ là tâm.

**Mô tả thuật toán**

Tham khảo thêm ở [link](http://articles.leetcode.com/longest-palindromic-substring-part-ii)

**Code**

```cpp
const char DUMMY = '.';

int manacher(string s) {
  // Để tránh phải xét riêng trường hợp độ dài xâu đối xứng chẵn / lẻ,
  // ta thêm 1 ký tự DUMMY vào giữa các ký tự của s.
  // CHÚ Ý: Phải đảm bảo DUMMY không có trong xâu s

	int n = s.size() * 2 - 1;
	vector <int> f = vector <int>(n, 0);

  // Tạo xâu a bằng cách chèn ký tự DUMMY vào giữa các ký tự của s.
  // Ví dụ:
  // s = aabcb
  // a = a.a.b.c.b
	string a = string(n, DUMMY);
	for (int i = 0; i < n; i += 2) a[i] = s[i / 2];

	int l = 0, r = -1, center, res = 0;
	for (int i = 0, j = 0; i < n; i++) {
		j = (i > r ? 0 : min(f[l + r - i], r - i)) + 1;
		while (i - j >= 0 && i + j < n && a[i - j] == a[i + j]) j++;
		f[i] = --j;
		if (i + j > r) {
			r = i + j;
			l = i - j;
		}

		int len = (f[i] + i % 2) / 2 * 2 + 1 - i % 2;
		if (len > res) {
			res = len;
			center = i;
		}
	}
  // Với mỗi vị trí i, xâu đối xứng dài nhất nhận i là tâm là [i - f[i], i + f[i]].
  // Ví dụ:
  // s = aabcb
  // a = a.a.b.c.b
  // f = 011010200
	return res;
}
```

### Minimal string rotation

**Bài toán**

Cho một xâu $S$. Xét các xâu thu được từ xâu $S$ bằng phép xoay. Ví dụ: `S = abcd`, thì các xâu thu được từ $S$ bằng phép xoay là:

- `abcd`
- `bcda`
- `cdab`
- `dabc`

Tìm xâu có thứ tự từ điển nhỏ nhất.

**Mô tả thuật toán**

Bạn có thể xem [ở đây](https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation)

**Code**

```cpp
// Tính vị trí của xâu xoay vòng có thứ tự từ điển nhỏ nhất của xâu s[]
int minmove(string s) {
	int n = s.length();
	int x, y, i, j, u, v; // x is the smallest string before string y
	for (x = 0, y = 1; y < n; ++ y) {
		i = u = x;
		j = v = y;
		while (s[i] == s[j]) {
			++ u; ++ v;
			if (++ i == n) i = 0;
			if (++ j == n) j = 0;
			if (i == x) break; // All strings are equal
		}
		if (s[i] <= s[j]) y = v;
		else {
			x = y;
			if (u > y) y = u;
		}
	}
	return x;
}
```

### Lyndon Decomposition

**Bài toán**

**Lyndon word** là các xâu khác rỗng, mà có thứ tự từ điển nhỏ hơn tất cả các xâu thu được bằng phép xoay của nó.

Cho một xâu $S$. Tìm cách tách $S$ thành ít nhất các xâu, sao cho mỗi xâu đều là Lyndon word.

**Code**

```cpp
void lyndon(string s) {
	int n = (int) s.length();
	int i = 0;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j]) k = i;
			else ++k;
			++j;
		}
		while (i <= k) {
			cout << s.substr(i, j - k) << ' ';
			i += j - k;
		}
	}
	cout << endl;
}
```
