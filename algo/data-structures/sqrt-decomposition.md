# Chia căn (sqrt decomposition) và ứng dụng

**Tác giả**: Hoàng Xuân Nhật & Vương Hoàng Long

[[_TOC_]]

Chia căn là tên gọi chung của một nhóm các thuật toán thường liên quan đến việc chia mảng độ dài $N$ ra làm $\sqrt{N}$ đoạn, dùng để giải quyết các bài toán truy vấn. 

Sau đây ta sẽ xét một dạng đơn giản nhất: chia mảng ra làm $\sqrt{N}$ đoạn.


# Bài toán

Cho một mảng $A$ gồm $N$ phần tử là các số nguyên không âm. Bạn cần trả lời $Q$ truy vấn, mỗi truy vấn có dạng $(l, r, k)$ yêu cầu tìm đếm số phần tử của A nằm trong đoạn $[l..r]$ có giá trị bằng $k$. Giới hạn: $N, Q, A_i \le 10^5$.

Giả sử ta luôn có $l = 1$ và $r = N$, bài toán trên có thể giải đơn giản bằng cách tạo một mảng $cnt[x] = $ số phần tử của mảng có giá trị **bằng** $x$.

Ta áp dụng ý tưởng này để giải bài toán tổng quát, bằng cách tạo ra $\sqrt{N}$ mảng *cnt*, mỗi mảng quản lý một đoạn $\sqrt{N}$ phần tử liên tiếp của $A$. Để hiểu rõ hơn, ta có thể xem ví dụ sau.

Ta có mảng A gốm 13 phần tử, chỉ số được đánh bắt đầu từ 0. Ta sẽ chia mảng $A$ thành các đoạn có độ dài 4, đoạn cuối cùng sẽ chỉ chứa 1 phần tử. Nội dung mảng $A$ và các mảng $cnt$ đã được tính sẵn như trong hình sau:

[[/uploads/sqrt_problem1_1.PNG]]

Với cấu trúc trên, ta có thể dễ dàng trả lời các truy vấn. Ví dụ, xét truy vấn $(1, 11, 0)$.

[[/uploads/sqrt_problem1_2.PNG]]

Có thể thấy, đoạn truy vấn sẽ luôn được chia thành các đoạn chứa đủ $\sqrt{N}$ phần tử (trong trường hợp này là đoạn $[4..7]$ và $[8..11]$), và có thể thêm một số đoạn không đầy đủ ở hai đầu (ở đây là đoạn $[1..3]$).

Với những đoạn đầy đủ, ta cộng $cnt[0]$ của chúng vào kết quả. Với những đoạn không đầy đủ, ta xét từng phần tử. Phần tử nào bằng 0, ta sẽ tăng biến đếm kết quả lên 1. Với truy vấn $(1, 11, 0)$, ta có kết quả là $2 + 3 + 1 + 1 = 7$.

[[/uploads/sqrt_problem1_3.PNG]]

Cấu trúc trên vẫn có thể giải bài toán này khi có thêm truy vấn **chỉnh sửa một phần tử** của $A$, bạn chỉ cần thay đổi giá trị $cnt$ của một đoạn duy nhất chứa phần tử cần cập nhật.


# Phân tích

Đầu tiên, ta phải trả lời được câu hỏi: tại sao lại chia thành $\sqrt{N}$ đoạn, mà không phải $1, 2, 10, N/2, ... $ ? 

Gọi số đoạn ta chia ra là $S$. Vậy mỗi đoạn sẽ có độ dài $N/S$ (ta tạm bỏ qua đoạn cuối).

Khi truy vấn, ta phải xét 2 thứ: một là những đoạn đầy đủ, nằm trong đoạn truy vấn. Hai là đoạn dư ra ở hai đầu của truy vấn.

Với những đoạn đầy đủ, trong trường hợp tệ nhất chúng ta phải xét cả $S$ đoạn. Mỗi đoạn ta cộng $cnt[k]$ vào kết quả trong $O(1)$, vậy tổng cộng mất $O(S)$.

Với đoạn dư ra ở hai đầu, ta xét riêng từng phần tử mất $O(1)$. Các đoạn đều có độ dài $N/S$, nên ta mất $O(N/S)$ cho phần này.

