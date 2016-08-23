# Trie

Tác giả: Nguyễn _RR_ Thành Trung

Trie là một cấu trúc dữ liệu dùng để quản lý một tập hợp các xâu. Trie cho phép:

- Thêm một xâu vào tập hợp
- Xóa một xâu khỏi tập hợp
- Kiểm tra một xâu có tồn tại trong tập hợp hay không.

# Cấu trúc

Trie gồm một gốc không chứa thông tin, trên mỗi cạnh lưu một ký tự, mỗi nút và đường đi từ gốc đến nút đó thể hiện 1 xâu, gồm các ký tự là các ký tự thuộc cạnh trên đường đi đó.

![Hình minh họa](https://sites.google.com/site/ngthanhtrung23/_/rsrc/1401387820016/algorithm/trie/Screenshot%20from%202014-05-30%2002%3A22%3A51.png?height=272&width=320)

Trong hình vẽ trên, nút 1 là nút gốc, nút 7 thể hiện có 1 xâu là ‘bg’, nút 8 thể hiện có 1 xâu là ‘db’, nút 9 thể hiện có 1 xâu là ‘dc’, nút 10 thể hiện có 1 xâu là ‘acd’, nút 5 thể hiện là có 1 xâu là ‘ab’.

Tuy nhiên, như các bạn có thể thấy, đối với một số nút, chẳng hạn nút 4, ta không biết nó là thể hiện kết thúc 1 xâu hay chỉ là 1 phần của đường đi từ nút 1 đến nút 9. Vì vậy, khi cài đặt, thông thường, tại nút U ta cần lưu thêm thông tin nút U có là kết thúc của 1 xâu hay không, hoặc nút U là kết thúc của bao nhiêu xâu, tuỳ theo yêu cầu bài toán.

# Một số ưu điểm của trie

- Cài đặt đơn giản, dễ nhớ

- Tiết kiệm bộ nhớ: Khi số lượng khóa lớn và các khóa có độ dài nhỏ, thông thường trie tiết kiệm bộ nhớ hơn do các phần đầu giống nhau của các khoá chỉ được lưu 1 lần. Ưu điểm này có ứng dụng rất lớn, chẳng hạn trong từ điển.

- Thao tác tìm kiếm: $O(m)$ với $m$ là độ dài khóa. Với **Binary search tree** (cân bằng): là $O(logN)$. Khi số lượng khóa cần tìm lớn và độ dài mỗi khóa tương đối nhỏ, $logN$ xấp xỉ $m$, và như các bạn đã biết, để cài được **Binary search tree** cân bằng không phải là một việc đơn giản. Hơn nữa, các thao tác trên trie rất đơn giản và thường chạy nhanh hơn trên thực tế.

- Dựa vào tính chất của cây trie, có thể thực hiện một số liên quan đến thứ tự từ điển như sắp xếp, tìm một khóa có thứ tự từ điển nhỏ nhất và lớn hơn một khóa cho trước...; và một số thao tác liên quan đến tiền tố, hậu tố.

# Cài đặt

```pascal
//Định nghĩa kiểu trie
type
    trie = ^node;
    node = record
        count : longint; //Số lượng xâu kết thúc tại một nút
        c : array['a'..'z'] of trie; //Link đến các nút con của một nút
    end;
var
    root : trie; //Gốc trie

//Thêm một nút rỗng vào trie
procedure add(var a:trie);
var
    c : char;
begin
    new(a);
    a^.count:=0;
    for c:='a' to 'z' do 
        a^.c[c]:=nil;
end;
//Thêm xâu s vào trie 
procedure insert(s:string);
var
    i : longint;
begin
    for i:=1 to length(s) do
    begin
        //Duyệt mỗi kí tự i của s. Với mỗi kí tự, ta đi theo nhánh tương ứng với ký tự i, nếu nhánh này chưa có, ta thêm vào cây
        if p^.c[s[i]]=nil then add(p^.c[s[i]]);
        p:=p^.c[s[i]];
    end;
    inc(p^.count);
end;

//Tìm  xem xâu s có trong trie không
function find(s:string):boolean;
var
    i : longint;
    p : trie;
begin
    p:=root;
    for i:=1 to length(s) do
        begin
            if p^.c[s[i]]=nil then exit(false);
            p:=p^.c[s[i]];
        end;
    exit(true);
end;
```

_(Có thể cài đặt thêm thao tác xóa một từ khỏi trie, nhưng đối với các bài toán thường gặp thì thao tác này không cần thiết. Việc cài đặt cụ thể xin nhường lại cho bạn đọc)_

# Một vài ứng dụng trong các bài toán

Sau đây là một vài ví dụ cơ bản thể hiện tác dụng của trie

## Chuỗi từ

**Nguồn**: Цикл Интернет-олимпиад для школьников, сезон 2007-2008

Chuỗi từ có độ dài $n$ là một dãy các từ $w_1, w_2, ..., w_n$ sao cho với mọi $1 \le i < n$, từ $w_i$ là tiền tố của từ $w_{i+1}$. Từ $u$ có độ dài $k$ là tiền tố của từ $v$ có độ dài $l$ nếu $l > k$ và các ký tự đầu tiên của $v$ trùng với từ $u$. Cho tập hợp các từ $S = {s_1, s_2, ..., s_m}$. Tìm chuỗi từ dài nhất có thể xây dựng được bằng cách dùng các từ trong tập hợp $S$ (có thể không sử dụng hết các từ).

### Thuật toán

Một trong những cách giải khá đơn giản đối với bài này là sử dụng trie:

Lưu tất cả các từ lại vào trie. Đối với mỗi nút trên cây, ta tính $f$ là độ dài chuỗi từ dài nhất bắt đầu ở nút đó.

### Cài đặt một số phần quan trọng

```pascal
type
    trie = ^node;
    node = record
        f,u : longint; //Số lượng xâu kết thúc tại một nút
        c : array['a'..'z'] of trie; //Link đến các nút con của một nút
    end;
...
procedure dfs(a:trie);
var
    c : char;
begin
    a^.f:=0
    for c:='a' to 'z' do
        begin
            dfs(a^.c[c]);
            a^.f:=max(a^.f,a^.c[c].f);
        end;;
    inc(a^.f,a^.u);
end;

function solve:longint;
begin
    add(root);
    for i:=1 to m do insert(s[i]);
    dfs(root);
    exit(root^.f);
end;

```

## Tách từ

**Nguồn**: Croatian OI 2006

Một xâu $S$ độ dài không quá $300,000$ cần được tách thành các đoạn con sao cho mỗi đoạn con thuộc một tập gồm không quá 400 từ cho trước, mỗi từ có độ dài không quá $100$, không có 2 từ nào giống nhau.

Viết chương trình xác định số cách tách một từ cho trước.

### Thuật toán

Quy hoạch động.

Đặt $f[i]$ là số cách tách đoạn từ 1 đến $i$ của $S$.

Như vậy, $f[i] = \sum{f[j]}$ với mỗi $j$ thoả mãn đoạn từ $j+1..i$ là một từ thuộc tập từ đã cho. Ta lần lượt tính $f[i]$ với $i$ chạy từ 1 đến $n$. Với mỗi $i$, để kiểm tra mọi đoạn $j..i$ có là một từ cho trước không, chú ý là khi giảm $j$, các từ này có độ dài tăng lên, và từ trước là hậu tố của từ sau, các từ có độ dài hơn kém nhau một đơn vị. Do đó, trên cây trie, ta có thể đi từ gốc xuống các nút thể hiện các xâu này, nếu không đi được nữa, tức là không có từ nào thoả mãn. Chú ý là khi thêm các xâu của tập đã cho, ta cần thêm các xâu này theo chiều ngược (hoặc một cách xử lý khác là ta tính hàm $f$ từ $n$ đến 1).

### Cài đặt một số phần quan trọng

```pascal
f[0]=1;
for i:=1 to n do
    begin
        j:=i; p:=root;
        while (j>0) and (p^.c[s[j]]<>nil) do
            begin
                p:=p^.c[s[j]];
                dec(j);
                if (x^.c=1) then inc(f[i],f[j]);
            end;
    end;

```

# Bài tập áp dụng:

- [VOJ - NKSEV](http://vn.spoj.com/problems/NKSEV/)
- [VOJ - SEC](http://vn.spoj.com/problems/SEC/)
- [VOJ - CHAIN2](http://vn.spoj.com/problems/CHAIN2/)
- [A lot of games](http://codeforces.com/contest/456/problem/D)