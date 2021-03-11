# **Các thuật về tìm đường đi ngắn nhất**

[[_TOC_]]

Ở bài viết này mình sẽ giới thiệu 3 thuật toán cơ bản của dạng bài tìm đường đi ngắn nhất.Dưới đây sẽ là 3 thuật toán mình sẽ giới thiệu.
* Thuật toán Bellman - Ford
* Thuật toán Dijkstra
* Thuật toán Floyd-Warshall.

Trong bài viết này, ta sẽ gọi tắt thuật toán Floyd-Warshall là thuật toán Floyd. Cần lưu ý rằng, có một thuật toán thông dụng khác cũng có tên thường gọi là thuật toán Floyd, dùng để tìm chu trình trong đồ thị có hướng. **[crossref đến bài two-pointer]**. Bài viết này sẽ chỉ đề cập đến thuật toán tìm đường đi ngắn nhất.

# 1. Thuật toán Bellman - Ford
### Bài toán.
Cho đồ thị có hướng $n$ đỉnh và $m$ cạnh ,một đỉnh $s$ và $q$ truy vấn. Mỗi cạnh có trọng số là $w$. Mỗi truy vấn bao gồm một đỉnh $u$. Yêu cầu với mỗi truy vấn yêu cầu xuất: 
1. Nếu không tồn tại đường đi ngắn nhất từ $s$ đến $u$ thì xuất : **Impossible**
2. Nếu trên độ dài đường đi ngắn nhất từ $s$ đến $u$ không xác định thì in ra màn hình : **-Infinity**
3. Trường hợp còn lại xuất đường đi ngắn nhất từ $s$ đến $u$.

Giới hạn bài toán : $1 \le n \le 1000 ,1 \le m \le 5000,1 \le q \le 100, -2000 \le w \le 2000$.

* **Input:** gồm nhiều Test, với mỗi Test bắt đầu bằng 4 số nguyên $n,m,q,s$.M dòng tiếp theo với mỗi dòng bao gồm ba số nguyên $u,v,w$ biểu diễn một cạnh một chiều từ u đến v với trọng số là w.
* **Output:** Với mỗi truy vấn xuất kết quả theo yêu cầu đề bài

**Sample Input**
```cmake=
5 4 3 0
0 1 999
1 2 -2
2 1 1
0 3 2
1
3
4
2 1 1 0
0 1 -100
1
0 0 0 0
```
**Sample Output**
```cmake=
-Infinity
2
Impossible

-100
```
### Khái niệm về chu trình âm

* Chu trình là một dạng đồ thị trong đó mọi đỉnh có thể đến được đỉnh khá thông qua các cạnh. 
* Chu trình âm là một chi trình trong đó tổng trọng số các cạnh là ![](https://i.imgur.com/J5jInFi.png)



* Với đồ thị trên, chúng ta dễ dàng thấy được chu trình âm là $1 -> 2 -> 3.$ Vì tổng số cạnh là -9 + 7 + 1 = -1






### Tư tưởng thuật toán
Gọi $D_u$ là đường đi ngắn nhất từ $s$ đến $u$. Ban đầu ta coi toàn bộ $D_u$ bằng $\infty$, riêng $D_s$ ta sẽ đặt bằng $0$.

Gọi $W_{u, v}$ là trọng số cạnh đi từ $u$ đến $v$. Tư tưởng thuật toán như sau : 

* **Ta sẽ tối ưu dần các d[v] như sau** : Xét lần lượt từng cạnh (u,v). Nếu độ dài đường đi ngắn nhất từ s đến v hiện tại dài hơn độ dài đường đi ngắn nhất từ s đến u + c[u,v] tức là nếu sử dụng cạnh (u,v) sẽ tốt cho $d[v]$ hơn thì ta sẽ tiến hành cập nhật $d[v] = d[u] + W_{u,v}$.Việc cập nhật này sẽ kết thúc khi không còn $d[v]$ nào được tối ưu nửa.
# Phân Tích.
* Ta sẽ có nhận xét rằng là đường đi ngắn nhất từ s đến một đỉnh bất kì u nào đều không đi qua quá n đỉnh hay nói cách khác thì sau tối đa n - 1 lần tối ưu (do đỉnh s luôn tối ưu) ta chắc chắn sẽ thu được d[u] tối ưu.
* Với nhật xét trên thì ta có thể dễ dàng đánh giá được độ phức tập của thuật toán : Chúng ta cần n-1 lần lặp và mỗi lần lặp sẽ xét m cạnh (u,v) nên dpt sẽ là n * m.
## Cài đặt
``` cpp
//Lưu đồ thị dưới dạng danh sách kề
int n,m,s,t;
struct Edge{
    int v,w;
};
vector <Edge> e[1111];
int d[1111];
int Bellman_Ford()
{
    for(int i = 1;i<=n;i++)
        d[i] = 2e9;
    d[s] = 0;
    for(int T = 1;T < n;T++)// n - 1 lần lặp
    {
        for(int u = 1;u <= n ; u++)
        {
            for(auto E : e[u])
            {
                int v = E.v;
                int w = E.w;
                if(d[v] > d[u] + w) d[v] = d[u] + w;
            }
        }
    }
    return d[t];
}
```
* Từ thuật toán trên tra có thể cải tiến để chương trình chạy nhanh hơn. Để ý rằng rất có thể tất cả các giá trị d[v] của chúng ta sẽ tối ưu hết trước khi cần lặp đến bước thứ n-1, vậy nên ta có thể cho một biến opm trả về giá trị true/false để kiểm tra xem còn d[v] nào được tối ưu hay không. Biến opm cũng sẽ giúp ta kiểm tra xem tồn tại chu trình âm hay không, Khi lặp hết n - 1 bước mà biến mà opm vẫn bằng true thì ta sẽ kết luận là tồn tại chu trình âm.
``` cpp
int Bellman_Ford()
{
    for(int i = 1;i<=n;i++)
        d[i] = 2e9;
    d[s] = 0;
    for(int T = 1;T < n;T++)// n - 1 lần lặp
    {
        bool opm = false;
        for(int u = 1;u <= n ; u++)
        {
            for(auto E : e[u])
            {
                int v = E.v;
                int w = E.w;
                if(d[v] > d[u] + w){
                    d[v] = d[u] + w;
                    opm = true;
                }
            }
        }
        if(!opm)
        {
            return d[t];
        }
    }
    return -1;
}
```













    