Mỗi truy vấn ta mất thời gian là $O(S + N/S)$. Ta cần tìm giá trị $S$ sao cho $S + N/S$ đạt giá trị nhỏ nhất. Áp dụng [bất đẳng thức AM-GM](https://vi.wikipedia.org/wiki/B%E1%BA%A5t_%C4%91%E1%BA%B3ng_th%E1%BB%A9c_trung_b%C3%ACnh_c%E1%BB%99ng_v%C3%A0_trung_b%C3%ACnh_nh%C3%A2n), giá trị này là nhỏ nhất khi $S = N/S \iff S = \sqrt{N}$. Thời gian để thực hiện $Q$ truy vấn sẽ là $O(Q\sqrt{N})$.

# Cài đặt

Ta cần phải lưu những cấu trúc sau: 
* $\sqrt{N}$ mảng $cnt$, mỗi mảng có độ dài $max(A_i)$, tốn $O(\sqrt{N} * max(A_i)$) bộ nhớ.
* Mảng $A$, tốn $O(N)$ bộ nhớ.

Khi giải bài toán, ta thường chia thành các hàm tiền xử lý để dựng ra cấu trúc dữ liệu, và các hàm trả lời các truy vấn.

```cpp
const int BLOCK_SIZE = 320;
const int N = 1e5 + 2;

int n;
int cnt[N / BLOCK_SIZE + 2][N];
int a[N];

void preprocess()
{
    for (int i = 0; i < n; ++i)
        ++cnt[i / BLOCK_SIZE][a[i]];
}
```

Sau khi đã tiền xử lý, hàm trả lời truy vấn có thể cài đặt như sau. Lưu ý, ta phải xét riêng trường hợp cả hai đầu của truy vấn nằm trong cùng một đoạn. Trong code bên dưới, tác giả dùng [hàm count](https://www.cplusplus.com/reference/algorithm/count/) của thư viện C++ STL.

```cpp
int query(int l, int r, int k)
{
    int blockL = l / BLOCK_SIZE, blockR = r / BLOCK_SIZE;
    if (blockL == blockR)
        return count(a + l, a + r + 1, k);
    
    int sum = 0;
    for (int i = blockL + 1; i < blockR; ++i)
        sum += cnt[i][k];
        
    for (int i = (blockL + 1) * BLOCK_SIZE - 1; i >= l; --i)
        if (a[i] == k) ++sum;
        
    for (int i = blockR * BLOCK_SIZE; i <= r; ++i)
        if (a[i] == k) ++sum;
        
    return sum;
}
```

Thao tác cập nhật một phần tử có thể thêm vào như sau (với $u$ là vị trí cần cập nhật, và $v$ là giá trị mới):

```cpp
void update(int u, int v)
{
    int block = u / BLOCK_SIZE;
    --cnt[block][a[u]];
    a[u] = v;
    ++cnt[block][a[u]];
}
```

# Lưu ý
* Trong phần lớn trường hợp, ta nên đặt ***BLOCK_SIZE*** là hằng số, chứ không nên thực sự lấy căn của $N$ trong dữ liệu nhập vào. Lý do là việc chia cho hằng số, cũng như việc dùng mảng tĩnh sẽ giúp code của bạn chạy nhanh hơn nhiều so với việc chia cho biến và xài mảng động.
* Khi cài đặt, các bạn cần tránh việc thực hiện $O(Q \sqrt{N})$ phép chia (cả chia lấy nguyên lẫn chia lấy dư), vì phép chia là một thao tác chậm hơn nhiều so với các phép toán khác. Phạm vào điều này nhiều khả năng sẽ khiến code bạn bị chạy quá thời gian (TLE).
* Vì thường yêu cầu bộ nhớ lớn, các bạn cần tính toán để không bị quá bộ nhớ (MLE). Cách tính như sau: 1MB = $10^6$ byte, 1 int = $4$ byte, 1 long long = $8$ byte. Ví dụ, mảng $cnt$ trong code mẫu ở trên sẽ tốn $320 * 10^5 * 4 = 128 000 000 = 128 MB$.
