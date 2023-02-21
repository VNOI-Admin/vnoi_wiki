---
title: Kinh nghiệm thi VOI
---

# Kinh nghiệm thi VOI

[[_TOC_]]

Khác với các kì thi khác, bản chất thi offline của VOI khiến thí sinh phải rất cẩn trọng và tỉ mỉ khi code. Bài viết dưới đây sẽ chỉ ra các lỗi sai mà các bạn thường gặp, đồng thời chỉ ra cách khắc phục chúng.

# Các lỗi sai thường gặp

Hai lỗi đầu tiên rất dễ tránh nếu bạn làm như sau:

5-7 phút trước khi hết giờ, các bạn nên chạy lại tất cả các bài **bằng file**. Kiểm tra xem tất cả ví dụ đúng chưa, rồi sau đó đóng code lại và **không sửa** gì nữa.

## Dịch lỗi

<figure style="text-align: center">
<img width="70%" src="https://i.imgur.com/imtNf6p.png">
<img width="70%" src="https://i.imgur.com/KIPhy94.png">
<img width="70%" src="https://i.imgur.com/E997wjd.png">
<figcaption>Các nạn nhân xấu số :(</figcaption>
</figure>

Một trong những lỗi "ngớ ngẩn" nhất có thể xảy ra trong kì thi, nhưng đã có không ít trường hợp như trên xảy ra ở PreVOI và thậm chí là VOI nữa.

Để phòng tránh thì đơn giản thôi: Trước khi bạn hoàn thành một bài, hãy compile lại nó một lần nữa để kiểm tra, sau đó đóng nó lại và không sửa gì nữa.

<figure style="text-align: center">
<img width="70%" src="https://i.imgur.com/qFKDGvI.png">
<figcaption>Đừng thêm #define int long long lúc cuối giờ...</figcaption>
</figure>

## Đọc/ghi file sai

Do thể thức đọc/ghi qua file của VOI khác với các trang thi như Codeforces hay AtCoder, nên nhiều bạn còn cẩu thả ở phần này. Các bạn nên:

- **Đọc kĩ (ít nhất hai lần) tên file dữ liệu** ở trang đầu tiên của đề thi.

<figure style="text-align: center">
<img width="70%" src="https://i.imgur.com/JRWhTaC.png">
<img width="70%" src="https://i.imgur.com/mFoGwjK.png">
<figcaption>Bạn có thấy lỗi sai không?</figcaption>
</figure>

- Khi chạy thử ví dụ, hãy chạy luôn trên các file dữ liệu thay vì nhập xuất trên terminal.

- Nếu bạn cảm thấy cách trên bất tiện, bạn có thể tham khảo đoạn code dưới đây để test bằng terminal trên máy nhưng vẫn đọc được file khi chấm bài.

  ```cpp
  // Kiểm tra xem file "SEI.inp" có tồn tại hay không
  if (fopen("SEI.inp", "r")){
      // Nếu có, mở file "SEI.inp" để đọc và file "SEI.out" để ghi
      freopen("SEI.inp", "r", stdin);
      freopen("SEI.out", "w", stdout);
  }
  ```
  
  **Lưu ý:** Chỉ nên dùng cách này nếu bạn chắc chắn bạn code đúng trong phòng thi.
  
<figure style="text-align: center">
<img width="70%" src="https://i.imgur.com/GxDRlyX.png">
<figcaption style="text-align:center">Nạn nhân xấu số khác</figcaption>
</figure>

## Lỗi khi input/output

### In thừa debug
Trước khi nộp bài, hãy gõ `Ctrl+F` để tìm tất cả các lần xuất hiện của `cout`/`printf`, khi đó *gần như* chắc chắn bạn sẽ không bỏ sót dòng debug nào hết!
Trừ khi bạn dùng `cerr`...

**Lưu ý:** Đừng xoá nhầm cả dòng output [như mình](https://discord.com/channels/660930260405190688/660934748566454276/1000076316147724378)

### Đọc chưa hết input

```cpp
int n, a[N];
int tests; cin >> tests; while (tests--){
    cin >> n;
    if (n % 2 == 0){
        cout << "NO" << endl;
        continue;
    }
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    ...
}
```

Ở code trên, trong trường hợp $n$ chẵn, ta đã `continue` sang test tiếp theo luôn mà không đọc nốt mảng $a$, dẫn đến việc input các test sau bị sai.

Để tránh việc này xảy ra, bạn nên **đọc tất cả dữ liệu của test** trước khi đi vào phần xử lí trong code.

```cpp
int n, a[N];
int tests; cin >> tests; while (tests--){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }

    // Để phần xử lí trường hợp xuống dưới phần đọc dữ liệu
    if (n % 2 == 0){
        cout << "NO" << endl;
        continue;
    }
    ...
}
```

### Output thừa

```cpp
int n, m, a[N][N];
... // Đọc input
bool has_answer = false;
for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
        // Nếu a[i][j] = 0, thì in ra i j và dừng lại
        if (a[i][j] == 0){
            cout << i << ' ' << j << endl;
            has_answer = true;
            break;
        }
    }
}
// Nếu không có phần tử nào thoả mãn, thì in ra -1 -1
if (!has_answer){
    cout << -1 << ' ' << -1 << endl;
}
```

Lỗi ở trên rất phổ biến: Nếu có hai hàng khác nhau chứa ô có giá trị bằng $0$, thì code trên sẽ in ra cả hai ô đó!

Cách sửa dễ thấy nhất là thêm một lần if biến `has_answer` ở cuối vòng for trong, tuy nhiên code nhìn sẽ khá xấu. Mình thường viết một hàm riêng để kiểm tra như sau:

```cpp
bool check(){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (a[i][j] == 0){
                cout << i << ' ' << j << endl;
                return true;
            }
        }
    }
    return false;
}
...
if (!check()){
    cout << -1 << ' ' << -1 << endl;
}
```

## Tràn mảng

Vì VOI không cho phép bạn được sai sót, nên việc để thừa mảng không phải là việc đáng bận tâm lắm. Bình thường mình sẽ khai báo mảng như sau:

```cpp
// Kích cỡ tối đa của mảng, nên lưu vào một biến constant
const int N = 1e5 + 5;

// Mình thường để thừa hẳn 5 phần tử để vừa có thể
// truy cập mảng bắt đầu từ 1 mà vẫn không lo tràn mảng.
int a[N];
```

**Lưu ý: Đọc kĩ giới hạn mảng.** Khi soát lại bài, hãy kiểm tra lại giới hạn của từng mảng một.

Không nên truy cập mảng từ $0$ vì ai biết khi nào bạn truy cập nhầm vào `a[i - 1]` đâu, tốt nhất là bắt đầu từ $1$ để bạn tạo cho chính mình một vùng an toàn. Đây cũng chính là lí do bạn nên đặc biệt chú ý khi dùng std::vector hay bitmask, vốn hay được sử dụng để duyệt trâu các subtask nhỏ.

Lưu ý một số giới hạn mảng đặc biệt: Segment Tree có giới hạn là $4\times n$, Euler Tour (trong cách cài đặt <$\mathcal O(n\log n)$, $\mathcal O(1)$> của LCA) có giới hạn là $2 \times n$.

## Tràn số

Cách dễ nhất để đề phòng tràn số là thêm một dòng `#define int long long` ngay sau khi include thư viện. Bạn sẽ không phải lo chuyện cast biến từ int sang long long, tuy nhiên thời gian chạy của code sẽ lâu hơn gấp đôi.

### Tràn số khi modulo

Với các bài yêu cầu tính đáp án theo một modulo nào đó (thường là $10^9 + 7$ hoặc $998244353$), thì bạn phải đặc biệt cẩn thận khi code. Chỉ cần quên một phép `%` thôi là bạn sẽ bay phần lớn điểm của bài.

Vậy các lỗi nào các bạn hay gặp?

- Quên mod sau từng phép tính
  ```cpp
  int a, b; cin >> a >> b;
  
  int x1 = a + b; // Sai vì a + b có thể vượt quá mod
  int x2 = (a + b) % mod; // Đúng
  
  int y1 = a * b; // Sai vì a * b có thể vượt quá mod
  int y2 = (a * b) % mod; // Sai vì a * b vẫn có thể tràn số
  int y3 = ((long long)a * b) % mod; // Đúng
  
  int z1 = ((long long)a * b * c) % mod; // Sai vì a * b * c có thể tràn số
  int z2 = (((long long)a * b) % mod * c) % mod; // Đúng
  ```
  
  Các phép tính `*`, `/`, `%` [có cùng thứ tự ưu tiên và được tính từ trái qua phải](https://en.cppreference.com/w/cpp/language/operator_precedence), nên cách code này cũng đúng:
  
  ```cpp
  int z3 = (long long)a * b % mod * c % mod; // Đúng
  ```
  
- Số âm sau khi trừ
  ```cpp
  int x1 = (a - b) % mod; // Sai
  int x2 = ((a - b) % mod + mod) % mod; // Đúng
  ```
  
  Lí do là vì phép mod số âm sẽ ra số âm, nên bạn phải cộng thêm mod để đảm bảo giá trị không âm trước khi mod thêm lần nữa.

#### Cách giải quyết

Mình sẽ code riêng các phép tính cộng, trừ, nhân ra thành hàm để đảm bảo mình mod sau mỗi phép tính và không cần phải xử lí phép trừ mỗi bước nữa.

```cpp
// Các hàm này giả sử 0 <= x, y < mod
int add(int x, int y){
    return (x + y) % mod;
}

int sub(int x, int y){
    return ((x - y) % mod + mod) % mod;
}

int mul(int x, int y){
    return (long long)x * y % mod;
}
```

### Các dạng tràn số khác
- Tràn số khi shift bit: `1 << x` sẽ tràn int nếu $x \ge 31$.
  Để kết quả là long long, hãy dùng `1ll << x`.
- Dùng `builtin_popcount`, `builtin_clz` cho long long.
  Đúng ra phải dùng `builtin_popcountll`, `builtin_clzll`.
- Tràn số khi chặt nhị phân.
  Cách tính thông thường `int mid = (l + r) / 2` sẽ tràn số nếu $l + r \ge 2^{31}$.
  Nếu chẳng may gặp tình huống này, sửa dòng trên thành `int mid = l + (r - l) / 2` --- Giá trị của $mid$ vẫn không thay đổi.
- `accumulate(a + 1, a + n + 1, 0)` sẽ tràn số nếu tổng của mảng $a$ tràn số --- Phải thay bằng `accumulate(a + 1, a + n + 1, 0ll)`.

Mình có lời khuyên là đừng dùng `INT_MAX` hay `LLONG_MAX` vì bạn sẽ phải cẩn thận hơn với việc cộng / trừ các giá trị này --- ví dụ như khi DP hay Dijkstra, có bạn để giá trị ban đầu như trên, khi đó việc transition sẽ bị lỗi.

Thay vào đó, hãy dùng các biến `const int inf = 1e9 + 7`, `const long long infll = (long long)1e18 + 7`. Nếu dùng memset thì các bạn có thể dùng biến "cách tư duy của Trung Quốc" `memset(dist, 0x3f, sizeof(dist));`[^1] --- các giá trị của $dist$ sẽ được gán bằng 1061109567.

## Sử dụng iterator và STL

### Cộng trừ iterator và dereference

```cpp
vector <int> b;
... // Đọc vào b
sort(b.begin(), b.end()); // Lưu ý: đừng quên sort trước khi chặt nhị phân!
int x; cin >> x;
vector <int>::iterator itr1 = lower_bound(b.begin(), b.end(), x);
cout << (*itr1) << endl;
vector <int>::iterator itr2 = itr1;
itr2--;
cout << (*itr2) << endl;
```

Nếu mọi phần tử trong $b$ đều bé hơn $x$, thì $itr1$ sẽ chỉ về $b.end()$, là iterator chỉ về phần tử *ngay sau* phần tử cuối của $b$. Việc dereference (tạm hiểu là lấy giá trị được chỉ đến) $itr1$ lúc này là [UB](https://en.cppreference.com/w/cpp/language/ub), và nhiều khả năng là code bạn sẽ RTE :).

Ngoài ra, nếu $itr1$ là $b.begin()$, thì dòng `itr2--;` cũng sẽ bị UB do bạn không giảm iterator xuống dưới begin được.

Để phòng tránh thì tốt nhất là bạn đừng động đến iterator luôn :D. Trong trường hợp bất đắc dĩ, thì bạn phải cố gắng xét hết mọi trường hợp corner case thôi.

### Các hàm STL đặc biệt cần lưu ý

- Để chặt nhị phân trên `set`, các bạn phải dùng hàm riêng `set::lower_bound(value)`.
  Dùng hàm `lower_bound(set::begin(), set::end(), value)` có độ phức tạp **ít nhất** là $\mathcal O(n)$. Tương tự cho các hàm khác như `upper_bound` và cấu trúc dữ liệu khác như `multiset`.
- `multiset::erase(value)` xoá **toàn bộ** các giá trị $value$ trong multiset đó.
  Để xoá một phần tử duy nhất, dùng `multiset::erase(multiset::find(value))`. Lưu ý $value$ phải tồn tại trong multiset đó.
- `multiset::count(value)` có độ phức tạp là số phần tử bằng $value$ trong multiset đó, tức là có thể lên đến $\mathcal O(n)$.
  Để đếm trong $\mathcal O(\log n)$, bạn nên dùng `map`.
- Bạn sẽ bị tràn số nếu bạn dùng `a.size() - 1` khi $a$ rỗng, do `a.size()` trả về một số unsigned.
  Để sửa thì bạn có thể dùng một dòng define chắp vá của mình: `#define isz(a) ((signed)(a).size()`

## Các lỗi sai khác

### Truyền CTDL vào hàm

```cpp
// Pass by value
int ssize(vector <int> a){
    return (int)a.size();
}

int n = 1e5;
vector <int> a(n);
for (int i = 1; i <= n; i++){
    cout << ssize(a) << endl;
}
```

Code trên có độ phức tạp là $\mathcal O(n^2)$, vì hàm `ssize` mất độ phức tạp là $\mathcal O(n)$. Lí do là vì mỗi khi gọi hàm, **toàn bộ** vector $a$ được copy lại, sau đó hàm `size` mới được gọi cho vector mới để trả về kết quả.

Để hàm `ssize` có độ phức tạp là $\mathcal O(1)$, ta sẽ sửa lại thành:

```cpp
// Pass by const reference
int ssize(const vector <int>& a){
    return (int)a.size();
}
```

Còn nếu ta muốn sửa giá trị của $a$ trong hàm:

```cpp
// Pass by reference
int ssize(vector <int>& a){
    return (int)a.size();
}
```

Các bạn có thể đọc thêm tại [đây](https://stackoverflow.com/questions/5060137/passing-as-const-and-by-reference-worth-it).

### Reset mảng

```cpp
const int N = 1e5 + 5;
int n;
int ck[N];

int tests; cin >> tests; while (tests--){
    cin >> n;
    memset(ck, 0, sizeof(ck));
    for (int i = 1; i <= n; i++){
        int x; cin >> x; // 1 <= x <= n
        ck[x] = 1;
    }
}
```

Nếu bài có $10^5$ test $n=1$, thì code trên chạy `memset` $10^5$ lần và do vậy độ phức tạp của code là $\mathcal O(10^{10})$!.

Với các bài multitest, **tuyệt đối không được memset** (trừ khi bạn biết chính xác bạn đang làm gì). Bạn có thể dùng hàm `fill` hoặc for trâu để thay thế. 

**Lưu ý:** Khi soát lại bài, hãy kiểm tra lại xem mình đã reset mọi biến trước mỗi test chưa.

## Fast I/O

### Không dùng endl

`cout << endl` tương đương với `cout << '\n' << flush`. Flush được dùng để đưa output đang ở trong buffer ra ngay lập tức, nhằm đồng bộ dữ liệu được đưa ra từ chương trình ra bên ngoài như terminal chẳng hạn. Tuy nhiên vì ta đọc/ghi qua file nên flush không để làm gì cả và nó còn rất chậm nữa.

Cách dùng thay thế là `cout << '\n'`. Nếu bạn quen tay dùng `endl` rồi, thì có thể thêm dòng `#define endl '\n'` ở bên trên code.

Các bạn có thể đọc thêm tại [đây](https://stackoverflow.com/questions/64253865/whats-the-difference-between-stdendl-and-n).

### Dùng sync_with_stdio và cin.tie

Để đẩy tốc độ nhập/xuất nhanh hơn nữa, thêm hai dòng này ở trên cùng hàm `main`:

```cpp    
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}
```

`sync_with_stdio` dùng để đồng bộ thứ tự nhập/xuất của cin -- scanf, cout -- printf. Vì bạn không dùng lẫn cả hai cái nên bạn có thể thoải mái đặt nó về $0$, khi đó tốc độ input/output sẽ được cải thiện nhiều.

`cin.tie` được dùng để đồng bộ thứ tự nhập/xuất của cin -- cout. Nếu không đồng bộ, thứ tự input/output của code bạn nhiều khả năng sẽ bị xáo trộn, nhưng vì bạn đọc/ghi qua file nên có thể đặt nó về $0$, khi đó tốc độ cũng sẽ được cải thiện nhiều.

Các bạn có thể đọc thêm tại [đây](https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull)

# Những kinh nghiệm khác

## Tối ưu

Nếu code bạn đã chính xác rồi, nhưng khi bạn chạy thử một test to thì bị TLE, thì phải làm thế nào để tối ưu?

**Lưu ý: Không dùng pragma!!!**

### Dùng mảng

Dùng mảng so với dùng `vector` có thể làm code bạn nhanh hơn một chút, nhưng như thế là quá ít ;). Hiệu quả của việc này sẽ cao hơn nhiều nếu bạn dùng để tối ưu `stack`, `queue` hay `deque`, vì cả stack và queue đều được cài đặt "ngầm" bằng deque, và deque có constant rất cao cả về time và memory.

### Khử đệ quy

Các bạn có thể đọc bài viết [này](https://vnoi.info/wiki/algo%2Fdata-structures%2FStack.md?redirected_from=translate%2Fdata-structures%2FStack.md#s%E1%BB%AD-d%E1%BB%A5ng-stack-%C4%91%E1%BB%83-kh%E1%BB%AD-%C4%91%E1%BB%87-quy) trên VNOI wiki. Nếu có thể thì bạn hãy cài stack trong này bằng mảng như đã nói ở trên.

## Dùng struct

Mình thấy nhiều bạn khi lưu cạnh của đồ thị thường hay dùng `pair <pair <int, int>, int>` hoặc `tuple <int, int, int>`. Code thế này sẽ làm giảm tốc độ code của bạn (phải gõ liên tục `edge[i].first.second`) và còn dễ bug nữa. Những lúc như thế này các bạn có thể dùng `struct` trong C++, là một công cụ khá hữu ích trong việc "đóng gói" dữ liệu.

```cpp
struct edge{
    int u, v, w;
    
    // Default constructor, khi bạn khởi tạo edge mà không có thông tin gì thêm
    edge(): u(0), v(0), w(0){
        
    }
    
    // Constructor để bạn khởi tạo edge với hai đầu mút và trọng số của cạnh
    edge(int u, int v, int w): u(u), v(v), w(w){
        
    }
};

// Input cạnh
edge a[N];
for (int i = 1; i <= n; i++){
    int u, v, w; 
    cin >> u >> v >> w;
    a[i] = edge(u, v, w);
}
```

Giờ đây bạn có thể truy cập các biến trong cạnh rất dễ dàng: `a[i].u`, `a[i].v` và `a[i].w`. Nhưng không chỉ thế, bạn còn có thể code hàm nhập/xuất tuỳ ý cho struct nữa!

```cpp
struct edge{
    int u, v, w;
    ...
    // Hàm nhập edge vào từ in
    istream& operator>> (istream& in, edge& e){
        in >> e.u >> e.v >> e.w;
        return in;
    }
    
    // Hàm xuất edge ra out
    ostream& operator<< (ostream& out, const edge& e){
        out << e.u << ' ' << e.v << ' ' << e.w;
        return out;
    }
};

// Input/output cạnh
edge a[N];
for (int i = 1; i <= n; i++){
    cin >> a[i];
    cout << a[i] << endl;
}
```

Các bạn có thể đọc thêm tại [đây](https://en.cppreference.com/w/cpp/language/operators)

# Sinh test

Trên VNOI đã có bài viết rất tốt tại [đây](https://vnoi.info/wiki/algo/skill/viet-trinh-cham.md). Mình muốn bổ sung thêm trường hợp khi các bạn cần viết checker:

```cpp
ifstream out1(NAME + ".out"), out2(NAME + ".ans");

// Viết checker. Output của code chuẩn đọc ở out1, của code trâu đọc ở out2.

out1.close(); out2.close();
cout << "Test " << iTest << ": CORRECT!\n";
```

[^1]: [link giải thích](https://codeforces.com/blog/entry/18163?#comment-230614).