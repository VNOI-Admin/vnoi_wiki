# Disjoints Sets

**Disjoint Sets** là 1 CTDL rất hữu dụng, sử dụng rất nhanh, gọn và dễ dàng. Nó được dùng làm nền tảng cho một số thuật toán, như **Kruskal’s** và **Prim’s**, 2 thuật toán tìm **cây khung** nhỏ nhất trên đồ thị.

**Disjoint Sets**, hoặc **DSU** (**Disjoint Sets Union**) như tên gọi của nó, là một tập hợp các tập hợp.

Hãy tưởng tượng chúng ta có $n$ cái hộp và $n$ viên sỏi. Các viên sỏi phân biệt. Ban đầu mỗi viên sỏi nằm trong một cái hộp. ta cần thực hiện 2 loại truy vấn:

1. Cho hết sỏi ở 2 hộp $u$ và $v$ vào cùng một hộp.
2. Kiểm tra 2 viên sỏi $i$ và $j$ có thuộc cùng một hộp hay không

Giả sử, chỉ có duy nhất 1 bộ dụng cụ trong 1 hộp. Ta có $n$ bộ dụng cụ, $n$ hộp, và ban đầu, bộ thứ $i$ sẽ nằm trong hộp thứ $i$.

Với những yêu cầu trên, ta có thể sử dụng nhiều cấu trúc, như:

## Cài đặt Disjoint Set với Cây

Cây là cấu trúc hữu hiệu nhất dùng cho DSU. Với mỗi đỉnh, ta lưu lại đỉnh cha của nó (đỉnh cha của đỉnh gốc là -1). Ban đầu, mọi đỉnh cha được set là -1. Có các truy vấn **tìm đỉnh gốc** của mỗi hộp (có được gốc, ta có thể truy ra vị trí của hộp) và các truy vấn yêu cầu **hợp** 2 cây lại. Để thuật toán nhanh hơn, mỗi lần tìm gốc của mỗi đỉnh, ta đặt đỉnh cha của nó là gốc cho truy vấn tiếp theo. Luôn muốn độ cao của cây là nhỏ nhất có thể, vì vậy, mỗi khi nhập các hộp lại với nhau, ta bỏ các bộ dụng cụ trong hộp có ít bộ hơn vào hộp còn lại.

[/uploads/tree1.png](/tree1)

_Code C++ ([bmerry](http://codeforces.com/profile/bmerry))_

```cpp

// par[i] = x nếu viên sỏi i và viên sỏi x nằm trong cùng một hộp
// Nếu par[i] < 0 thì viên sỏi i nằm trong hộp i, và -par[i] chính là số sỏi trong hộp đó.
// Ban đầu, khởi tạo par[i] = -1 với mọi i.

int root(int v) {
    // Cho 1 số v, tìm hộp chứa viên sỏi v
    return par[v] < 0
            ? v
            : (par[v] = root(par[v])); // Viên sỏi v nằm trong cùng hộp với viên sỏi chứa par[v]
                                       // Chú ý ở đây ta gán lại par[v] = root(par[v]), kĩ thuật này
                                       // được gọi là Path Compression, giúp giảm độ phức tạp mỗi
                                       // thao tác xuống log(n)
}

void merge(int x, int y) {
    // Gộp 2 hộp chứa viên sỏi x và y vào cùng 1 hộp
    if ((x = root(x)) == (y = root(y)) {
        // 2 viên sỏi x và y đã thuộc cùng 1 hộp, ta không cần làm gì cả
        return ;
    }
    if (par[y] < par[x]) {
        // Ta gộp vào hộp chứa nhiều sỏi hơn. Kĩ thuật này gọi là Union-by-rank, và cũng giúp giảm
        // độ phức tạp mỗi thao tác xuống log(n).
        // Nếu kết hợp cả Union-by-rank và Path-compression thì độ phức tạp mỗi thao tác là ackerman(n),
        // rất rất nhỏ với n.
        swap(x, y);
    }
    par[x] += par[y];
    par[y] = x;
}
```

## Cài đặt Disjoint set với Mảng & Vector

Ta lưu vị trí các viên sỏi trong một **vector** (hoặc **mảng**) và mỗi khi có truy vấn yêu cầu **nhập** hai hộp, ta bỏ các viên sỏi ở hộp có ít viên sỏi hơn vào hộp còn lại.

Độ phức tạp không cao vì với mỗi viên sỏi, tổng số lần lấy và bỏ nó vào hộp chỉ tối đa là $log(n)$.

Độ phức tạp cho $n$ thao tác sẽ là $O(nlog(n))$.

Khi cài đặt DSU, cách này không được sử dụng (do phức tạp hơn cách trên), tuy nhiên ý tưởng này có thể được áp dụng cho nhiều bài khác.


## Cài đặt Disjoint Set với Sets (Cây Đỏ Đen; Red-Black Trees)

Một cách khác là lưu chúng trong một cây đỏ đen (trong C++ là **set** thư viện **STL**). Ta làm y như đã làm với vectors, độ phức tạp sẽ là $O(nlog^2n)$. (1 log cho việc nhập vào).

_Bài tập: (Phải tham gia nhóm [ACM-OI](http://codeforces.com/group/L1Sf9F4uBt))_

- [Hamro & Tools](http://codeforces.com/group/L1Sf9F4uBt/contest/200499/problem/E)
- [TROY Query](http://codeforces.com/gym/100571/problem/F)


# Tài liệu tham khảo:

- [Codeforces](http://codeforces.com/blog/entry/15729)
